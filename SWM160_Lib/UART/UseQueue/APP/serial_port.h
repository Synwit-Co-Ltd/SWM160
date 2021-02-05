#include "define.h"
#include <stdint.h>
#include <stdbool.h>

#ifndef __SERIAL_PORT__
#define __SERIAL_PORT__

// hardware config
#define CUR_UART			UART0
#define UART_PORT		PORTA
#define UART_TX_PIN		PIN13
#define UART_RX_PIN		PIN12
#define UART_IRQ_NO		IRQ0_15_UART0

void SPort_Init(uint32_t baudrate);

bool SPort_Send(uint8_t *buf, uint16_t len);

bool SPort_Receive(uint8_t *buf, uint16_t len);

bool SPort_PutByte(uint8_t ch);

bool SPort_GetByte(uint8_t *ch);

#endif	/* __SERIAL_PORT__ */

