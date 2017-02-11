// chrisUART.c - Simple UART config/usage library for Tiva-C microcontrollers
// Christopher Green - Created 2/10/2017

#include "chrisUART.h"

// Init UART0 @ baud with 8-bit data, one stop, no parity, FIFO mode
// Uses pins PA0 and PA1
// cmdHandler is the ISR that handles receiving from the UART buffer and processing comands
void initUart(uint32_t baud, void (*cmdHandler)(void)){
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), baud, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    UARTFIFOEnable(UART0_BASE);                                         // Enable queue for RX

    UARTIntEnable(UART0_BASE, (UART_INT_RX | UART_INT_RT));             // Enable interrupt-triggering on reception of UART characters
    UARTIntRegister(UART0_BASE, (cmdHandler));		                    // Attach handler function to UART interrupts
	UARTEnable(UART0_BASE);


}

// printf over UART TX - This still doesn't work perfectly
void chrisPrintf(char* str, ...){
	va_list argPtr;
    va_start(argPtr, str);

    int finalLen = 0;
    int inputLen = strlen(str);
    char print_buf [UART_BUF_SIZE];
    if(strlen(str) < (UART_BUF_SIZE - 1)){
        finalLen = vsnprintf(print_buf, UART_BUF_SIZE, str, argPtr);
    }
    else{
        snprintf(print_buf, UART_BUF_SIZE, "Input data too large for buffer!\r\n");
    }
    int i;
    if(finalLen == 0){
            UARTCharPut(UART0_BASE, 'E');
        }
    for(i = 0; i < finalLen; i++){
        UARTCharPut(UART0_BASE, print_buf[i]);
    }
    va_end(argPrt);
}

