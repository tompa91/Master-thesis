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

#ifndef TASKS_CONCENTRATORRADIOTASKTASK_H_
#define TASKS_CONCENTRATORRADIOTASKTASK_H_

#include "stdint.h"
#include "RadioProtocol.h"

#define CONCENTRATOR_MAX_NODES          3

#define PASSWORD_LENGTH     20

#define RADIO_EVENT_ALL                 0xFFFFFFFF
#define RADIO_EVENT_SEND_DATA           (uint32_t)(1 << 0)
#define RADIO_EVENT_DATA_ACK_RECEIVED   (uint32_t)(1 << 1)
#define RADIO_EVENT_ACK_TIMEOUT         (uint32_t)(1 << 2)
#define RADIO_EVENT_SEND_FAIL           (uint32_t)(1 << 3)
#define RADIO_EVENT_SEND_INIT_MSG       (uint32_t)(1 << 4)
#define RADIO_EVENT_SEND_STRING         (uint32_t)(1 << 5)
#define RADIO_EVENT_RECV_PASSW          (uint32_t)(1 << 6)
#define RADIO_EVENT_CONNECT_FAIL        (uint32_t)(1 << 7)
#define RADIO_EVENT_CONNECT_SUCCESS     (uint32_t)(1 << 8)
#define RADIO_EVENT_NETW_FULL           (uint32_t)(1 << 9)
#define RADIO_EVENT_AUTHENTICATE        (uint32_t)(1 << 10)
#define RADIO_EVENT_WRONG_PASSW         (uint32_t)(1 << 11)
#define RADIO_EVENT_INIT                (uint32_t)(1 << 12)
#define NODE_ALREADY_KNOWN              (uint32_t)(1 << 13)

#define STATUS_EVENT_FLAGS              (RADIO_EVENT_CONNECT_FAIL | RADIO_EVENT_CONNECT_SUCCESS | RADIO_EVENT_NETW_FULL | RADIO_EVENT_AUTHENTICATE | RADIO_EVENT_WRONG_PASSW | NODE_ALREADY_KNOWN)







#define NODE_TYPE_ALL                   0xFF
#define NODE_TYPE_TEMP                  (uint8_t)(1 << 0)
#define NODE_TYPE_BLE_ANNCE             (uint8_t)(1 << 1)
#define NODE_TYPE_OTHER                 (uint8_t)(1 << 2)


enum ConcentratorRadioOperationStatus {
    ConcentratorRadioStatus_Success,
    ConcentratorRadioStatus_Failed,
    ConcentratorRadioStatus_FailedNotConnected,
};

union ConcentratorPacket {
    struct PacketHeader header;
    struct AdcSensorPacket adcSensorPacket;
    struct DualModeSensorPacket dmSensorPacket;
};

/***** Type declarations *****/
struct NWK_Node {
    uint8_t address;
    uint8_t nodeType;
    uint8_t latestRssi;
};

struct AdcSensorNode {
    uint8_t address;
    uint16_t latestAdcValue;
    uint8_t button;
    int8_t latestRssi;
};

struct BLE_Node {
    uint8_t address;
    uint8_t latestRssi;
};


struct NWK_Node knownSensorNodes[CONCENTRATOR_MAX_NODES];


typedef void (*ConcentratorRadio_PacketReceivedCallback)(union ConcentratorPacket* packet, int8_t rssi);

/* Create the ConcentratorRadioTask and creates all TI-RTOS objects */
void ConcentratorRadioTask_init(void);


/* Register the packet received callback */
void ConcentratorRadioTask_registerPacketReceivedCallback(ConcentratorRadio_PacketReceivedCallback callback);

#endif /* TASKS_CONCENTRATORRADIOTASKTASK_H_ */
