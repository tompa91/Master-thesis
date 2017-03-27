/*
 * uartBridge.c
 *
 *  Created on: Mar 20, 2017
 *      Author: Tom
 */

#include "uartBridge.h"
#include "ProjectZero.h"

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>
//#include "C:\ti\tirex-content\tirtos_cc13xx_cc26xx_2_21_00_06\products\bios_6_46_01_37\packages\ti\targets\std.h"
//#include "C:\ti\tirex-content\xdctools_3_31_01_33_core\packages\xdc\std.h"

/* Example/Board Header files */
#include "Board.h"

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

/* TI-RTOS Header files */
#include <ti/drivers/PIN.h>
#include <ti/drivers/UART.h>

/* Example/Board Header files */
#include <stdint.h>
#include <string.h>

#define writeMode
#define TASKSTACKSIZE     768

Task_Struct task0Struct;
Char task0Stack[TASKSTACKSIZE];
/*
PIN_State ledPinState;

PIN_Config ledPinTable[] = {
  Board_LED0 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
  Board_LED1 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
  PIN_TERMINATE
};
*/

void uartFxn(uint8_t mode, uint8_t *data, uint8_t dataLen)
{
#if 0
    PIN_Handle ledPinHandle;

    /* Open LED pins */
    ledPinHandle = PIN_open(&ledPinState, ledPinTable);
    if(!ledPinHandle) {
        System_abort("Error initializing board LED pins\n");
    }
#endif
    //char input;
    UART_Handle uart;
    UART_Params uartParams;

    /* Create a UART with data processing off. */
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = 9600;
    uart = UART_open(Board_UART0, &uartParams);

    if (uart == NULL) {
        System_abort("Error opening the UART");
    }

    *(data+dataLen) = '\0';
    dataLen++;

    if(mode == 0)
    {
    }

    else if(mode == 1)
    {
        int i;

        for(i = 0; i < dataLen; i++)
        {
            UART_write(uart, (data+i), 1);
        }

        PIN_setOutputValue(ledPinHandle, Board_LED0, 1);    //Red


        if(strcmp((char*)data,"green") == 0)
        {
            PIN_setOutputValue(ledPinHandle, Board_LED1, 1);    //Green
        }

    }

    /* Loop forever echoing */

/*
#ifdef readMode
    UART_read(uart, &input, sizeof(input));

    while (1)
    {
        if(input == 'g')
        {
            PIN_setOutputValue(ledPinHandle, Board_LED1, 1);    //Green
            PIN_setOutputValue(ledPinHandle, Board_LED0, 0);    //Red
        }
        else if(input == 'r')
        {
            PIN_setOutputValue(ledPinHandle, Board_LED1, 0);    //Green
            PIN_setOutputValue(ledPinHandle, Board_LED0, 1);    //Red
        }

        UART_read(uart, input, sizeof(input));
    }
#endif
#ifdef writeMode
    char inputG = 'g';
    char inputR = 'r';

    UART_write(uart, &inputG, dataLen);


    while (1)
    {
        UART_write(uart, &inputG, sizeof(input));
        PIN_setOutputValue(ledPinHandle, Board_LED1, 1);    //Green
        PIN_setOutputValue(ledPinHandle, Board_LED0, 0);    //Red
        Task_sleep(25000);

        UART_write(uart, &inputR, sizeof(input));
        PIN_setOutputValue(ledPinHandle, Board_LED1, 0);    //Green
        PIN_setOutputValue(ledPinHandle, Board_LED0, 1);    //Red
        Task_sleep(25000);
    }

#endif
*/
}
