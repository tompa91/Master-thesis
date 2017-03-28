/*
 * uartecho.h
 *
 *  Created on: Mar 23, 2017
 *      Author: Tom
 */

#include <xdc/std.h>

void UARTread(char *buffer);

void UARTwrite(char *buffer);


void UARTtask1_Init(void);
void UARTtask2_Init(void);

Void UARTtask1(UArg arg0, UArg arg1);
Void UARTtask2(UArg arg0, UArg arg1);

Event_Struct uartEvent;
Event_Handle uartEventHandle;


