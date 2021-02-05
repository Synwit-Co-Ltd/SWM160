#include "SWM160.h"

#include <string.h>

#define SLV_ADDR  0x6C

char mst_txbuff[4] = {0x37, 0x55, 0xAA, 0x78};
char mst_rxbuff[4] = {0};
char slv_txbuff[4] = {0};
char slv_rxbuff[4] = {0};

volatile uint32_t slv_rxindx = 0;
volatile uint32_t slv_txindx = 0;

void SerialInit(void);
void I2CMstInit(void);
void I2CSlvInit(void);

int main(void)
{
	uint32_t i;
	uint8_t ack;
	
	SystemInit();
	
	SerialInit();
	
	I2CMstInit();
	I2CSlvInit();
	
	while(1==1)
	{
		/*************************** Master Write ************************************/
		slv_rxindx = 0;
		
		ack = I2C_Start(I2C0, (SLV_ADDR << 1) | 0);
		if(ack == 0)
		{
			printf("Slave send NACK for address\r\n");
			goto nextloop;
		}
		
		for(i = 0; i < 4; i++)
		{
			ack = I2C_Write(I2C0, mst_txbuff[i]);
			if(ack == 0)
			{
				printf("Slave send NACK for data\r\n");
				goto nextloop;
			}
		}
		
		I2C_Stop(I2C0);
		
		printf("Master Send %X %X %X %X\r\n", mst_txbuff[0], mst_txbuff[1], mst_txbuff[2], mst_txbuff[3]);
		
		
		/********************************** Master Read *******************************/
		slv_txindx = 0;
		memcpy(slv_txbuff, slv_rxbuff, 4);
		
		ack = I2C_Start(I2C0, (SLV_ADDR << 1) | 1);
		if(ack == 0)
		{
			printf("Slave send NACK for address\r\n");
			goto nextloop;
		}
		
		for(i = 0; i < 3; i++)
		{
			mst_rxbuff[i] = I2C_Read(I2C0, 1);
		}
		mst_rxbuff[i] = I2C_Read(I2C0, 0);
		
		printf("Master Read %X %X %X %X\r\n", mst_rxbuff[0], mst_rxbuff[1], mst_rxbuff[2], mst_rxbuff[3]);
		
		if((mst_txbuff[0] == mst_rxbuff[0]) && (mst_txbuff[1] == mst_rxbuff[1]) && (mst_txbuff[2] == mst_rxbuff[2]) && (mst_txbuff[3] == mst_rxbuff[3]))
			printf("Success\r\n");
		else
			printf("Fail\r\n");

nextloop:
		I2C_Stop(I2C0);
		for(i = 0; i < 4000000; i++) ;
	}
}


void I2CMstInit(void)
{
	I2C_InitStructure I2C_initStruct;
	
	PORT_Init(PORTC, PIN12, PORTC_PIN12_I2C0_SCL, 1);	//GPIOC.12配置为I2C0 SCL引脚
	PORTC->OPEND |= (1 << PIN12);						//开漏输出
	PORTC->PULLU |= (1 << PIN12);						//使能上拉
	PORT_Init(PORTC, PIN13, PORTC_PIN13_I2C0_SDA, 1);	//GPIOC.13配置为I2C0 SDA引脚
	PORTC->OPEND |= (1 << PIN13);						//开漏输出
	PORTC->PULLU |= (1 << PIN13);						//使能上拉
	
	I2C_initStruct.Master = 1;
	I2C_initStruct.Addr7b = 1;
	I2C_initStruct.MstClk = 10000;
	I2C_initStruct.MstIEn = 0;
	I2C_Init(I2C0, &I2C_initStruct);
	
	I2C_Open(I2C0);
}


void I2CSlvInit(void)
{
	I2C_InitStructure I2C_initStruct;
	
	PORT_Init(PORTC, PIN0, PORTC_PIN0_I2C1_SCL, 1);		//GPIOC.0配置为I2C1 SCL引脚
	PORTC->OPEND |= (1 << PIN0);						//开漏输出
	PORTC->PULLU |= (1 << PIN0);						//使能上拉
	PORT_Init(PORTC, PIN1, PORTC_PIN1_I2C1_SDA, 1);		//GPIOC.1配置为I2C1 SDA引脚
	PORTC->OPEND |= (1 << PIN1);						//开漏输出
	PORTC->PULLU |= (1 << PIN1);						//使能上拉
	
	I2C_initStruct.Master = 0;
	I2C_initStruct.Addr7b = 1;
	I2C_initStruct.SlvAddr = SLV_ADDR;
	I2C_initStruct.SlvSTADetIEn = 1;
	I2C_initStruct.SlvRdReqIEn = 0;
	I2C_initStruct.SlvWrReqIEn = 1;
	I2C_initStruct.SlvTxEndIEn = 1;
	I2C_initStruct.SlvRxEndIEn = 1;
	I2C_initStruct.SlvSTODetIEn = 1;
	I2C_Init(I2C1, &I2C_initStruct);
	
	I2C_Open(I2C1);
}


void I2C1_Handler(void)
{
	if(I2C1->SLVIF & I2C_SLVIF_STADET_Msk)				//收到起始位
	{
		I2C1->SLVIF = (1 << I2C_SLVIF_STADET_Pos);
		
		I2C1->SLVTX = slv_txbuff[0];
		slv_txindx = 1;
	}
	else if(I2C1->SLVIF & I2C_SLVIF_STODET_Msk)			//收到停止位
	{
		I2C1->SLVIF = (1 << I2C_SLVIF_STODET_Pos);
	}
	else if(I2C1->SLVIF & I2C_SLVIF_WRREQ_Msk)			//收到写请求
	{
		I2C1->SLVIF = (1 << I2C_SLVIF_WRREQ_Pos);
		
		slv_rxindx = 0;
		I2C1->SLVCR |= (1 << I2C_SLVCR_ACK_Pos);
	}
	else if(I2C1->SLVIF & I2C_SLVIF_RXEND_Msk)			//接收完成
	{
		I2C1->SLVIF = (1 << I2C_SLVIF_RXEND_Pos);
		
		slv_rxbuff[slv_rxindx] = I2C1->SLVRX;
		if(slv_rxindx < 3) slv_rxindx++;
	}
	else if(I2C1->SLVIF & I2C_SLVIF_RDREQ_Msk)			//收到读请求
	{		
		I2C1->SLVIF = (1 << I2C_SLVIF_RDREQ_Pos);
		
		//收到读请求后会立即把SLVTX中的值发送出去，而不是等待软件写入后再发送；所以将第一个数据写入SLVTX只能提前到“收到起始位”
	}
	else if(I2C1->SLVIF & I2C_SLVIF_TXEND_Msk)			//发送完成
	{
		I2C1->SLVIF = (1 << I2C_SLVIF_TXEND_Pos);
		
		I2C1->SLVTX = slv_txbuff[slv_txindx];
		if(slv_txindx < 3) slv_txindx++;
	}
}


void SerialInit(void)
{
	UART_InitStructure UART_initStruct;
	
	PORT_Init(PORTB, PIN11, PORTB_PIN11_UART0_RX, 1);	//GPIOB.11配置为UART0输入引脚
	PORT_Init(PORTB, PIN12, PORTB_PIN12_UART0_TX, 0);	//GPIOB.12配置为UART0输出引脚
 	
	UART_initStruct.Baudrate = 57600;
	UART_initStruct.DataBits = UART_DATABIT_8;
	UART_initStruct.Parity = UART_PARITY_NONE;
	UART_initStruct.StopBits = UART_STOPBIT_1;
	UART_initStruct.RXThresholdIEn = 0;
	UART_initStruct.TXThresholdIEn = 0;
	UART_initStruct.TimeoutIEn = 0;
 	UART_Init(UART0, &UART_initStruct);
	UART_Open(UART0);
}


/****************************************************************************************************************************************** 
* 函数名称: fputc()
* 功能说明: printf()使用此函数完成实际的串口打印动作
* 输    入: int ch		要打印的字符
*			FILE *f		文件句柄
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
int fputc(int ch, FILE *f)
{
	UART_WriteByte(UART0, ch);
	
	while(UART_IsTXBusy(UART0));
 	
	return ch;
}
