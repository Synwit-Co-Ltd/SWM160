#include "serial_port.h"
#include "circle_queue.h"
#include "SWM160.h"

#define UART_IF_RXIF(UART)		(UART->BAUD & UART_BAUD_RXIF_Msk) != 0
#define UART_IF_TXIF(UART)		(UART->BAUD & UART_BAUD_TXIF_Msk) != 0

static CircleQueue_t TxQue;
static CircleQueue_t RxQue;

static void SerialInit(uint32_t baudrate)
{
	UART_InitStructure UART_initStruct;
	
	PORT_Init(PORTB, PIN11, PORTB_PIN11_UART0_RX, 1);	//GPIOB.11配置为UART0输入引脚
	PORT_Init(PORTB, PIN12, PORTB_PIN12_UART0_TX, 0);	//GPIOB.12配置为UART0输出引脚
	
	UART_initStruct.Baudrate = baudrate;
	UART_initStruct.DataBits = UART_DATABIT_8;
	UART_initStruct.Parity = UART_PARITY_NONE;
	UART_initStruct.StopBits = UART_STOPBIT_1;
	UART_initStruct.RXThreshold = 0;
	UART_initStruct.RXThresholdIEn = 1;
	UART_initStruct.TXThreshold = 3;
	UART_initStruct.TXThresholdIEn = 0;
	UART_initStruct.TimeoutTime = 10;
	UART_initStruct.TimeoutIEn = 0;
 	UART_Init(UART0, &UART_initStruct);
	
	NVIC_EnableIRQ(UART0_IRQn);
	
	UART_Open(UART0);
}

void SPort_Init(uint32_t baudrate)
{
	halIntState_t int_state;

	HAL_ENTER_CRITICAL_SECTION(int_state);

	SerialInit(baudrate);
	
	Queue_Init(&TxQue);
	Queue_Init(&RxQue);
	
	HAL_EXIT_CRITICAL_SECTION(int_state);
}

static void SPort_OnRxByte(uint8_t rx_byte)
{
	halIntState_t x;

	HAL_ENTER_CRITICAL_SECTION(x);
	
	Queue_Put(&RxQue, rx_byte);

	HAL_EXIT_CRITICAL_SECTION(x);
}

static bool SPort_GetTxByte(uint8_t *tx_byte)
{
	bool flag;
	halIntState_t x;

	HAL_ENTER_CRITICAL_SECTION(x);
	flag = Queue_Get(&TxQue, tx_byte);
	HAL_EXIT_CRITICAL_SECTION(x);

	return flag;
}

static void SPort_OnTxFin(void)
{
	halIntState_t x;

	HAL_ENTER_CRITICAL_SECTION(x);
	UART_INTTXThresholdDis(CUR_UART);
	HAL_EXIT_CRITICAL_SECTION(x);
}

bool SPort_GetByte(uint8_t *ch)
{
	halIntState_t x;
	bool flag = false;	

	if (!Queue_IfEmpty(&RxQue))
	{
		HAL_ENTER_CRITICAL_SECTION(x);
		flag = Queue_Get(&RxQue, ch);
		HAL_EXIT_CRITICAL_SECTION(x);
	}

	return flag;
}

bool SPort_PutByte(uint8_t ch)
{
	return SPort_Send(&ch, 1);
}

bool SPort_Send(uint8_t* buf, uint16_t len)
{
	halIntState_t x;
	
	if (len  > 0)
	{
		while (len--)
		{
			HAL_ENTER_CRITICAL_SECTION(x);
			Queue_Put(&TxQue, *buf++);
			HAL_EXIT_CRITICAL_SECTION(x);
		}

		HAL_ENTER_CRITICAL_SECTION(x);
		UART_INTTXThresholdEn(CUR_UART);
		HAL_EXIT_CRITICAL_SECTION(x);
	}

	return true;
}

void UART0_Handler(void)
{
	if (UART_IF_RXIF(CUR_UART))
	{
		uint32_t data;
		
		if (UART_ReadByte(CUR_UART, &data) == 0)
			SPort_OnRxByte((uint8_t)data);
	}

	if (UART_IF_TXIF(CUR_UART))
	{
		uint8_t ch;
		
		if (SPort_GetTxByte(&ch))
			UART_WriteByte(CUR_UART, ch);
		else
			SPort_OnTxFin();
	}
}

