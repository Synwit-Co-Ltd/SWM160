#include "mb.h"
#include "mbport.h"


BOOL xMBPortSerialInit(UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity)
{
    uint8_t dataBits, parity;
	UART_InitStructure UART_initStruct;

    switch (ucDataBits) {
    case 8:
        dataBits = UART_DATABIT_8;
        break;

    case 9:
        dataBits = UART_DATABIT_9;
        break;

    default:
        return FALSE;
    }

    switch (eParity) {
    case MB_PAR_NONE:
        parity = UART_PARITY_NONE;
        break;

    case MB_PAR_EVEN:
        parity = UART_PARITY_EVEN;
        break;

    case MB_PAR_ODD:
        parity = UART_PARITY_ODD;
        break;

    default:
        return FALSE;
    }
	
    PORT_Init(PORTB, PIN9, PORTB_PIN9_UART1_RX, 1);	//GPIOB.9 配置为UART1输入引脚
    PORT_Init(PORTB, PIN8, PORTB_PIN8_UART1_TX, 0);	//GPIOB.8 配置为UART1输出引脚
	
    UART_initStruct.Baudrate = ulBaudRate;
    UART_initStruct.DataBits = dataBits;
    UART_initStruct.Parity = parity;
	UART_initStruct.StopBits = UART_STOPBIT_1;
    UART_initStruct.RXThreshold = 0;
	UART_initStruct.RXThresholdIEn = 1;
	UART_initStruct.TXThreshold = 0;
	UART_initStruct.TXThresholdIEn = 0;
	UART_initStruct.TimeoutTime = 10;
	UART_initStruct.TimeoutIEn = 0;
 	UART_Init(UART1, &UART_initStruct);

	UART_Open(UART1);
	
    return TRUE;
}

void vMBPortSerialClose(void)
{
     
}

void vMBPortSerialEnable(BOOL xRxEnable, BOOL xTxEnable)
{
    if(xRxEnable)
    {
        UART_INTRXThresholdEn(UART1);
    }
    else
    {
        UART_INTRXThresholdDis(UART1);
    }

    if(xTxEnable)
    {
        UART_INTTXThresholdEn(UART1);
    }
    else
    {
        UART_INTTXThresholdDis(UART1);
    }
}

BOOL xMBPortSerialPutByte(CHAR ucByte)
{
    UART_WriteByte(UART1, ucByte);
    return TRUE;
}

BOOL xMBPortSerialGetByte(CHAR * pucByte)
{
    UART_ReadByte(UART1, (uint32_t *)pucByte);
    return TRUE;
}

void UART1_Handler( void )
{
    if(UART_INTRXThresholdStat(UART1))
    {
        pxMBFrameCBByteReceived();
    }

    if(UART_INTTXThresholdStat(UART1))
    {
        pxMBFrameCBTransmitterEmpty();
    }
}
