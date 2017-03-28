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


#include "string.h"
#include <xdc/std.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/knl/Clock.h>

#include <ti/drivers/PIN.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>

/* Board Header files */
#include "Board.h"


//#include "SceAdc.h"
#include "NodeTask.h"
#include "NodeRadioTask.h"



/***** Defines *****/

#define COMMISSIONING

#define NODE_TASK_STACK_SIZE 1024
#define NODE_TASK_PRIORITY   3

#define NODE_EVENT_ALL              0xFFFFFFFF
#define NODE_EVENT_NEW_ADC_VALUE    (uint32_t)(1 << 0)

#ifdef COMMISSIONING
#define USER_TASK_STACK_SIZE  1024
#define USER_TASK_PRIORITY    5

#define CONNECT_EVENT_ALL           0xFFFFFFFF
#define CONNECT_SUCCESS_EVENT       (uint32_t)(1 << 0)

#endif //COMMISSIONING

/* A change mask of 0xFF0 means that changes in the lower 4 bits does not trigger a wakeup. */
#define NODE_ADCTASK_CHANGE_MASK                    0xFF0

/* Minimum slow Report interval is 50s (in units of samplingTime)*/
#define NODE_ADCTASK_REPORTINTERVAL_SLOW                2
/* Minimum fast Report interval is 1s (in units of samplingTime) for 30s*/
#define NODE_ADCTASK_REPORTINTERVAL_FAST                1
#define NODE_ADCTASK_REPORTINTERVAL_FAST_DURIATION_MS   30000



/***** Variable declarations *****/
static Task_Params nodeTaskParams;
Task_Struct nodeTask;    /* not static so you can see in ROV */
static uint8_t nodeTaskStack[NODE_TASK_STACK_SIZE];
Event_Struct nodeEvent;  /* not static so you can see in ROV */
static Event_Handle nodeEventHandle;
//static uint16_t latestAdcValue;
static uint16_t txData;

#ifdef COMMISSIONING
static Task_Params userTaskParams;
Task_Struct userTaskStruct;
static uint8_t userTaskStack[USER_TASK_STACK_SIZE];
Event_Struct connectEvent;
static Event_Handle connectEventHandle;
const char  skip2rows[]         = "\r\n\r\n";
const char  enter_pass[]        = "Enter network password: ";
const char  wrong_pass[]        = "Wrong password, try again!\r\n";
const char  netw_full[]         = "The network is full. To replace an existing node, press Y. Press n if nothing is to be done.\r\n";
const char  connected[]         = "Connection to Concentrator established.\r\n\r\n";
const char  connection_failed[] = "Connection failed. Try again? Y/n: ";


static char passw[PASSWORD_LENGTH];
#endif //COMMISSIONING


/* Clock for the fast report timeout */
Clock_Struct fastReportTimeoutClock;     /* not static so you can see in ROV */
static Clock_Handle fastReportTimeoutClockHandle;

/* Pin driver handle */
/*static PIN_Handle buttonPinHandle;
static PIN_Handle ledPinHandle;
static PIN_State buttonPinState;
static PIN_State ledPinState;
*/
/* Enable the 3.3V power domain used by the LCD */
/*PIN_Config pinTable[] = {
    NODE_ACTIVITY_LED | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    PIN_TERMINATE
};*/

/*
 * Application button pin configuration table:
 *   - Buttons interrupts are configured to trigger on falling edge.
 */
/*PIN_Config buttonPinTable[] = {
    Board_PIN_BUTTON1 | PIN_INPUT_EN | PIN_PULLDOWN | PIN_IRQ_POSEDGE,
    PIN_TERMINATE
};*/

/***** Prototypes *****/
#ifdef COMMISSIONING
static void userTask(UArg arg0, UArg arg1);
#endif //COMMISSIONING

static void nodeTaskFunction(UArg arg0, UArg arg1);
void fastReportTimeoutCallback(UArg arg0);
void adcCallback(uint16_t adcValue);
void buttonCallback(PIN_Handle handle, PIN_Id pinId);
void uartRead(UART_Handle uart, struct UARTPacket *data, uint8_t *dataLen);
void uartWrite(UART_Handle uart, struct UARTPacket *data, uint8_t dataLen);
void commissioningHandler(UART_Handle uart, uint32_t cEvents);

/***** Function definitions *****/

/*
 *  Initialization of the commissioning task
 */
#ifdef COMMISSIONING
void userTask_init(void)
{
    /* Create event used internally for state changes */
    Event_Params eventParam2;
    Event_Params_init(&eventParam2);
    Event_construct(&connectEvent, &eventParam2);
    connectEventHandle = Event_handle(&connectEvent);

    /* Create the node task */
    Task_Params_init(&userTaskParams);
    userTaskParams.stackSize = USER_TASK_STACK_SIZE;
    userTaskParams.priority = USER_TASK_PRIORITY;
    userTaskParams.stack = &userTaskStack;
    Task_construct(&userTaskStruct, userTask, &userTaskParams, NULL);
}
#endif //COMMISSIONING


void NodeTask_init(void)
{
    GPIO_init();

    /* Create event used internally for state changes */
    Event_Params eventParam;
    Event_Params_init(&eventParam);
    Event_construct(&nodeEvent, &eventParam);
    nodeEventHandle = Event_handle(&nodeEvent);

    /* Create clock object which is used for fast report timeout */
    Clock_Params clkParams;
    clkParams.period = 0;
    clkParams.startFlag = FALSE;
    Clock_construct(&fastReportTimeoutClock, fastReportTimeoutCallback, 1, &clkParams);
    fastReportTimeoutClockHandle = Clock_handle(&fastReportTimeoutClock);

    /* Create the node task */
    Task_Params_init(&nodeTaskParams);
    nodeTaskParams.stackSize = NODE_TASK_STACK_SIZE;
    nodeTaskParams.priority = NODE_TASK_PRIORITY;
    nodeTaskParams.stack = &nodeTaskStack;
    Task_construct(&nodeTask, nodeTaskFunction, &nodeTaskParams, NULL);
}

#ifdef COMMISSIONING

/*
 *  ======== gpioButtonFxn0 ========
 *  Callback function for the GPIO interrupt on Board_GPIO_BUTTON1.
 *
 *  Signaling userTask to initiate a connection with a
 *  concentrator.
 */
void gpioButtonFxn0(uint_least8_t index)
{
    GPIO_toggle(Board_GPIO_LED0);

    Event_post(commissionEventHandle, RADIO_EVENT_INIT);
}
static uint8_t connected;

static void userTask(UArg arg0, UArg arg1)
{
    UART_Handle uart;
    UART_Params uartParams;
    struct UARTPacket uartPacket;
    uint8_t pktSize;

    connected = 0;


    /* install Button callback */
    GPIO_setCallback(Board_GPIO_BUTTON0, gpioButtonFxn0);

    /* Enable interrupts */
    GPIO_enableInt(Board_GPIO_BUTTON0);

    UART_init();

    /* Create a UART with data processing off. */
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = 115200;

    uart = UART_open(Board_UART0, &uartParams);

    if (uart == NULL) {
        /* UART_open() failed */
        while (1);
    }

    struct UARTPacket test;
    test.flag = 0xF0F0F0F0;
    test.rssi = 56;
    strcpy(test.message, "welcome");

    uartWrite(uart, &test, sizeof(struct UARTPacket));

    while(1)
    {
        // Wait for UART packet read...
        uartRead(uart, &uartPacket, &pktSize);

        //switch (buffer.flaggor)
            //post radioTask...

        commissioningHandler(uart, )



        switch(uartPacket.flag)
        {
        case (readVar):
        {

        }

        case (dunnoVar & connected):
        {
        }

        default:
        {
            if(commisioningHandle == true )
                connected = 0xFF;
        }
        uint32_t cEvents = Event_pend(commissionEventHandle, 0, RADIO_EVENT_CONNECT_FAIL
                                              | RADIO_EVENT_CONNECT_SUCCESS | RADIO_EVENT_AUTHENTICATE
                                              | RADIO_EVENT_NETW_FULL | RADIO_EVENT_WRONG_PASSW
                                              | RADIO_EVENT_INIT, BIOS_WAIT_FOREVER);
        break;
        }
        if(uartPacket.flag & )
        commissionHandle(uart, uartPacket.flag);

        // wait for radio event

        // Wait for directions
        uint32_t cEvents = Event_pend(commissionEventHandle, 0, RADIO_EVENT_CONNECT_FAIL
                                      | RADIO_EVENT_CONNECT_SUCCESS | RADIO_EVENT_AUTHENTICATE
                                      | RADIO_EVENT_NETW_FULL | RADIO_EVENT_WRONG_PASSW
                                      | RADIO_EVENT_INIT, BIOS_WAIT_FOREVER);



        uartWrite(uart, )
        //UART_write() tillbaka till CC2650.


    }
}

void uartRead(UART_Handle uart, struct UARTPacket *data, uint8_t *dataLen)
{
    uint8_t i = 0;
    char input;
    char tmp_data[128];

    while(1)
    {
        UART_read(uart, &input, 1);
        *(tmp_data + i) = input;

        if(*(tmp_data + i) == '\0')
        {

            break;
        }
        else
            i++;
    }

    *dataLen = i;

    data->flag = (uint32_t) tmp_data[0];/*(tmp_data[0] << 24) | (tmp_data[1] << 16) |
                 (tmp_data[2] << 8) | (tmp_data[3]);*/

    memcpy(data->message, tmp_data + 5, *dataLen - 5);
}

void uartWrite(UART_Handle uart, struct UARTPacket *data, uint8_t dataLen)
{
    char *buffer;
    buffer = (char *) data;
    UART_write(uart, buffer, dataLen);
}

void commissioningHandler(UART_Handle uart)
{
    uint8_t     size, data;
    char        input;
    char        echo[2];
    struct UARTPacket uartPacket;

    NodeRadioTask_sendData((void *) data, 0, RADIO_EVENT_SEND_INIT_MSG);

    while(!connected)
    {
        uint32_t cEvents = Event_pend(commissionEventHandle, 0, RADIO_EVENT_CONNECT_FAIL
                                              | RADIO_EVENT_CONNECT_SUCCESS | RADIO_EVENT_AUTHENTICATE
                                              | RADIO_EVENT_NETW_FULL | RADIO_EVENT_WRONG_PASSW
                                              | RADIO_EVENT_INIT, BIOS_WAIT_FOREVER);

        /* If the user wants to connect this unit/node to a concentrator,
         * an InitPacket is broadcasted to concentrators nearby.
         */
        if (cEvents & RADIO_EVENT_INIT)
        {
            // Say hello to concentrator
            data = NODE_TYPE_BLE_ANNCE;
            NodeRadioTask_sendData((void *) data, 0, RADIO_EVENT_SEND_INIT_MSG);
        }

        /* This flag is set if:
         * a concentrator tells this node to attempt authentication.
         * an authentication attempt was made, but the password was wrong.
         */
        if (cEvents & RADIO_EVENT_AUTHENTICATE)
        {
            // If the previously entered password was wrong
            if (cEvents & RADIO_EVENT_WRONG_PASSW)
            {
                //UART_write(uart, skip2rows, sizeof(skip2rows));
                // Tell user that the password was wrong and to try again
                //UART_write(uart, wrong_pass, sizeof(wrong_pass));

                //UART_write(uart, enter_pass, sizeof(enter_pass));

                // Set UART packet flag wrong password
                uartPacket.flag = RADIO_EVENT_WRONG_PASSW;

                // Send UART packet to CC2650
                uartWrite(uart, uartPacket, 5);
            }
            else
            {
                uartPacket.flag = RADIO_EVENT_AUTHENTICATE;

                // Tell user to enter password
                uartWrite(uart, &uartPacket, 5);
            }

            input = ' ';
            int i = 0;

            // Wait for password entry
            uartRead(uart, &uartPacket, &size);



            /*while ((i < PASSWORD_LENGTH) && (input != 13))
            {
                UART_read(uart, &input, 1);

                if(input == 13)
                {
                    echo[0] = '\r';
                    echo[1] = '\n';
                    size = 2;
                }
                else
                {
                    passw[i] = input;
                    echo[0] = input;
                    size = 1;
                    i++;
                }

                UART_write(uart, &echo, size);
            }*/

            // Add null termination
            //passw[i] = '\0';
            //i++;


            // Send the password to concentrator
            NodeRadioTask_sendData((void *) uartPacket.message, size, RADIO_EVENT_SEND_PASSW);
        }

        /* If the network is full:
         * The user will be able to replace one unit/node in the network.
         */
        if (cEvents & RADIO_EVENT_NETW_FULL)
        {
            uartPacket.flag = RADIO_EVENT_NETW_FULL;

            uartWrite(uart, &uartPacket, 5);

            /*UART_write(uart, netw_full, sizeof(netw_full));

            UART_read(uart, &input, 1);
            UART_write(uart, &input, 1);*/

            /*do {
                if(input == 'y' || input == 'Y')
                {
                    /* Alert concentrator to send a list of existing nodes
                     * to choose which one to replace
                     */
                    //  //  EDIT
                    /************************/
                    //UART_write(uart, skip2rows, sizeof(skip2rows));

                //}
                //else if(input == 'n' || input == 'N')
                //{
                    /* Do nothing */
                    //UART_write(uart, skip2rows, sizeof(skip2rows));

              //  }
            //} while(input != 'y' || input != 'Y' || input != 'n' || input != 'N');

        }

        /* If this unit/node already was known by the network
         * or
         * if connection to the network succeeded,
         * post connection success to nodeTaskFunction
         */
        if (cEvents & (RADIO_EVENT_CONNECT_SUCCESS | NODE_ALREADY_KNOWN))
        {
            // Alert user that connection is established
            UART_write(uart, connected, sizeof(connected));

            connected = 1;

            //Event_post(connectEventHandle, RADIO_EVENT_CONNECT_SUCCESS);
        }

        /* If connection to network failed, tell the user
         */
        if (cEvents & RADIO_EVENT_CONNECT_FAIL)
        {
            /* Tell user that connection has failed and ask if
             * user wants to try again
             */
            UART_write(uart, connection_failed, sizeof(connection_failed));
            /* . . . */
            break;

        }
    }
}


#endif //COMMISSIONING


/*
 *  ======== gpioButtonFxn1 ========
 *  Callback function for the GPIO interrupt on Board_GPIO_BUTTON1.
 */
int count;

void gpioButtonFxn1(uint_least8_t index)
{
    count = 0;

    /* Clear the GPIO interrupt and toggle an LED */
    GPIO_toggle(Board_GPIO_LED1);


    if (count++ == 100) {
        count = 0;
    }

    Event_post(nodeEventHandle, NODE_EVENT_NEW_ADC_VALUE);
}

static void nodeTaskFunction(UArg arg0, UArg arg1)
{
    /* install Button callback */
    GPIO_setCallback(Board_GPIO_BUTTON1, gpioButtonFxn1);

    /* Enable interrupts */
    GPIO_enableInt(Board_GPIO_BUTTON1);


#ifdef COMMISSIONING

    //*******************************************************//
    //    Wait for established connection to concentrator    //
    //*******************************************************//

    uint32_t cEvents = Event_pend(connectEventHandle, 0, RADIO_EVENT_CONNECT_SUCCESS, BIOS_WAIT_FOREVER);
#endif //COMMISSIONING


    /* Open LED pins */
    //ledPinHandle = PIN_open(&ledPinState, pinTable);
    /*if (!ledPinHandle)
    {
        System_abort("Error initializing board 3.3V domain pins\n");
    }*/

    /* Start the SCE ADC task with 1s sample period and reacting to change in ADC value. */
    //SceAdc_init(0x00010000, NODE_ADCTASK_REPORTINTERVAL_FAST, NODE_ADCTASK_CHANGE_MASK);
    //SceAdc_registerAdcCallback(adcCallback);
    //SceAdc_start();

    /* setup timeout for fast report timeout */
    Clock_setTimeout(fastReportTimeoutClockHandle,
            NODE_ADCTASK_REPORTINTERVAL_FAST_DURIATION_MS * 1000 / Clock_tickPeriod);

    /* start fast report and timeout */
    Clock_start(fastReportTimeoutClockHandle);


    /*buttonPinHandle = PIN_open(&buttonPinState, buttonPinTable);
    if (!buttonPinHandle)
    {
        System_abort("Error initializing button pins\n");
    }*/


    /* Setup callback for button pins */
    /*if (PIN_registerIntCb(buttonPinHandle, &buttonCallback) != 0)
    {
        System_abort("Error registering button callback function");
    }*/

    while(1) {
        /* Wait for event */
        uint32_t events = Event_pend(nodeEventHandle, 0, NODE_EVENT_ALL, BIOS_WAIT_FOREVER);


        /* If new ADC value, send this data */
        if (events & NODE_EVENT_NEW_ADC_VALUE) {

            /* Toggle activity LED */
            //PIN_setOutputValue(ledPinHandle, NODE_ACTIVITY_LED,!PIN_getOutputValue(NODE_ACTIVITY_LED));

            GPIO_write(Board_PIN_LED1, 1);

            txData = 2;

            /* Send ADC value to concentrator */
            NodeRadioTask_sendData((void *) &txData, 2, RADIO_EVENT_SEND_DATA);
        }
    }
}

/*void adcCallback(uint16_t adcValue)
{
    /* Save latest value */
/*    latestAdcValue = adcValue;

    /* Post event */
/*    Event_post(nodeEventHandle, NODE_EVENT_NEW_ADC_VALUE);
}*/

/*
 *  ======== buttonCallback ========
 *  Pin interrupt Callback function board buttons configured in the pinTable.
 */
/*void buttonCallback(PIN_Handle handle, PIN_Id pinId)
{
    /// EDIT
    if(PIN_getInputValue(Board_PIN_BUTTON1) == 1)
        txData = 2;

    //PIN_setOutputValue(pinHandle, Board_PIN_LED1,!PIN_getOutputValue(Board_PIN_LED1));

    //CPUdelay(8000*50);

    //PIN_setOutputValue(pinHandle, Board_PIN_LED1,!PIN_getOutputValue(Board_PIN_LED1));

    //Event_post(nodeEventHandle, NODE_EVENT_NEW_ADC_VALUE);

    /* Debounce logic, only toggle if the button is still pushed (low) */
    //CPUdelay(8000*50);


    /*if (PIN_getInputValue(Board_PIN_BUTTON0) == 0)
    {
        //start fast report and timeout
        SceAdc_setReportInterval(NODE_ADCTASK_REPORTINTERVAL_FAST, NODE_ADCTASK_CHANGE_MASK);
        Clock_start(fastReportTimeoutClockHandle);
    }
}*/

void fastReportTimeoutCallback(UArg arg0)
{
    //stop fast report
    SceAdc_setReportInterval(NODE_ADCTASK_REPORTINTERVAL_SLOW, NODE_ADCTASK_CHANGE_MASK);
}
