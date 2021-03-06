#include "ADS1112.h"
#ifdef SimI2C
#include "SimI2C.h"
#endif
u16_wf ADS1112_Result;
_ADS1112_Status ADS1112_Status;
#ifdef SimI2C
void ADS1112_Init(void)
{
	SimI2C_Init();
}
uint8_t ADS1112_Read(void)
{
	uint8_t ErrTimes=ADS1112_RetryCount;	
	uint8_t bRight=0;
	while(ErrTimes--)
	{
		SimI2C_Start();		
		SimI2C_SendByte(ADS1112_ADDR_R);//读
		if(SimI2C_RecAck())
			continue;
		ADS1112_Result.u8H=SimI2C_ReadByte();
		SimI2C_Ack();
		ADS1112_Result.u8L=SimI2C_ReadByte();
		SimI2C_Ack();
		ADS1112_Status.AllFlag=SimI2C_ReadByte();
		SimI2C_Ack();		
		//SimI2C_NoAck();
		bRight=1;
		break;
	}
	SimI2C_Stop();
	return bRight;
}
uint8_t ADS1112_Write()
{
	uint8_t ErrTimes=ADS1112_RetryCount;
	uint8_t bRight=0;	
	while(ErrTimes--)
	{
		SimI2C_Start();		
		SimI2C_SendByte(ADS1112_ADDR_W);//写
		if(SimI2C_RecAck())
			continue;//无应答返回到循环
		SimI2C_SendByte(ADS1112_Status.AllFlag);
		if(SimI2C_RecAck())
			continue;		
		bRight=1;
		break;
	}
	SimI2C_Stop();
	//wfDelay_us(5);
	return bRight;
}
#endif

