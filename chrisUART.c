// chrisUART.c - Simple UART config/usage library for Tiva-C microcontrollers
// Christopher Green - Created 2/10/2017

#include "chrisUART.h"

// Init UART0 @ baud with 8-bit data, one stop, no parity
// Uses pins PA0 and PA1
// cmdHandler(char*, int) is the function which handles whole-word commands
void initUart(uint32_t baud, void (*cmdHandler)(char*, int)){ 
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), baud, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
	UARTIntRegister(UART0_BASE, &uartRXIntHandler(&cmdHandler));		// Attach handler function to UART interrupts
	UARTIntEnable(UART0_BASE, UART_INT_RX);								// Enable interrupts on reception of UART characters
}

// printf over UART TX
void chrisPrintf(char*, ...){
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

// Function for handling UART RX-triggered interrupts 
void uartRXIntHandler(void (*cmdHandler)(char*, int)){
	uint16_t buf_index = 0;
	char rx_buf[UART_BUF_SIZE];
	UARTIntClear(UART0_BASE, UART_INT_RX);
	while(UARTCharsAvail(UART0_BASE){
		if(index < UART_BUF_SIZE){
			rx_buf[buf_index] = UARTCharGetNonBlocking(UART0_BASE);
			// I'm not sure if we actually need this or not, blocking call
			SysCtlDelay(SysCtlClockGet() / (1000*3)); // ~1ms
			buf_index++;
		}
	}
	cmdHandler(rx_buf, buf_index); // Pass the command and the length to the command handler function
}

