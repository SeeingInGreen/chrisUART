// chrisUART.h - Simple UART config/usage library for Tiva-C microcontrollers
// Christopher Green - Created 2/10/2017

#ifndef CHRISUART_H
#define CHRISUART_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>				
#include <stdarg.h>				// Variable argument list manipulation
#include <string.h>				// C-string manipulation functions
#include "inc/hw_memmap.h"		// Peripheral memory mappings.
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"	
#include "driverlib/uart.h"		// UART configuration
	
// Constants and global configuration parameters
#define UART_BUF_SIZE 255		// Size of the send buffer, configure to your liking

void initUart(uint32_t baud, void (*cmdHandler)(void));	// Init @ baud with 8-bit data, one stop, no parity
void chrisPrintf(char*, ...);	// Printf over UART RX
void uartRXIntHandler();	




#endif /* CHRISUART_H */