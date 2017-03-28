/*
 * Copyright (c) 2015-2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/***** Includes *****/
#include <xdc/std.h>
#include <xdc/runtime/System.h>

#include "ConcentratorRadioTask.h"

#include <ti/sysbios/BIOS.h>

#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Event.h>

/* Drivers */
#include <ti/drivers/rf/RF.h>
#include <ti/drivers/PIN.h>
#include <ti/drivers/GPIO.h>


/* Board Header files */
#include "Board.h"

#include "easylink/EasyLink.h"
#include "RadioProtocol.h"


/***** Defines *****/
#define CONCENTRATORRADIO_TASK_STACK_SIZE       1024
#define CONCENTRATORRADIO_TASK_PRIORITY         3

#define RADIO_EVENT_ALL                         0xFFFFFFFF
#define RADIO_EVENT_VALID_PACKET_RECEIVED       (uint32_t)(1 << 0)
#define RADIO_EVENT_INVALID_PACKET_RECEIVED     (uint32_t)(1 << 1)

#define CONCENTRATOR_MAX_NODES          3
#define CONCENTRATORRADIO_MAX_RETRIES   2
#define NORERADIO_ACK_TIMEOUT_TIME_MS   (160)


#define CONCENTRATOR_ACTIVITY_LED


/***** Type declarations *****/



/***** Variable declarations *****/
static Task_Params concentratorRadioTaskParams;
Task_Struct concentratorRadioTask; /* not static so you can see in ROV */
static uint8_t concentratorRadioTaskStack[CONCENTRATORRADIO_TASK_STACK_SIZE];
Event_Struct radioOperationEvent;  /* not static so you can see in ROV */
static Event_Handle radioOperationEventHandle;


static ConcentratorRadio_PacketReceivedCallback packetReceivedCallback;
static union ConcentratorPacket latestRxPacket;
static EasyLink_TxPacket txPacket;
static struct AckPacket ackPacket;
static struct StringPacket *stringPacket;
static uint8_t concentratorAddress;
static int8_t latestRssi;
static uint8_t nNodesWaiting;

static uint8_t password_length;
static char password[PASSWORD_LENGTH];

static struct NWK_Node bindWaitNode;
static struct NWK_Node* bindWaitList[CONCENTRATOR_MAX_NODES];
static struct NWK_Node* nodeIter = knownSensorNodes;


/***** Prototypes *****/
static void concentratorRadioTaskFunction(UArg arg0, UArg arg1);
static void rxDoneCallback(EasyLink_RxPacket * rxPacket, EasyLink_Status status);
static void notifyPacketReceived(union ConcentratorPacket* latestRxPacket);
static void sendStatusMsg(uint32_t statusMsg);
static void sendAck(uint8_t latestSourceAddress);
static uint8_t isKnownNodeAddress(uint8_t address);
static uint8_t checkPassw(char *passw);
static uint8_t addNewNode(struct NWK_Node* node);
static void replaceNode(uint8_t address, struct NWK_Node* node);
static void removeNode(uint8_t address);


/* Pin driver handle */
//static PIN_Handle ledPinHandle;
//static PIN_State ledPinState;
//PIN_Handle pinHandle;


/* Configure LED Pin */
/*PIN_Config ledPinTable[] = {
        CONCENTRATOR_ACTIVITY_LED | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    PIN_TERMINATE
};

/***** Function definitions *****/
void ConcentratorRadioTask_init(void)
{
    uint8_t i;

    GPIO_init();

    password[0] = '4';
    password[1] = '3';
    password[2] = '2';
    password[3] = '1';
    password[4] = '\0';

    password_length = 5;

    /* Create event used internally for state changes */
    Event_Params eventParam;
    Event_Params_init(&eventParam);
    Event_construct(&radioOperationEvent, &eventParam);
    radioOperationEventHandle = Event_handle(&radioOperationEvent);

    /* Create the concentrator radio protocol task */
    Task_Params_init(&concentratorRadioTaskParams);
    concentratorRadioTaskParams.stackSize = CONCENTRATORRADIO_TASK_STACK_SIZE;
    concentratorRadioTaskParams.priority = CONCENTRATORRADIO_TASK_PRIORITY;
    concentratorRadioTaskParams.stack = &concentratorRadioTaskStack;
    Task_construct(&concentratorRadioTask, concentratorRadioTaskFunction, &concentratorRadioTaskParams, NULL);
}

void ConcentratorRadioTask_registerPacketReceivedCallback(ConcentratorRadio_PacketReceivedCallback callback) {
    packetReceivedCallback = callback;
}

static void concentratorRadioTaskFunction(UArg arg0, UArg arg1)
{
    /* Initialize EasyLink */
    if(EasyLink_init(RADIO_EASYLINK_MODULATION) != EasyLink_Status_Success) {
        System_abort("EasyLink_init failed");
    }


    /* If you wich to use a frequency other than the default use
     * the below API
     * EasyLink_setFrequency(868000000);
     */

    /* Set concentrator address */;
    concentratorAddress = RADIO_CONCENTRATOR_ADDRESS;
    EasyLink_enableRxAddrFilter(&concentratorAddress, 1, 1);

    /* Set up Ack packet */
    ackPacket.header.sourceAddress = concentratorAddress;
    ackPacket.header.packetType = RADIO_PACKET_TYPE_ACK_PACKET;

    /* Enter receive */
    if(EasyLink_receiveAsync(rxDoneCallback, 0) != EasyLink_Status_Success) {
        System_abort("EasyLink_receiveAsync failed");
    }

    while (1) {
        uint32_t events = Event_pend(radioOperationEventHandle, 0, RADIO_EVENT_ALL, BIOS_WAIT_FOREVER);

        /* If valid packet received */
        if(events & RADIO_EVENT_VALID_PACKET_RECEIVED)
        {
            /* Did the Event include status flag? */
            if(events & STATUS_EVENT_FLAGS)
            {
                /* Remove Valid Packet flag from events */
                events = events & ~RADIO_EVENT_VALID_PACKET_RECEIVED;

                /* Send status message */
                sendStatusMsg(events);
            }
            else
            {
                /* Send ack packet */
                sendAck(latestRxPacket.nodeInfo.address);
            }

            /* Call packet received callback */
            notifyPacketReceived(&latestRxPacket);

            /* Go back to RX */
            if(EasyLink_receiveAsync(rxDoneCallback, 0) != EasyLink_Status_Success) {
                System_abort("EasyLink_receiveAsync failed");
            }
        }

        /* If invalid packet received */
        if(events & RADIO_EVENT_INVALID_PACKET_RECEIVED) {
            /* Go back to RX */
            if(EasyLink_receiveAsync(rxDoneCallback, 0) != EasyLink_Status_Success) {
                System_abort("EasyLink_receiveAsync failed");
            }
        }
    }
}

static void sendStatusMsg(uint32_t statusMsg)
{
    /* Set destinationAdress */
    txPacket.dstAddr[0] = bindWaitNode.address;

    txPacket.payload[0] = RADIO_CONCENTRATOR_ADDRESS;
    txPacket.payload[1] = RADIO_PACKET_TYPE_NETW_STATUS_PACKET;

    txPacket.payload[2] = (statusMsg & 0xFF000000) >> 24;
    txPacket.payload[3] = (statusMsg & 0x00FF0000) >> 16;
    txPacket.payload[4] = (statusMsg & 0x0000FF00) >> 8;
    txPacket.payload[5] = (statusMsg & 0x000000FF);

    txPacket.len = sizeof(struct NetwStatus);

    GPIO_toggle(Board_GPIO_LED1);


    /* Send packet  */
    if (EasyLink_transmit(&txPacket) != EasyLink_Status_Success)
    {
        System_abort("EasyLink_transmit failed");
    }
}

static void sendAck(uint8_t latestSourceAddress) {

    /* Set destinationAdress, but use EasyLink layers destination adress capability */
    txPacket.dstAddr[0] = latestSourceAddress;

    /* Copy ACK packet to payload, skipping the destination adress byte.
     * Note that the EasyLink API will implcitily both add the length byte and the destination address byte. */
    memcpy(txPacket.payload, &ackPacket.header, sizeof(ackPacket));
    txPacket.len = sizeof(ackPacket);

    /* Send packet  */
    if (EasyLink_transmit(&txPacket) != EasyLink_Status_Success)
    {
        System_abort("EasyLink_transmit failed");
    }

    uint8_t i;

    for(i = 0; i < 5; i++) {
        GPIO_toggle(Board_GPIO_LED0);

        Task_sleep(100000);

        GPIO_toggle(Board_GPIO_LED0);

        Task_sleep(100000);
    }
}

static void notifyPacketReceived(union ConcentratorPacket* latestRxPacket)
{
    if (packetReceivedCallback)
    {
        packetReceivedCallback(latestRxPacket, latestRssi);
    }
}

static void rxDoneCallback(EasyLink_RxPacket * rxPacket, EasyLink_Status status)
{
    //union ConcentratorPacket* tmpRxPacket;
    struct PacketHeader* packetHeader;

    /* If we received a packet successfully */
    if (status == EasyLink_Status_Success)
    {
        /* Save the latest RSSI, which is later sent to the receive callback */
        latestRssi = (int8_t)rxPacket->rssi;

        packetHeader = (struct PacketHeader*)(rxPacket->payload);
        //tmpRxPacket = (union ConcentratorPacket*)(rxPacket->payload);

        /* Check if we know this unit/node from before */
        if (isKnownNodeAddress(packetHeader->sourceAddress))
        {
            /* Texas stuff */
            if (packetHeader->packetType == RADIO_PACKET_TYPE_DATA_PACKET)
            {
                /* Save packet */
                /*
                latestRxPacket.header.sourceAddress = rxPacket->payload[0];
                latestRxPacket.header.packetType = rxPacket->payload[1];
                */
                latestRxPacket.msgType = MSG_TYPE_DATA;
                latestRxPacket.nodeInfo.address = rxPacket->payload[0];
                latestRxPacket.adcSensorPacket.header.sourceAddress = rxPacket->payload[0];
                latestRxPacket.adcSensorPacket.header.packetType = rxPacket->payload[1];
                latestRxPacket.adcSensorPacket.adcValue = (rxPacket->payload[2] << 8) | rxPacket->payload[3];

                /* Signal packet received */
                Event_post(radioOperationEventHandle, RADIO_EVENT_VALID_PACKET_RECEIVED);
            }
            /* Texas stuff */
            else if (packetHeader->packetType == RADIO_PACKET_TYPE_DM_SENSOR_PACKET)
            {
                /* Save packet */
                latestRxPacket.msgType = MSG_TYPE_DATA;
                latestRxPacket.nodeInfo.address = rxPacket->payload[0];
                latestRxPacket.dmSensorPacket.header.sourceAddress = rxPacket->payload[0];
                latestRxPacket.dmSensorPacket.header.packetType = rxPacket->payload[1];
                latestRxPacket.dmSensorPacket.adcValue = (rxPacket->payload[2] << 8) | rxPacket->payload[3];
                latestRxPacket.dmSensorPacket.batt = (rxPacket->payload[4] << 8) | rxPacket->payload[5];
                latestRxPacket.dmSensorPacket.time100MiliSec = (rxPacket->payload[6] << 24) |
                                                               (rxPacket->payload[7] << 16) |
                                                               (rxPacket->payload[8] << 8) |
                                                                rxPacket->payload[9];
                latestRxPacket.dmSensorPacket.button = rxPacket->payload[10];

                /* Signal packet received */
                Event_post(radioOperationEventHandle, RADIO_EVENT_VALID_PACKET_RECEIVED);
            }
            /* If this is an init packet */
            else if (packetHeader->packetType == RADIO_PACKET_TYPE_INIT_PACKET)
            {
                latestRxPacket.msgType = 0;

                /* Post radioTask to tell the node that it is connected. */
                Event_post(radioOperationEventHandle, NODE_ALREADY_KNOWN | RADIO_EVENT_VALID_PACKET_RECEIVED);
            }
            else
            {
                /* Signal invalid packet received */
                Event_post(radioOperationEventHandle, RADIO_EVENT_INVALID_PACKET_RECEIVED);
            }
        }
        /* If the unit/node is unknown to this network */
        else
        {
            /* If this is an init packet */
            if (packetHeader->packetType == RADIO_PACKET_TYPE_INIT_PACKET)
            {
                /*latestRxPacket.header.sourceAddress = rxPacket->payload[0];
                latestRxPacket.header.packetType = rxPacket->payload[1];
                */

                latestRxPacket.msgType = 0;

                /* Save the node's address, nodeType and RSSI in a "wait state"
                 * for it to be remembered in the authentication process
                 */
                bindWaitNode.address = rxPacket->payload[0];
                bindWaitNode.nodeType = rxPacket->payload[2];
                bindWaitNode.latestRssi = latestRssi;

                /* Possible Implementation: "waitList"
                 * A node wait list for nodes that haven't been authenticated yet.
                 * Instead of only one wait spot.
                 */

                /*bindWaitList[nNodesWaiting]->address = rxPacket->payload[0];
                bindWaitList[nNodesWaiting]->nodeType = rxPacket->payload[2];
                bindWaitList[nNodesWaiting]->latestRssi = latestRssi;

                nNodesWaiting++;*/

                /* Post radioTask to send "authentication request" to the node. */
                Event_post(radioOperationEventHandle, RADIO_EVENT_AUTHENTICATE | RADIO_EVENT_VALID_PACKET_RECEIVED);
            }
            /* If the packet contains a network password */
            else if(packetHeader->packetType == RADIO_PACKET_TYPE_PASSW)
            {
                stringPacket = (struct StringPacket *) rxPacket->payload;

                latestRxPacket.msgType = 0;

                // Check that the node is in the wait list
                if (stringPacket->header.sourceAddress == bindWaitNode.address)
                {
                    // Check that the password is correct
                    if(checkPassw(stringPacket->buffer/*(char *)&rxPacket->payload[2]*/))
                    {
                        // If there is space in the network, add the node
                        if(addNewNode(&bindWaitNode))
                        {
                            latestRxPacket.msgType = MSG_TYPE_NEW_UNIT;
                            latestRxPacket.nodeInfo.address = bindWaitNode.address;
                            latestRxPacket.nodeInfo.nodeType = bindWaitNode.nodeType;
                            latestRxPacket.nodeInfo.latestRssi = bindWaitNode.latestRssi;

                            /* Post radioTast that connection was successful */
                            Event_post(radioOperationEventHandle, RADIO_EVENT_CONNECT_SUCCESS | RADIO_EVENT_VALID_PACKET_RECEIVED);


                            // Maybe indicate that the wait spot is free.
                            // But it won't matter, really.
                        }
                        else
                        {
                            /* Post radioTask that the network is full */
                            Event_post(radioOperationEventHandle, RADIO_EVENT_NETW_FULL | RADIO_EVENT_VALID_PACKET_RECEIVED);
                        }
                    }
                    else
                    {
                        Event_post(radioOperationEventHandle, RADIO_EVENT_WRONG_PASSW | RADIO_EVENT_AUTHENTICATE | RADIO_EVENT_VALID_PACKET_RECEIVED);
                    }
                }
                /* The node wasn't in the wait list. Send a fail message */
                else
                {
                    Event_post(radioOperationEventHandle, RADIO_EVENT_CONNECT_FAIL | RADIO_EVENT_VALID_PACKET_RECEIVED);
                }
            }
            else if(packetHeader->packetType == RADIO_PACKET_TYPE_STRING_PACKET)
            {
                stringPacket = (struct StringPacket *) rxPacket->payload;

                latestRxPacket.msgType = MSG_TYPE_STRING;

            }
            else
            {
                latestRxPacket.msgType = 0;
                // A NODE IS TRYING TO SEND DATA WITHOUT PERMISSION IN THIS NETWORK!!!
            }
        }
    }
    else
    {
        latestRxPacket.msgType = 0;

        /* Signal invalid packet received */
        Event_post(radioOperationEventHandle, RADIO_EVENT_INVALID_PACKET_RECEIVED);
    }
}

static uint8_t checkPassw(char *passw)
{
    int i;

    for (i = 0; password[i] != '\0'; i++)
    {
        if (passw[i] != password[i])
            return 0;
    }
    if ((passw[i] == '\0') && (password[i] == '\0'))
        return 1;

    return 0;
}


static uint8_t isKnownNodeAddress(uint8_t address)
{
    uint8_t found = 0;
    uint8_t i;

    for (i = 0; i < CONCENTRATOR_MAX_NODES; i++)
    {
        if (knownSensorNodes[i].address == address)
        {
            found = 1;
            break;
        }
    }
    return found;
}

static uint8_t addNewNode(struct NWK_Node* node)
{
    /*nodeIter = knownSensorNodes;

    while (nodeIter < &knownSensorNodes[CONCENTRATOR_MAX_NODES-1])
    {
        if (nodeIter->address == -1)
        {
            *nodeIter = *node;

            //knownSensorNodes[i].address = node->address;
            return 1;
        }
        nodeIter++;
    }

    return 0;*/

    if (nodeIter <= &knownSensorNodes[CONCENTRATOR_MAX_NODES-1])
    {
        *nodeIter = *node;
        nodeIter++;

        return 1;
    }

    return 0;
}

/* Replace node with existing
 */
static void replaceNode(uint8_t address, struct NWK_Node* node)
{
    removeNode(address);

    *nodeIter = *node;
}

/* Removes a node
 */
static void removeNode(uint8_t address)
{
    uint8_t i;

    for(i = 0; i < CONCENTRATOR_MAX_NODES; i++)
    {
        if(knownSensorNodes[i].address == address)
        {
            // Förutom att göra platsen tillgänglig kanske initiera noden som *empty* eller nåt
            nodeIter = &knownSensorNodes[i];
        }
    }
}

