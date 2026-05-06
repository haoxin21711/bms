/******************** (C) BOBO   ********************************
 * �ļ���  ��main.c
 * ����    ����Ҫ�����BMS��ؼ��ͱ���
 * ��汾  ��V3.50
 * ����    ��BOBO
 * �汾����: 2019-04-12
 * ���Է�ʽ��J-Link
**********************************************************************************/

// //ͷ�ļ�
// #include "stm32f10x.h"
// #include "led.h"
// #include "wdg.h"
// #include "SYSTICK.h"
// #include "usart.h"
// #include "usart2.h"
// #include "i2c.h"
// #include "i2c1.h"
// #include "i2c2.h"
// #include "BQ76930.h"
// #include "IO_CTRL.h"
// #include <stdio.h>
// #include "math.h"
// #include "timer.h"
// #include "stm32f10x_it.h"
// #include "w25qxx.h"
// #include "spi.h"
// #include "can.h"
// /**
//   * @file   main
//   * @brief  Main program.
//   * @param  None
//   * @retval None
//   */
	
// /* �洢����Flashҳ�׵�ַ 60K Ϊ�׵�ַ���������������Ŀռ���60K��С��103C8T6��FLASH�Ĵ�С��62K*��ÿ����ַ����һҳ��Ҳ����+0X802*/
//     uint32_t   Battery_ADR     =  0x08007800 ;  
//     uint32_t   Temp_up         =  0x08007C00 ; 		
		
 
		 
// 	void Write_Flash(uint32_t Add,unsigned int Data)
// 	{	
// 		  FLASH_Unlock();		/* ÿ�β���Flash������ʱ���Ƚ��� */
//       FLASH_ErasePage(Add);		  /* ����ҳ */		
// 		  FLASH_ProgramWord(Add,Data);   /* д16λ���� */
// 		  FLASH_Lock();							   /* ���� */		  
// 	}
	
// unsigned int Read_Flash(uint32_t Add)
// 	{	
// 		unsigned int Data;
// 		Data=*(vu16*)(Add);	 /* ��ȡ��ַ�е�16λ���� */ 
// 		return Data;
// 	}		
// unsigned char SEND_readparameter_TO_SHANGWEIJI[500]={0XAA,0X88};
	

// extern unsigned char ucUSART1_ReceiveDataBuffer[];
// unsigned char BMS_DATA_FLAG;
// void RECEICE_DATA_DEAL(void)
// {
// 	int i,n,t,u,r,Crc_result;
// 	unsigned char p_USART1_ReceiveDataBuffer[10];
	
// if( Get_USART1_StopFlag() == USART1_STOP_TRUE)  //????????????
//   {
		
// 		if((ucUSART1_ReceiveDataBuffer[0] ==0X01) && (ucUSART1_ReceiveDataBuffer[1] ==0X02)&& (ucUSART1_ReceiveDataBuffer[2] ==0X55))
// 		 {
//        LEDXToggle(5);
// 			BMS_DATA_FLAG=1;				
// 		 }
// 		 if((ucUSART1_ReceiveDataBuffer[0] ==0X01) && (ucUSART1_ReceiveDataBuffer[1] ==0X03)&& (ucUSART1_ReceiveDataBuffer[2] ==0X55))
// 		 {
//        LEDXToggle(5);
// 			BMS_DATA_FLAG=0;				
// 		 }
// 		 if((ucUSART1_ReceiveDataBuffer[0] ==0X01) && (ucUSART1_ReceiveDataBuffer[1] ==0X04)&& (ucUSART1_ReceiveDataBuffer[2] ==0X55))
// 		 {
//        LEDXToggle(5);
// 			Only_Open_DSG	();		
// 		 }
// 		 if((ucUSART1_ReceiveDataBuffer[0] ==0X01) && (ucUSART1_ReceiveDataBuffer[1] ==0X05)&& (ucUSART1_ReceiveDataBuffer[2] ==0X55))
// 		 {
//        LEDXToggle(5);
// 			Only_Close_DSG();			
// 		 }
// 		 if((ucUSART1_ReceiveDataBuffer[0] ==0X01) && (ucUSART1_ReceiveDataBuffer[1] ==0X06)&& (ucUSART1_ReceiveDataBuffer[2] ==0X55))
// 		 {
//        LEDXToggle(5);
// 			Only_Open_CHG	();		
// 		 }
// 		 if((ucUSART1_ReceiveDataBuffer[0] ==0X01) && (ucUSART1_ReceiveDataBuffer[1] ==0X07)&& (ucUSART1_ReceiveDataBuffer[2] ==0X55))
// 		 {
//        LEDXToggle(5);
// 			Only_Close_CHG();			
// 		 }
		 
		 
// //		 if((ucUSART1_ReceiveDataBuffer[0] ==0X01) && (ucUSART1_ReceiveDataBuffer[1] ==0X10)&& (ucUSART1_ReceiveDataBuffer[2] ==0X55))
// //		 {
// //       LEDXToggle(5);
// //			 FUN_POWER_EN_ONOFF(1);			
// //		 }
// //		 
// //		 if((ucUSART1_ReceiveDataBuffer[0] ==0X01) && (ucUSART1_ReceiveDataBuffer[1] ==0X11)&& (ucUSART1_ReceiveDataBuffer[2] ==0X55))
// //		 {
// //       LEDXToggle(5);
// //			FUN_POWER_EN_ONOFF(0);			
// //		 }
// //		 
// 		 if((ucUSART1_ReceiveDataBuffer[0] ==0X01) && (ucUSART1_ReceiveDataBuffer[1] ==0X12)&& (ucUSART1_ReceiveDataBuffer[2] ==0X55))
// 		 {
//        LEDXToggle(5);
//        Write_Flash(Battery_ADR ,(ucUSART1_ReceiveDataBuffer[3]<<8) +ucUSART1_ReceiveDataBuffer[4]);							
// 		 }
		 
// 		 if((ucUSART1_ReceiveDataBuffer[0] ==0X01) && (ucUSART1_ReceiveDataBuffer[1] ==0X13)&& (ucUSART1_ReceiveDataBuffer[2] ==0X55))
// 		 {
//        LEDXToggle(5);
//        Write_Flash(Temp_up ,(ucUSART1_ReceiveDataBuffer[3]<<8) +ucUSART1_ReceiveDataBuffer[4]);							
// 		 }
		 
// 		 if((ucUSART1_ReceiveDataBuffer[0] ==0X01) && (ucUSART1_ReceiveDataBuffer[1] ==0X14)&& (ucUSART1_ReceiveDataBuffer[2] ==0X55))
// 		 {
//        LEDXToggle(5);
//        SEND_readparameter_TO_SHANGWEIJI[2]=(Read_Flash(Battery_ADR)>>8);
//        SEND_readparameter_TO_SHANGWEIJI[3]= Read_Flash(Battery_ADR)&0X00FF;
//        SEND_readparameter_TO_SHANGWEIJI[4]=(Read_Flash(Temp_up)>>8);
//        SEND_readparameter_TO_SHANGWEIJI[5]= Read_Flash(Temp_up)&0X00FF;				 
// 			 USART1_Printf( SEND_readparameter_TO_SHANGWEIJI,50, ASCII_CODE );								

// 		 }
		 
		 
		 
// 	}
// 			Set_USART1_StopFlag( USART1_STOP_FALSE );
// 	}
	
// 	u8 key,u;	
// 	u8 canbuf[8];
	
// 	const u8 TEXT_Buffer[]={0,1};
// #define SIZE sizeof(TEXT_Buffer)
// 	u8 datatemp[SIZE]ACTIVATE_USART1,Temp_up_flag,OV_FLAG,UV_FLAG,OC_FLAG;
// 	u32 FLASH_SIZE = 16*1024*1024;
// extern UV_Alarm_flag,OV_Alarm_flag,SCD_Alarm_flag,OCD_Alarm_flag,OT_Alarm_flag,UT_Alarm_flag;
// extern int Batteryval[50];
// int main(void)
// {
//     SYSTICK_Init(); //ϵͳ��ʼ����ʱ�����ã�
// 	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
//     delay_ms(1000);
// 	  uart_init(115200);	 //���ڳ�ʼ��Ϊ115200   
// 	  USART2_Config();    //�������ڳ�ʼ��Ϊ9600
//     LED_GPIO_Config();//������ʾ��4��LED���ã�
//     IO_CTRL_Config(); //ϵͳ��һЩIO�����ã�	   
// 	  I2C1_Configuration();  //BQ76940_1��IIC���ã�
// 	  CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,CAN_Mode_Normal);//CAN��ʼ������ģʽ,������500Kbps    

// 	  BQ76930_config();      //BQ76940�ĳ�ʼ���������豸��OV,UV,SCD,OCD�����ã�	
// 	  LED4_ONOFF(1) ;
//    	TIM2_Config(99,7199);//100mS��ʱ���ж�
// 	  UartSend("MODE_CFG(1);DIR(1);FSIMG(2097152,0,0,220,176,0);\r\n");
// 	  delay_ms(1000);   	
//     UartSend("CLR(61);\r\n");
// 	  IWDG_Init(6,1250);      //���Ź�4S����
//     while (1)
//     {	
// 	   IWDG_Feed();
// 		 LEDXToggle(1);
// 		key=Can_Receive_Msg(canbuf);
// 		if(key)//���յ�������
// 		{			
//  			for(u=0;u<key;u++)
// 			{
// 						 LEDXToggle(1);

//  			}
// 		}
// 		 RECEICE_DATA_DEAL();
// 	   Get_Update_Data();
// 			if((Batteryval[0]>4200)||(Batteryval[1]>4200)||(Batteryval[4]>4200)||(Batteryval[5]>4200)||(Batteryval[6]>4200)||(Batteryval[9]>4200)||(Batteryval[10]>4200)||(Batteryval[11]>4200)||(Batteryval[14]>4200))
// 					{
// 						Only_Close_CHG();                        //
// 						IIC1_write_one_byte_CRC(SYS_STAT,0xFF); //���״̬
// 						OV_FLAG=1;
// 					}
//      if(OV_FLAG==1)
// 		 {
// 					if((Batteryval[0]<4100)&&(Batteryval[1]<4100)&&(Batteryval[4]<4100)&&(Batteryval[5]<4100)&&(Batteryval[6]<4100)&&(Batteryval[9]<4100)&&(Batteryval[10]<4100)&&(Batteryval[11]<4100)&&(Batteryval[14]<4100))
// 					{
// 						Only_Open_CHG();                         //
// 						IIC1_write_one_byte_CRC(SYS_STAT,0xFF); //���״̬
// 						OV_FLAG=0;
// 					}
// 			}
		 
			
// 					if((Batteryval[0]<2800)||(Batteryval[1]<2800)||(Batteryval[4]<2800)||(Batteryval[5]<2800)||(Batteryval[6]<2800)||(Batteryval[9]<2800)||(Batteryval[10]<2800)||(Batteryval[11]<2800)||(Batteryval[14]<2800))
// 					{
// 						Only_Close_DSG();
// 						IIC1_write_one_byte_CRC(SYS_STAT,0xFF); //���״̬
// 						UV_FLAG=1;
// 					}
//           if(UV_FLAG==1)
// 					{
// 					if((Batteryval[0]>2800)&&(Batteryval[1]>2800)&&(Batteryval[4]>2800)&&(Batteryval[5]>2800)&&(Batteryval[6]>2800)&&(Batteryval[9]>2800)&&(Batteryval[10]>2800)&&(Batteryval[11]>2800)&&(Batteryval[14]>2800))
// 					{
// 						Only_Open_DSG();
// 						IIC1_write_one_byte_CRC(SYS_STAT,0xFF); //���״̬
//             UV_FLAG=0;						
// 					}
// 		     }
// 			if(Batteryval[17]>2000)//�����������2000ma���رճ�ŵ�MOS��
// 			{
// 			      Close_DSG_CHG();
// 						IIC1_write_one_byte_CRC(SYS_STAT,0xFF); //���״̬	
// 				    OC_FLAG=1;
// 			}
// 			if( OC_FLAG==1)
// 			{
// 						if(Batteryval[17]<2000)//�����������2000ma���رճ�ŵ�MOS��
// 						{
// 									Open_DSG_CHG();
// 									IIC1_write_one_byte_CRC(SYS_STAT,0xFF); //���״̬	
// 									OC_FLAG=0;
// 						}
						
// 			}
			
// 						if(Batteryval[18]>Read_Flash(Temp_up))//�����������2000ma���رճ�ŵ�MOS��
// 			{
// 			      Close_DSG_CHG();
// 						IIC1_write_one_byte_CRC(SYS_STAT,0xFF); //���״̬	

// 				    Temp_up_flag = 1;
// 			}
// 			if(Temp_up_flag == 1)
// 			{
// 			  if(Batteryval[18]<Read_Flash(Temp_up))
// 				{
// 					  Open_DSG_CHG();
// 											IIC1_write_one_byte_CRC(SYS_STAT,0xFF); //���״̬	

// 				    Temp_up_flag = 0;
					
// 				}
			
// 			}

			
// 		}
// }
// /*********************************************************************************************************
//       END FILE
// *********************************************************************************************************/





// ͷ�ļ�





#include "stm32f10x.h"
#include "led.h"
#include "wdg.h"
#include "SYSTICK.h"
#include "usart.h"
#include "usart2.h"
#include "i2c.h"
#include "i2c1.h"
#include "i2c2.h"
#include "BQ76930.h"
#include "IO_CTRL.h"
#include <stdio.h>
#include "math.h"
#include "timer.h"
#include "stm32f10x_it.h"
#include "w25qxx.h"
#include "spi.h"
#include "can.h"

/**
  * @file   main
  * @brief  Main program.
  * @param  None
  * @retval None
  */

/* �洢����Flashҳ�׵�ַ */
uint32_t  Battery_ADR     =  0x08007800;
uint32_t  Temp_up         =  0x08007C00;

void Write_Flash(uint32_t Add, unsigned int Data)
{
    FLASH_Unlock();
    FLASH_ErasePage(Add);
    FLASH_ProgramWord(Add, Data);
    FLASH_Lock();
}

unsigned int Read_Flash(uint32_t Add)
{
    unsigned int Data;
    Data = *(vu32*)(Add);
    return Data;
}


uint16_t Get_Real_Flash_Size(void)

{

return *(__IO uint16_t*)0x1FFFF7E0;

}

unsigned char SEND_readparameter_TO_SHANGWEIJI[500] = {0XAA,0X88};

extern unsigned char ucUSART1_ReceiveDataBuffer[];
unsigned char BMS_DATA_FLAG = 0;

void RECEICE_DATA_DEAL(void)
{
    int i,n,t,u,r,Crc_result;
    unsigned char p_USART1_ReceiveDataBuffer[10];

    if(Get_USART1_StopFlag() == USART1_STOP_TRUE)
    {
        if((ucUSART1_ReceiveDataBuffer[0]==0X01) && (ucUSART1_ReceiveDataBuffer[1]==0X02) && (ucUSART1_ReceiveDataBuffer[2]==0X55))
        {
            LEDXToggle(5);
            BMS_DATA_FLAG=1;
        }
        if((ucUSART1_ReceiveDataBuffer[0]==0X01) && (ucUSART1_ReceiveDataBuffer[1]==0X03) && (ucUSART1_ReceiveDataBuffer[2]==0X55))
        {
            LEDXToggle(5);
            BMS_DATA_FLAG=0;
        }
        if((ucUSART1_ReceiveDataBuffer[0]==0X01) && (ucUSART1_ReceiveDataBuffer[1]==0X04) && (ucUSART1_ReceiveDataBuffer[2]==0X55))
        {
            LEDXToggle(5);
            Only_Open_DSG();
        }
        if((ucUSART1_ReceiveDataBuffer[0]==0X01) && (ucUSART1_ReceiveDataBuffer[1]==0X05) && (ucUSART1_ReceiveDataBuffer[2]==0X55))
        {
            LEDXToggle(5);
            Only_Close_DSG();
        }
        if((ucUSART1_ReceiveDataBuffer[0]==0X01) && (ucUSART1_ReceiveDataBuffer[1]==0X06) && (ucUSART1_ReceiveDataBuffer[2]==0X55))
        {
            LEDXToggle(5);
            Only_Open_CHG();
        }
        if((ucUSART1_ReceiveDataBuffer[0]==0X01) && (ucUSART1_ReceiveDataBuffer[1]==0X07) && (ucUSART1_ReceiveDataBuffer[2]==0X55))
        {
            LEDXToggle(5);
            Only_Close_CHG();
        }
        if((ucUSART1_ReceiveDataBuffer[0]==0X01) && (ucUSART1_ReceiveDataBuffer[1]==0X12) && (ucUSART1_ReceiveDataBuffer[2]==0X55))
        {
            LEDXToggle(5);
            Write_Flash(Battery_ADR, (ucUSART1_ReceiveDataBuffer[3]<<8) + ucUSART1_ReceiveDataBuffer[4]);
        }
        if((ucUSART1_ReceiveDataBuffer[0]==0X01) && (ucUSART1_ReceiveDataBuffer[1]==0X13) && (ucUSART1_ReceiveDataBuffer[2]==0X55))
        {
            LEDXToggle(5);
            Write_Flash(Temp_up, (ucUSART1_ReceiveDataBuffer[3]<<8) + ucUSART1_ReceiveDataBuffer[4]);
        }
        if((ucUSART1_ReceiveDataBuffer[0]==0X01) && (ucUSART1_ReceiveDataBuffer[1]==0X14) && (ucUSART1_ReceiveDataBuffer[2]==0X55))
        {
            LEDXToggle(5);
            SEND_readparameter_TO_SHANGWEIJI[2] = (Read_Flash(Battery_ADR)>>8);
            SEND_readparameter_TO_SHANGWEIJI[3] =  Read_Flash(Battery_ADR)&0X00FF;
            SEND_readparameter_TO_SHANGWEIJI[4] = (Read_Flash(Temp_up)>>8);
            SEND_readparameter_TO_SHANGWEIJI[5] =  Read_Flash(Temp_up)&0X00FF;
            USART1_Printf(SEND_readparameter_TO_SHANGWEIJI,50, ASCII_CODE);
        }

        Set_USART1_StopFlag(USART1_STOP_FALSE);
    }
}

u8 key, u;
u8 canbuf[8];

const u8 TEXT_Buffer[] = {0,1};
#define SIZE sizeof(TEXT_Buffer)

u8 datatemp[SIZE];
u8 ACTIVATE_USART1;
u8 Temp_up_flag;
u8 OV_FLAG;
u8 UV_FLAG;
u8 OC_FLAG;

u32 FLASH_SIZE = 16*1024*1024;

extern u8 UV_Alarm_flag;
extern u8 OV_Alarm_flag;
extern u8 SCD_Alarm_flag;
extern u8 OCD_Alarm_flag;
extern u8 OT_Alarm_flag;
extern u8 UT_Alarm_flag;

extern int Batteryval[50];

int main(void)
{
    
    SYSTICK_Init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    delay_ms(1000);
    uart_init(115200);
    USART2_Config();
    LED_GPIO_Config();
    IO_CTRL_Config();
    I2C1_Configuration();
    CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,CAN_Mode_Normal);
    BQ76930_config();
    LED4_ONOFF(1);
    TIM2_Config(99,7199);
    UartSend("MODE_CFG(1);DIR(1);FSIMG(2097152,0,0,220,176,0);\r\n");
    delay_ms(1000);
    UartSend("CLR(61);\r\n");
    IWDG_Init(6,1250);
    while(1)
    {
			
			
        IWDG_Feed();
        LEDXToggle(1);
        key = Can_Receive_Msg(canbuf);

        if(key)
        {
            for(u=0;u<key;u++)
            {
                LEDXToggle(1);
            }
        }

        RECEICE_DATA_DEAL();
        Get_Update_Data();

        if((Batteryval[0]>4200)||(Batteryval[1]>4200)||(Batteryval[4]>4200)||
           (Batteryval[5]>4200)||(Batteryval[6]>4200)||(Batteryval[9]>4200)||
           (Batteryval[10]>4200)||(Batteryval[11]>4200)||(Batteryval[14]>4200))
        {
            Only_Close_CHG();
            IIC1_write_one_byte_CRC(SYS_STAT,0xFF);
            OV_FLAG=1;
        }
        if(OV_FLAG==1)
        {
            if((Batteryval[0]<4100)&&(Batteryval[1]<4100)&&(Batteryval[4]<4100)&&
               (Batteryval[5]<4100)&&(Batteryval[6]<4100)&&(Batteryval[9]<4100)&&
               (Batteryval[10]<4100)&&(Batteryval[11]<4100)&&(Batteryval[14]<4100))
            {
                Only_Open_CHG();
                IIC1_write_one_byte_CRC(SYS_STAT,0xFF);
                OV_FLAG=0;
            }
        }

        if((Batteryval[0]<2800)||(Batteryval[1]<2800)||(Batteryval[4]<2800)||
           (Batteryval[5]<2800)||(Batteryval[6]<2800)||(Batteryval[9]<2800)||
           (Batteryval[10]<2800)||(Batteryval[11]<2800)||(Batteryval[14]<2800))
        {
            Only_Close_DSG();
            IIC1_write_one_byte_CRC(SYS_STAT,0xFF);
            UV_FLAG=1;
        }
        if(UV_FLAG==1)
        {
            if((Batteryval[0]>2800)&&(Batteryval[1]>2800)&&(Batteryval[4]>2800)&&
               (Batteryval[5]>2800)&&(Batteryval[6]>2800)&&(Batteryval[9]>2800)&&
               (Batteryval[10]>2800)&&(Batteryval[11]>2800)&&(Batteryval[14]>2800))
            {
                Only_Open_DSG();
                IIC1_write_one_byte_CRC(SYS_STAT,0xFF);
                UV_FLAG=0;
            }
        }

        if(Batteryval[17]>2000)
        {
            Close_DSG_CHG();
            IIC1_write_one_byte_CRC(SYS_STAT,0xFF);
            OC_FLAG=1;
        }
        if(OC_FLAG==1)
        {
            if(Batteryval[17]<2000)
            {
                Open_DSG_CHG();
                IIC1_write_one_byte_CRC(SYS_STAT,0xFF);
                OC_FLAG=0;
            }
        }

        if(Batteryval[18] > Read_Flash(Temp_up))
        {
            Close_DSG_CHG();
            IIC1_write_one_byte_CRC(SYS_STAT,0xFF);
            Temp_up_flag = 1;
        }
        if(Temp_up_flag == 1)
        {
            if(Batteryval[18] < Read_Flash(Temp_up))
            {
                Open_DSG_CHG();
                IIC1_write_one_byte_CRC(SYS_STAT,0xFF);
                Temp_up_flag = 0;
            }
        }
    }
}













