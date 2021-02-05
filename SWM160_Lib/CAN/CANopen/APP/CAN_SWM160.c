#include "SWM160.h"

#include "TestSlave.h"

static Message RxMessage;

volatile uint8_t g_ucCanRxFlag = 0;

void can_slave_init(void)
{
	CAN_InitStructure CAN_initStruct;
	
    PORT_Init(PORTB, PIN0, PORTB_PIN0_CAN_RX, 1);	//GPIOB.0配置为CAN输入引脚
    PORT_Init(PORTB, PIN1, PORTB_PIN1_CAN_TX, 0);	//GPIOB.1配置为CAN输出引脚

    CAN_initStruct.Mode = CAN_MODE_SELFTEST;		//自测模式下TX、RX要连接在一起
    CAN_initStruct.CAN_BS1 = CAN_BS1_6tq;
    CAN_initStruct.CAN_BS2 = CAN_BS2_5tq;
    CAN_initStruct.CAN_SJW = CAN_SJW_4tq;
    CAN_initStruct.Baudrate = 100000;
    CAN_initStruct.FilterMode = CAN_FILTER_32b;
    CAN_initStruct.FilterMask32b = 0xFFFFFFFF;
    CAN_initStruct.FilterCheck32b = 0xFFFFFFFF;
    CAN_initStruct.RXNotEmptyIEn = 1;
    CAN_initStruct.RXOverflowIEn = 0;
    CAN_initStruct.ArbitrLostIEn = 0;
    CAN_initStruct.ErrPassiveIEn = 0;
    CAN_Init(CAN, &CAN_initStruct);

    CAN_Open(CAN);
}

void can_recv_thread(void)
{    
    TIMR_INTDis(TIMR3);

	canDispatch(&TestSlave_Data, &RxMessage);

    TIMR_INTEn(TIMR3);
}

uint8_t canSend(CAN_PORT notused, Message *m)
{
    if(m->rtr) CAN_TransmitRequest(CAN, CAN_FRAME_STD, m->cob_id, 0);
    else       CAN_Transmit(CAN, CAN_FRAME_STD, m->cob_id, m->data, m->len, 0);
	
	while(CAN_TXComplete(CAN) == 0);

    return 0xFF;
}

void CAN_Handler(void)
{
    uint32_t i;
    CAN_RXMessage rxMessage;

    if(CAN_INTRXNotEmptyStat(CAN) != 0)
    {
        CAN_Receive(CAN, &rxMessage);
		
        RxMessage.cob_id = (UNS16)rxMessage.id;
		
        if(rxMessage.remote == 1) RxMessage.rtr = 1;
        else                      RxMessage.rtr = 0;

        RxMessage.len = (UNS8)rxMessage.size;
		
        for(i = 0; i < RxMessage.len; i++) RxMessage.data[i] = rxMessage.data[i];

        g_ucCanRxFlag = 1;
    }
}
