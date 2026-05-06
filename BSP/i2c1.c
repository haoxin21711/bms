/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��i2c.c
 * ����    ����ʼ��IIC��һЩ�����Ĳ��� 
 * ����    ��zhuoyingxingyu
 * �Ա�    ��Դ�ع�����http://vcc-gnd.taobao.com/
 * ��̳��ַ������԰��-Ƕ��ʽ������̳http://vcc-gnd.com/
 * �汾����: 2016-04-08
 * Ӳ������: PB6-I2C1_SCL��PB7-I2C1_SDA
 * ���Է�ʽ��J-Link-OB
**********************************************************************************/

//ͷ�ļ�
#include "i2c1.h"
#include "usart.h"
#include "SYSTICK.h"
 

/**
  * @file   I2C1_Configuration
  * @brief  I2C1�ܽ�����
  * @param  ��
  * @retval ��
  */
void I2C1_Configuration(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
  /* Configure I2C2 pins: PB8->I2C1_SCL and PB9->I2C1_SDA */
  RCC_APB2PeriphClockCmd(I2C1_SCL_GPIO_RCC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  I2C1_SCL_PIN ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
	GPIO_Init(I2C1_SCL_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  I2C1_SDA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
	GPIO_Init(I2C1_SDA_GPIO_PORT, &GPIO_InitStructure);
}


 /**
  * @file   I2C_delay
  * @brief  �ӳ�ʱ��
  * @param  ��
  * @retval ��
  */
static void I2C_delay(void)
{	
   uint8_t i=80; /* ��������Ż��ٶ�,��������͵�5����д�� */
   while(i) 
   { 
     i--; 
   } 
}

 /**
  * @file   I2C_Start
  * @brief  ��ʼ�ź�
  * @param  ��
  * @retval ��
  */
static FunctionalState I2C1_Start(void)
{
	SDA1_H;
	SCL1_H;
	I2C_delay();
	if(!SDA1_read)return DISABLE;	/* SDA��Ϊ�͵�ƽ������æ,�˳� */
	SDA1_L;
	I2C_delay();
	if(SDA1_read) return DISABLE;	/* SDA��Ϊ�ߵ�ƽ�����߳���,�˳� */
	SDA1_L;
	I2C_delay();
	return ENABLE;
}

 /**
  * @file   I2C_Stop
  * @brief  ֹͣ�ź�
  * @param  ��
  * @retval ��
  */
static void I2C1_Stop(void)
{
	SCL1_L;
	I2C_delay();
	SDA1_L;
	I2C_delay();
	SCL1_H;
	I2C_delay();
	SDA1_H;
	I2C_delay();
}

 /**
  * @file   I2C_Ack
  * @brief  Ӧ���ź�
  * @param  ��
  * @retval ��
  */
static void I2C1_Ack(void)
{	
	SCL1_L;
	I2C_delay();
	SDA1_L;
	I2C_delay();
	SCL1_H;
	I2C_delay();
	SCL1_L;
	I2C_delay();
}

 /**
  * @file   I2C_NoAck
  * @brief  ��Ӧ���ź�
  * @param  ��
  * @retval ��
  */
static void I2C1_NoAck(void)
{	
	SCL1_L;
	I2C_delay();
	SDA1_H;
	I2C_delay();
	SCL1_H;
	I2C_delay();
	SCL1_L;
	I2C_delay();
}

 /**
  * @file   I2C_WaitAck
  * @brief  �ȴ�Ack
  * @param  ��
  * @retval ����Ϊ:=1��ACK,=0��ACK
  */
static FunctionalState I2C1_WaitAck(void) 	
{
	SCL1_L;
	I2C_delay();
	SDA1_H;			
	I2C_delay();
	SCL1_H;
	I2C_delay();
	if(SDA1_read)
	{
      SCL1_L;
      return DISABLE;
	}
	SCL1_L;
	return ENABLE;
}

 /**
  * @file   I2C_SendByte
  * @brief  ���ݴӸ�λ����λ
  * @param  - SendByte: ���͵�����
  * @retval ��
  */
// static void I2C1_SendByte(uint8_t SendByte) 
// {
//     uint8_t i=8;
//     while(i--)
//     {
//         SCL1_L;
//         I2C_delay();
//       if(SendByte&0x80)
//         SDA1_H;  
//       else 
//         SDA1_L;   
//         SendByte<<=1;
//         I2C_delay();
// 		SCL1_H;
//         I2C_delay();
//     }
//     SCL1_L;
// }
// 在 i2c1.c 的 I2C1_SendByte 函数中添加：

static void I2C1_SendByte(uint8_t SendByte) 
{
    uint8_t i = 8;
    printf("SendByte: 0x%02X = ", SendByte);
    
    while(i--)
    {
        SCL1_L;
        I2C_delay();
        
        if(SendByte & 0x80) {
            SDA1_H;
            printf("1");  // 打印每一位
        } else {
            SDA1_L;
            printf("0");
        }
        
        SendByte <<= 1;
        I2C_delay();
        SCL1_H;
        I2C_delay();
    }
    
    printf("\r\n");
    SCL1_L;
}

 /**
  * @file   I2C_ReceiveByte
  * @brief  ���ݴӸ�λ����λ
  * @param  ��
  * @retval I2C���߷��ص�����
  */
static uint8_t I2C1_ReceiveByte(void)  
{ 
    uint8_t i=8;
    uint8_t ReceiveByte=0;

    SDA1_H;				
    while(i--)
    {
      ReceiveByte<<=1;      
      SCL1_L;
      I2C_delay();
	  SCL1_H;
      I2C_delay();	
      if(SDA1_read)
      {
        ReceiveByte|=0x01;
      }
    }
    SCL1_L;
    return ReceiveByte;
}
  


u32 IIC1_read_len_byte(u16 ReadAddr,u8 Len)
{
  u8 t;
	u32 temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=IIC1_read_one_byte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;

}


void  IIC1_write_one_byte(u16 WriteAddr,u8 DataToWrite)
{			
	
    I2C1_Start();  
	
		I2C1_SendByte(0X10+((WriteAddr/256)<<1));   //����������ַ0XA0,д���� 
		 
	  I2C1_WaitAck();	   
    I2C1_SendByte(WriteAddr%256);   //���͵͵�ַ
	  I2C1_WaitAck(); 										  		   
	  I2C1_SendByte(DataToWrite);     //�����ֽ�							   
    I2C1_WaitAck();	    	   
    I2C1_Stop();//����һ��ֹͣ���� 
	  delay_ms(10);
  
}

void  IIC1_write_len_byte(u16 WriteAddr,u8 DataToWrite,u8 Len)
{
  u8 t;
	for(t=0;t<Len;t++)
	{
		IIC1_write_one_byte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    

}




void IIC1_write_one_byte_CRC(u16 WriteAddr,u16 DataToWrite)
{
		
  
  unsigned char DataBuffer[4];
	
  DataBuffer[0] = 0X08 << 1;
	DataBuffer[1] = WriteAddr;
	DataBuffer[2] = DataToWrite;
	DataBuffer[3] = CRC8(DataBuffer, 3, 7);
	
    I2C1_Start();  	
		I2C1_SendByte( DataBuffer[0]);   //����������ַ0XA0,д���� 		 
	  I2C1_WaitAck();	   
    I2C1_SendByte(DataBuffer[1]);   //���͵�ַ
	  I2C1_WaitAck(); 										  		   
	  I2C1_SendByte(DataBuffer[2]);     //�����ֽ�							   
    I2C1_WaitAck();	
	  I2C1_SendByte(DataBuffer[3]);     //����CRC
	  I2C1_WaitAck();
    I2C1_Stop();//����һ��ֹͣ���� 	  
	  delay_ms(10);
}


// u8 IIC1_read_one_byte(u16 ReadAddr)
// {				  
//   printf("========== I2C Read Start ==========\r\n");
// 	u8 temp=0;		  	    																 
//   I2C1_Start();  
//   printf("[OK] I2C Start success\r\n");
// 	I2C1_SendByte(0x08 << 1) ;   //����������ַ0XA0,д���� 	 
//   printf("[OK] Device 0x08 ACK (Write mode)\r\n");
// 	I2C1_WaitAck();
//   I2C1_SendByte(ReadAddr);   //
//   printf("[OK] Register 0x%02X ACK\r\n", ReadAddr);
// 	I2C1_WaitAck();    
// 	I2C1_Start();  	 	   
// 	I2C1_SendByte(0X11);           //�������ģʽ			   
// 	I2C1_WaitAck(); 
//     temp=I2C1_ReceiveByte();		   
//     I2C1_Stop();//����һ��ֹͣ����
//     return temp;
// }
// 在 i2c1.c 中添加调试代码

u8 IIC1_read_one_byte(u16 ReadAddr)
{
    u8 temp = 0;
    
    printf("========== I2C Read Start ==========\r\n");
    
    // Step 1: Start
    if(I2C1_Start() == DISABLE) {
        printf("[ERROR] I2C Start failed!\r\n");
        return 0xFF;
    }
    printf("[OK] I2C Start success\r\n");
    
    // Step 2: 发送设备地址(写)
    I2C1_SendByte(0x08 << 1);
    if(I2C1_WaitAck() == DISABLE) {
        printf("[ERROR] Device 0x08 not respond (Write mode)\r\n");
        I2C1_Stop();
        return 0xFF;
    }
    printf("[OK] Device 0x08 ACK (Write mode)\r\n");
    
    // Step 3: 发送寄存器地址
    I2C1_SendByte(ReadAddr);
    if(I2C1_WaitAck() == DISABLE) {
        printf("[ERROR] Register 0x%02X not respond\r\n", ReadAddr);
        I2C1_Stop();
        return 0xFF;
    }
    printf("[OK] Register 0x%02X ACK\r\n", ReadAddr);
    
    // Step 4: ReStart
    I2C1_Start();
    printf("[OK] I2C ReStart\r\n");
    
    // Step 5: 发送设备地址(读)
    I2C1_SendByte(0x08 << 1 | 1);
    if(I2C1_WaitAck() == DISABLE) {
        printf("[ERROR] Device 0x08 not respond (Read mode)\r\n");
        I2C1_Stop();
        return 0xFF;
    }
    printf("[OK] Device 0x08 ACK (Read mode)\r\n");
    
    // Step 6: 读取数据
    temp = I2C1_ReceiveByte();
    printf("[OK] Read data = 0x%02X (%d)\r\n", temp, temp);
    
    // Step 7: Stop
    I2C1_Stop();
    printf("[OK] I2C Stop\r\n");
    
    printf("========== I2C Read End ==========\r\n\r\n");
    
    return temp;
}
 /**
  * @file   I2C_WriteByte
  * @brief  дһ�ֽ�����
  * @param  
	*          - SendByte: ��д������
	*          - WriteAddress: ��д���ַ
	*          - DeviceAddress: ��������(24c16��SD2403)
  * @retval ����Ϊ:=1�ɹ�д��,=0ʧ��
  */
FunctionalState I2C1_WriteByte(uint8_t SendByte, uint16_t WriteAddress, uint8_t DeviceAddress)
{		
    if(!I2C1_Start())return DISABLE;
    I2C1_SendByte((((WriteAddress & 0x0700) >>7) | DeviceAddress) & 0xFFFE); /*���ø���ʼ��ַ+������ַ */
    if(!I2C1_WaitAck()){I2C1_Stop(); return DISABLE;}
    I2C1_SendByte((uint8_t)(WriteAddress & 0x00FF));   /* ���õ���ʼ��ַ */      
    I2C1_WaitAck();	
    I2C1_SendByte(SendByte);
    I2C1_WaitAck();   
    I2C1_Stop(); 
    return ENABLE;
}									 

 /**
  * @file   I2C_ReadByte
  * @brief  ��ȡһ������
  * @param  
	*					- pBuffer: ��Ŷ�������
	*     	  - length: ����������
	*         - ReadAddress: ��������ַ
	*         - DeviceAddress: ��������(24c16��SD2403)
  * @retval ����Ϊ:=1�ɹ�����,=0ʧ��
  */
FunctionalState I2C1_ReadByte(uint8_t* pBuffer,   uint16_t length,   uint16_t ReadAddress,  uint8_t DeviceAddress)
{		
    if(!I2C1_Start())return DISABLE;
    I2C1_SendByte((((ReadAddress & 0x0700) >>7) | DeviceAddress) & 0xFFFE); /* ���ø���ʼ��ַ+������ַ */ 
    if(!I2C1_WaitAck()){I2C1_Stop(); return DISABLE;}
    I2C1_SendByte((uint8_t)(ReadAddress & 0x00FF));   /* ���õ���ʼ��ַ */      
    I2C1_WaitAck();
    I2C1_Start();
    I2C1_SendByte(((ReadAddress & 0x0700) >>7) | DeviceAddress | 0x0001);
    I2C1_WaitAck();
    while(length)
    {
      *pBuffer = I2C1_ReceiveByte();
      if(length == 1)I2C1_NoAck();
      else I2C1_Ack(); 
      pBuffer++;
      length--;
    }
    I2C1_Stop();
    return ENABLE;
}






/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
