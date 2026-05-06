#include "BQ76930.h"
#include "SYSTICK.h" 
#include "i2c.h"
#include "i2c1.h"
#include "i2c2.h"
#include "usart.h"
#include "math.h"
#include "string.h"
#include "IO_CTRL.h"
#include "usart2.h"
#include "can.h"
#include "led.h"
/*****************************
file:BQData.c
decription:
   1.�ɼ�BQ76930��14λADC�������ƫ�õ�ѹ:void get_offset(void)
   2.�ɼ������ѹ:void Get_Batteryx(void),����xȡֵ1-10��
   3.BQ76930��ʼ�� void BQ_config(void)
   4.��ȡBQ76930�Ĵ���ֵ�� void readbqstate(void)
   5.
******************************/
/***********************
fuction:void get_offset(void)
************************/
int ADC_offset,GAIN;
float ADC_GAIN = 0;

/**
 * @brief 获取BQ76930的ADC增益和偏移量
 * @description 从BQ76930芯片读取ADC增益寄存器(ADCGAIN1, ADCGAIN2)和偏移量寄存器(ADCOFFSET)
 *              计算实际的ADC增益值(单位: uV)和偏移量(单位: mV)
 *              ADC_GAIN计算公式: ((ADCGAIN1 & 0x0C) << 1) + ((ADCGAIN2 & 0xE0) >> 5)
 *              最终GAIN = 365 + ADC_GAIN, 典型值为377uV
 * @param 无
 * @return 无
 * @note 全局变量ADC_GAIN, ADC_offset, GAIN会被更新
 */
void Get_offset(void)
{
 unsigned char gain[2];  // 临时存储ADCGAIN1和ADCGAIN2寄存器值
 
 gain[0]=IIC1_read_one_byte(ADCGAIN1);//ADC_GAIN1
 gain[1]=IIC1_read_one_byte(ADCGAIN2);//ADC_GAIN2
 ADC_GAIN = ((gain[0]&0x0c)<<1)+((gain[1]&0xe0)>>5);//12uV
 ADC_offset=IIC1_read_one_byte(ADCOFFSET);//45mV
 GAIN = 365+ADC_GAIN;//GAIN=377uV
}
/****************************************
fuction: void Get_Battery1(void)
description:��ȡ��1�ŵ����ص�ѹ
Parameters:batterylval[0],battery1val[1];
******************************************/
void BQ76930_config(void)
{
	  WAKE_ALL_DEVICE();  // 唤醒设备
	    BQ_1_2_config();   //BQ76930基础配置
	  Get_offset();  //获取数据写入全局变量
    OV_UV_1_2_PROTECT();
    OCD_SCD_PROTECT();  
	  //Open_DSG_CHG();  
	 
	  IIC1_write_one_byte_CRC(SYS_STAT,0xFF);  
}

void BQ_1_2_config(void)
{

    BQ_1_config();//
}

void OV_UV_1_2_PROTECT(void)
{
    OV_UV_1_PROTECT();
}
/**
 * @brief 唤醒所有设备
 * @description 通过控制MCU_WAKE_BQ_ONOFF引脚产生脉冲信号来唤醒BQ76930芯片
 *              先将引脚置高电平100ms，再置低电平，完成唤醒序列
 * @param 无
 * @return 无
 */
void WAKE_ALL_DEVICE(void)
{
	  MCU_WAKE_BQ_ONOFF(1);  // 唤醒引脚置高电平，开始唤醒
	  delay_ms(100);         // 延时100ms，确保唤醒信号稳定
		MCU_WAKE_BQ_ONOFF(0);  // 唤醒引脚置低电平，完成唤醒脉冲

}


void SHIP_ALL_DEVICE(void)
{
	IIC1_write_one_byte_CRC(SYS_STAT,0xFF);
}



 int Batteryval[50]={0};
unsigned char shang[500]={0xAA,0x01};
unsigned char shang1[50]={0xAA,0x02};
unsigned char shang2[50]={0xAA,0x03};
unsigned char shang3[50]={0xAA,0x04};

unsigned char can_buf1[8]={0xAA,0x01};
unsigned char can_buf2[8]={0xAA,0x02};
unsigned char can_buf3[8]={0xAA,0x03};
unsigned char can_buf4[8]={0xAA,0x04};
unsigned char can_buf5[8]={0xAA,0x05};
unsigned char can_buf6[8]={0xAA,0x06};
unsigned char can_buf7[8]={0xAA,0x07};


 void Get_Battery1(void)
{
  unsigned int readbattbuf[2];
  unsigned int battery1val[2];
  short batteryval1;
	
  readbattbuf[1] = IIC1_read_one_byte(0x0c);// ��ѹ���ֽ�
  readbattbuf[0] = IIC1_read_one_byte(0x0d);// ��ѹ���ֽ�
 
  batteryval1= readbattbuf[1];   //ƴ��
  batteryval1= (batteryval1 << 8) |readbattbuf[0];   //ƴ��
  batteryval1=((batteryval1*GAIN)/1000)+ADC_offset;//�����ѹ���㹫ʽ����1��
   Batteryval[0] = batteryval1;
	
  battery1val[1]=(char)(batteryval1 >> 8);
  battery1val[0]=(char)(batteryval1 & 0x00FF);
	
	shang[2]=battery1val[1];
	shang[3]=battery1val[0];
	
	shang1[2]=battery1val[1];
	shang1[3]=battery1val[0];
	
	can_buf1[2]=battery1val[1];
	can_buf1[3]=battery1val[0];

}
// void Get_Battery1(void)
// {
//     unsigned int readbattbuf[2];
//     short batteryval1;
    
//     printf("\r\n----- Battery 1 Voltage Reading -----\r\n");
    
//     // 读取高字节
//     readbattbuf[1] = IIC1_read_one_byte(0x0c);
//     printf("High byte (0x0C) = 0x%02X\r\n", readbattbuf[1]);
    
//     // 读取低字节
//     readbattbuf[0] = IIC1_read_one_byte(0x0d);
//     printf("Low byte  (0x0D) = 0x%02X\r\n", readbattbuf[0]);
    
//     // 拼接
//     batteryval1 = (readbattbuf[1] << 8) | readbattbuf[0];
//     printf("Raw ADC value = 0x%04X (%d)\r\n", batteryval1, batteryval1);
    
//     // 电压转换
//     printf("GAIN = %d uV, ADC_offset = %d mV\r\n", GAIN, ADC_offset);
//     batteryval1 = ((batteryval1 * GAIN) / 1000) + ADC_offset;
//     printf("Voltage = %d mV\r\n", batteryval1);
    
//     Batteryval[0] = batteryval1;
//     printf("-------------------------------------\r\n\r\n");
// }
void Get_Battery1_me(void)
{
  unsigned int readbattbuf[2];
  
  short batteryval1;
	
  readbattbuf[1] = IIC1_read_one_byte(0x0c);// ��ѹ���ֽ�
  readbattbuf[0] = IIC1_read_one_byte(0x0d);// ��ѹ���ֽ�
 
  batteryval1= readbattbuf[1];   //ƴ��
  batteryval1= (batteryval1 << 8) |readbattbuf[0];   //ƴ��
  batteryval1=((batteryval1*GAIN)/1000)+ADC_offset;//�����ѹ���㹫ʽ����1��
  Batteryval[0]=batteryval1;
	

}


/****************************************
fuction: void Get_Battery2(void)
description:��ȡ��2�ŵ����ص�ѹ
Parameters:battery2val[0],battery2val[1];
******************************************/
void Get_Battery2(void)
{
 
  char readbattbuf[2];
  int batteryval2;
  short battery2val[2];
	
  readbattbuf[1]=IIC1_read_one_byte(0x0e);
  readbattbuf[0]=IIC1_read_one_byte(0x0f);
 
  batteryval2= readbattbuf[1];
  batteryval2= (batteryval2 << 8) |readbattbuf[0];
   
  batteryval2=((batteryval2*GAIN)/1000)+ADC_offset;//????????,?2?
	Batteryval[1]=batteryval2;
	
  battery2val[1]=(char)(batteryval2 >> 8);
  battery2val[0]=(char)(batteryval2 & 0x00FF);
	
	shang[4]=battery2val[1];
	shang[5]=battery2val[0];
	shang1[4]=battery2val[1];
	shang1[5]=battery2val[0];
	
	can_buf1[4]=battery2val[1];
	can_buf1[5]=battery2val[0];

}
/****************************************
fuction: void Get_Battery3(void)
description:��ȡ��3�ŵ����ص�ѹ
Parameters:battery3val[0],battery3val[1];
******************************************/
void Get_Battery3(void)
{
 
  char readbattbuf[2];
  int batteryval3 ;
  char battery3val[2];
  readbattbuf[1]=IIC1_read_one_byte(0x10);
  readbattbuf[0]=IIC1_read_one_byte(0x11);

  batteryval3= readbattbuf[1];
  batteryval3= (batteryval3 << 8) |readbattbuf[0];
  batteryval3=((batteryval3*GAIN)/1000)+ADC_offset;//????????,?3?
  battery3val[1]=(char)(batteryval3 >> 8);
  battery3val[0]=(char)(batteryval3 >> 0);
	Batteryval[2]=batteryval3;
	
	shang[6]=battery3val[1];
	shang[7]=battery3val[0];
	
	
	shang1[6]=battery3val[1];
	shang1[7]=battery3val[0];
	
	can_buf1[6]=battery3val[1];
	can_buf1[7]=battery3val[0];
}
/****************************************
fuction: void Get_Battery4(void)
description:��ȡ��4�ŵ����ص�ѹ
Parameters:battery4val[0],battery4val[1];
******************************************/
void Get_Battery4(void)
{
  char readbattbuf[2];
  int batteryval4 ;
  char battery4val[2];
  readbattbuf[1]=IIC1_read_one_byte(0x12);
  readbattbuf[0]=IIC1_read_one_byte(0x13);
 
  batteryval4= readbattbuf[1];
  batteryval4= (batteryval4 << 8) |readbattbuf[0];
  batteryval4=((batteryval4*GAIN)/1000)+ADC_offset;//????????,?4?
  battery4val[1]=(char)(batteryval4 >> 8);
  battery4val[0]=(char)(batteryval4 >> 0);
	Batteryval[3]=batteryval4;
	
	shang[8]=battery4val[1];
	shang[9]=battery4val[0];

  shang1[8]=battery4val[1];
	shang1[9]=battery4val[0];
	
	can_buf2[2]=battery4val[1];
	can_buf2[3]=battery4val[0];

}
/****************************************
fuction: void Get_Battery5(void)
description:��ȡ��5�ŵ����ص�ѹ
Parameters:battery5val[0],battery5val[1];
******************************************/
void Get_Battery5(void)
{
 char readbattbuf[2];
  short batteryval5 ;
 char battery5val[2];
  readbattbuf[1]=IIC1_read_one_byte(0x14);
  readbattbuf[0]=IIC1_read_one_byte(0x15);
 
  batteryval5= readbattbuf[1];
  batteryval5= (batteryval5 << 8) |readbattbuf[0];
  batteryval5=((batteryval5*GAIN)/1000)+ADC_offset;//????????,?5?
	Batteryval[4]=batteryval5;
  battery5val[1]=(char)(batteryval5 >> 8);
  battery5val[0]=(char)(batteryval5 & 0x00FF);
	

	shang[10]=battery5val[1];
	shang[11]=battery5val[0];
	
	shang1[10]=battery5val[1];
	shang1[11]=battery5val[0];
	
	can_buf2[4]=battery5val[1];
	can_buf2[5]=battery5val[0];

}
/****************************************
fuction: void Get_Battery6(void)
description:��ȡ��6�ŵ����ص�ѹ
Parameters:battery6val[0],battery6val[1];
******************************************/
void Get_Battery6(void)
{
 
  char readbattbuf[2];
  short batteryval6 ;
 char battery6val[2];
  readbattbuf[1]=IIC1_read_one_byte(0x16);
  readbattbuf[0]=IIC1_read_one_byte(0x17);
 
  batteryval6= readbattbuf[1];
  batteryval6= (batteryval6 << 8) |readbattbuf[0];
  batteryval6=((batteryval6*GAIN)/1000)+ADC_offset;//????????,?6?
	Batteryval[5]=batteryval6;
  battery6val[1]=(char)(batteryval6 >> 8);
  battery6val[0]=(char)(batteryval6 & 0x00FF);
	
	shang[12]=battery6val[1];
	shang[13]=battery6val[0];

  shang1[12]=battery6val[1];
	shang1[13]=battery6val[0];
	
	can_buf2[6]=battery6val[1];
	can_buf2[7]=battery6val[0];

}
/****************************************
fuction: void Get_Battery7(void)
description:��ȡ��7�ŵ����ص�ѹ
Parameters:battery7val[0],battery7val[1];
******************************************/
void Get_Battery7(void)
{
  char readbattbuf[2];
  short batteryval7 ;
  char battery7val[2];
  readbattbuf[1]=IIC1_read_one_byte(0x18);
  readbattbuf[0]=IIC1_read_one_byte(0x19);
 
  batteryval7= readbattbuf[1];
  batteryval7= (batteryval7 << 8) |readbattbuf[0];
  batteryval7=((batteryval7*GAIN)/1000)+ADC_offset;//????????,?7?
	Batteryval[6]=batteryval7;
  battery7val[1]=(char)(batteryval7 >> 8);
  battery7val[0]=(char)(batteryval7 & 0x00FF);
	
	shang[14]=battery7val[1];
	shang[15]=battery7val[0];
	
	shang1[14]=battery7val[1];
	shang1[15]=battery7val[0];
	
	can_buf3[2]=battery7val[1];
	can_buf3[3]=battery7val[0];

}
/****************************************
fuction: void Get_Battery8(void)
description:��ȡ��8�ŵ����ص�ѹ
Parameters:battery8val[0],battery8val[1];
******************************************/
void Get_Battery8(void)
{
  char readbattbuf[2];
  int batteryval8 ;
  char battery8val[2];
  readbattbuf[1]=IIC1_read_one_byte(0x1a);
  readbattbuf[0]=IIC1_read_one_byte(0x1b);
 
  batteryval8= readbattbuf[1];
  batteryval8= (batteryval8 << 8) |readbattbuf[0];
  batteryval8=((batteryval8*GAIN)/1000)+ADC_offset;//????????,?8?
  battery8val[1]=(char)(batteryval8 >> 8);
  battery8val[0]=(char)(batteryval8 >> 0);
	Batteryval[7]=batteryval8;
	
	shang[16]=battery8val[1];
	shang[17]=battery8val[0];

  shang1[16]=battery8val[1];
	shang1[17]=battery8val[0];
	
	can_buf3[4]=battery8val[1];
	can_buf3[5]=battery8val[0];

}

/****************************************
fuction: void Get_Battery9(void)
description:��ȡ��9�ŵ����ص�ѹ
Parameters:battery9val[0],battery9val[1];
******************************************/
void Get_Battery9(void)
{
  char readbattbuf[2];
  short batteryval9 ;
  char battery9val[2];
  readbattbuf[1]=IIC1_read_one_byte(0x1c);
  readbattbuf[0]=IIC1_read_one_byte(0x1d);
 
  batteryval9= readbattbuf[1];
  batteryval9= (batteryval9 << 8) |readbattbuf[0];
  batteryval9=((batteryval9*GAIN)/1000)+ADC_offset;//????????,?8?
  battery9val[1]=(char)(batteryval9 >> 8);
  battery9val[0]=(char)(batteryval9 & 0x00FF);
	Batteryval[8]=batteryval9;
	
	shang[18]=battery9val[1];
	shang[19]=battery9val[0];

  shang1[18]=battery9val[1];
	shang1[19]=battery9val[0];
	
	can_buf3[6]=battery9val[1];
	can_buf3[7]=battery9val[0];

}
/****************************************
fuction: void Get_Battery10(void)
description:��ȡ��10�ŵ����ص�ѹ
Parameters:battery10val[0],battery10val[1];
******************************************/
void Get_Battery10(void)
{
  char readbattbuf[2];
  short batteryval10 ;
  char battery10val[2];
  readbattbuf[1]=IIC1_read_one_byte(0x1e);
  readbattbuf[0]=IIC1_read_one_byte(0x1f);
 
  batteryval10= readbattbuf[1];
  batteryval10= (batteryval10 << 8) |readbattbuf[0];
  batteryval10=((batteryval10*GAIN)/1000)+ADC_offset;//????????,?8?
	Batteryval[9]=batteryval10;
  battery10val[1]=(char)(batteryval10 >> 8);
  battery10val[0]=(char)(batteryval10 & 0x00FF);
	
	shang[20]=battery10val[1];
	shang[21]=battery10val[0];

  shang2[2]=battery10val[1];
	shang2[3]=battery10val[0];
	can_buf4[2]=battery10val[1];
	can_buf4[3]=battery10val[0];


}

/****************************************
fuction: void Get_Battery10(void)
description:��ȡ��11�ŵ����ص�ѹ
Parameters:battery10val[0],battery10val[1];
******************************************/
void Get_Battery11(void)
{
  char readbattbuf[2];
  short batteryval11 ;
  char battery11val[2];
  readbattbuf[1]=IIC1_read_one_byte(0x20);
  readbattbuf[0]=IIC1_read_one_byte(0x21);
 
  batteryval11= readbattbuf[1];
  batteryval11= (batteryval11 << 8) |readbattbuf[0];
  batteryval11=((batteryval11*GAIN)/1000)+ADC_offset;//????????,?8?
	Batteryval[10]=batteryval11;
  battery11val[1]=(char)(batteryval11 >> 8);
  battery11val[0]=(char)(batteryval11 & 0x00FF);
	
	shang[22]=battery11val[1];
	shang[23]=battery11val[0];

  shang2[4]=battery11val[1];
	shang2[5]=battery11val[0];
	
	can_buf4[4]=battery11val[1];
	can_buf4[5]=battery11val[0];

}
/****************************************
fuction: void Get_Battery10(void)
description:��ȡ��12�ŵ����ص�ѹ
Parameters:battery10val[0],battery10val[1];
******************************************/
void Get_Battery12(void)
{
  char readbattbuf[2];
  short batteryval12 ;
  char battery12val[2];
  readbattbuf[1]=IIC1_read_one_byte(0x22);
  readbattbuf[0]=IIC1_read_one_byte(0x23);
 
  batteryval12= readbattbuf[1];
  batteryval12= (batteryval12 << 8) |readbattbuf[0];
  batteryval12=((batteryval12*GAIN)/1000)+ADC_offset;//????????,?8?
	Batteryval[11]=batteryval12;
  battery12val[1]=(char)(batteryval12 >> 8);
  battery12val[0]=(char)(batteryval12 & 0x00FF);
	
	shang[24]=battery12val[1];
	shang[25]=battery12val[0];

  shang2[6]=battery12val[1];
	shang2[7]=battery12val[0];
	
	can_buf4[6]=battery12val[1];
	can_buf4[7]=battery12val[0];

}
/****************************************
fuction: void Get_Battery10(void)
description:��ȡ��13�ŵ����ص�ѹ
Parameters:battery10val[0],battery10val[1];
******************************************/
void Get_Battery13(void)
{
  char readbattbuf[2];
  short batteryval13 ;
  char battery13val[2];
  readbattbuf[1]=IIC1_read_one_byte(0x24);
  readbattbuf[0]=IIC1_read_one_byte(0x25);
 
  batteryval13= readbattbuf[1];
  batteryval13= (batteryval13 << 8) |readbattbuf[0];
  batteryval13=((batteryval13*GAIN)/1000)+ADC_offset;//????????,?8?
	Batteryval[12]=batteryval13;
  battery13val[1]=(char)(batteryval13 >> 8);
  battery13val[0]=(char)(batteryval13 & 0x00FF);
	
	shang[26]=battery13val[1];
	shang[27]=battery13val[0];

  shang2[8]=battery13val[1];
	shang2[9]=battery13val[0];
	
	can_buf5[2]=battery13val[1];
	can_buf5[3]=battery13val[0];

}
/****************************************
fuction: void Get_Battery10(void)
description:��ȡ��14�ŵ����ص�ѹ
Parameters:battery10val[0],battery10val[1];
******************************************/
void Get_Battery14(void)
{
  char readbattbuf[2];
  short batteryval14 ;
  char battery14val[2];
  readbattbuf[1]=IIC1_read_one_byte(0x26);
  readbattbuf[0]=IIC1_read_one_byte(0x27);
 
  batteryval14= readbattbuf[1];
  batteryval14= (batteryval14 << 8) |readbattbuf[0];
  batteryval14=((batteryval14*GAIN)/1000)+ADC_offset;//????????,?8?
	Batteryval[13]=batteryval14;
  battery14val[1]=(char)(batteryval14 >> 8);
  battery14val[0]=(char)(batteryval14 & 0x00FF);
	
	shang[28]=battery14val[1];
	shang[29]=battery14val[0];

  shang2[10]=battery14val[1];
	shang2[11]=battery14val[0];
	
	can_buf5[4]=battery14val[1];
	can_buf5[5]=battery14val[0];

}
/****************************************
fuction: void Get_Battery10(void)
description:��ȡ��15�ŵ����ص�ѹ
Parameters:battery10val[0],battery10val[1];
******************************************/
void Get_Battery15(void)
{
  char readbattbuf[2];
  short batteryval15 ;
  char battery15val[2];
  readbattbuf[1]=IIC1_read_one_byte(0x28);
  readbattbuf[0]=IIC1_read_one_byte(0x29);
 
  batteryval15= readbattbuf[1];
  batteryval15= (batteryval15 << 8) |readbattbuf[0];
  batteryval15=((batteryval15*GAIN)/1000)+ADC_offset;//????????,?8?
	Batteryval[14]=batteryval15;
  battery15val[1]=(char)(batteryval15 >> 8);
  battery15val[0]=(char)(batteryval15 & 0x00FF);
	
	shang[30]=battery15val[1];
	shang[31]=battery15val[0];

  shang2[12]=battery15val[1];
	shang2[13]=battery15val[0];
	
	can_buf5[6]=battery15val[1];
	can_buf5[7]=battery15val[0];


}



/****************************
��ȡ���е�ص��ܵ�ѹֵ���ô���1��ӡ����
 *****************************/

void Get_Update_ALL_Data(void)
{
	int i,Sum_val;
//  for(i=0;i<15;i++)
//	{
	   Sum_val= Batteryval[0]+Batteryval[1]+Batteryval[4]+Batteryval[5]+Batteryval[6]+Batteryval[9]+Batteryval[10]+Batteryval[11]+Batteryval[14];
	//}
	
	Batteryval[15] = Sum_val;
	
	shang[32]=(char)(Batteryval[15] >> 8);
  shang[33]=(char)(Batteryval[15] &0XFF);
	
  shang2[14]=(char)shang[32];
  shang2[15]=(char)shang[33];
	
	can_buf6[2]=(char)shang[32];
	can_buf6[3]=(char)shang[33];

}

int SOC;
void Get_SOC(void)
{
	
  if(	Batteryval[15] >(4100*9))
       {SOC=100;}
	else if((	Batteryval[15] >(4100*9))&&(Batteryval[15]<(4150*9))){SOC=95;}
	else if((Batteryval[15]>(4050*9))&&(Batteryval[15]<(4100*9))){SOC=90;}
	else if((Batteryval[15]>(4000*9))&&(Batteryval[15]<(4050*9))){SOC=88;}
	else if((Batteryval[15]>(3950*9))&&(Batteryval[15]<(4000*9))){SOC=87;}
	else if((Batteryval[15]>(3900*9))&&(Batteryval[15]<(3950*9))){SOC=86;}
	else if((Batteryval[15]>(3900*9))&&(Batteryval[15]<(3950*9))){SOC=85;}
	else if((Batteryval[15]>(3850*9))&&(Batteryval[15]<(3900*9))){SOC=84;}
	else if((Batteryval[15]>(3800*9))&&(Batteryval[15]<(3850*9))){SOC=83;}
	else if((Batteryval[15]>(3750*9))&&(Batteryval[15]<(3800*9))){SOC=82;}
	else if((Batteryval[15]>(3700*9))&&(Batteryval[15]<(3750*9))){SOC=81;}
	else if((Batteryval[15]>(3650*9))&&(Batteryval[15]<(3700*9))){SOC=80;}
	else if((Batteryval[15]>(3600*9))&&(Batteryval[15]<(3650*9))){SOC=79;}
	else if((Batteryval[15]>(3550*9))&&(Batteryval[15]<(3600*9))){SOC=78;}
	else if((Batteryval[15]>(3500*9))&&(Batteryval[15]<(3550*9))){SOC=77;}
	
	else if((Batteryval[15]>(3450*9))&&(Batteryval[15]<(3500*9))){SOC=40;}
	else if((Batteryval[15]>(3400*9))&&(Batteryval[15]<(3500*9))){SOC=30;}
	else if((Batteryval[15]>(3300*9))&&(Batteryval[15]<(3400*9))){SOC=20;}
	else if((Batteryval[15]>(3200*9))&&(Batteryval[15]<(3300*9))){SOC=10;}
	else if((Batteryval[15]>(3100*9))&&(Batteryval[15]<(3200*9))){SOC=5;}
	Batteryval[16] = SOC;
	
  shang[34]=(char)(Batteryval[16] >> 8);
  shang[35]=(char)(Batteryval[16] &0XFF);

	
	shang2[16]=(char)shang[34];
  shang2[17]=(char)shang[35];
	
	can_buf6[4]=(char)shang[34];
	can_buf6[5]=(char)shang[35];

}






 /****************************
��ȡ���е�صĵ�ѹֵ���ô���1��ӡ����
 *****************************/




/////////////////////////////////////////////////////////////////////////////////////////////////////////

void OV_UV_1_PROTECT(void)
{
  unsigned char OVTrip_Val,UVTrip_Val;
  float t = 0.377;
  OVTrip_Val = (unsigned char)((((unsigned int)((OVPThreshold - ADC_offset)/t + 0.5 ) )>>4) &0xFF);
  UVTrip_Val = (unsigned char)((((unsigned int)((UVPThreshold - ADC_offset)/t + 0.5 ) )>>4) &0xFF);
  IIC1_write_one_byte_CRC(OV_TRIP,OVTrip_Val);
  IIC1_write_one_byte_CRC(UV_TRIP,UVTrip_Val);
 }

 

void OCD_SCD_PROTECT(void) 
{

IIC1_write_one_byte_CRC(PROTECT1,0xFF);//���ö�·����66A(SRN-SRP33mV)����·��ʱ400us��RSNS=0.
IIC1_write_one_byte_CRC(PROTECT2,0xFF);//����OSDΪ100A(SRN-SRP50mV)����ʱ�����Ϊ1280ms��

}


/****************************************
fuction: void BQ_1_config(void)
description:BQ76930��ʼ��
Parameters: None
 //0x04�Ĵ���0x19��ӦSCD��ʱ70uS���ŵ��·��ѹ33mV��
 //0x05�Ĵ������ü�����Ϊ1-shotģʽ��
 //0x06�Ĵ���0x39��ӦOCD����ʱʱ��80mS���ŵ������ѹ33mV����·�͹�����Ӧ��������60A.
******************************************/
unsigned char BQ769_INITAdd[12]={SYS_STAT,CELLBAL1,CELLBAL2,CELLBAL3,SYS_CTRL1,SYS_CTRL2,PROTECT1,PROTECT2,PROTECT3,OV_TRIP,UV_TRIP,CC_CFG};
unsigned char BQ769_INITdata[12]={0xFF,     0x00,    0x00,     0x00,     0x18,    0x43,      0x00,     0x00,    0x00,    0x00,   0x00,  0x19};
/**
 * @brief BQ76930芯片配置函数
 * @description 通过I2C总线向BQ76930芯片写入12个配置寄存器的初始值
 *              配置内容包括系统状态、电池均衡、系统控制、保护设置等
 *              每个寄存器写入之间延时10ms确保稳定
 * @param 无
 * @return 无
 */
void BQ_1_config(void)
{
   char i;  // 循环计数器
   // 遍历12个配置寄存器，依次写入初始值
   for(i=0;i<12;i++)
    {
			delay_ms(10);  // 延时10ms，确保I2C写入稳定
			IIC1_write_one_byte_CRC(BQ769_INITAdd[i],BQ769_INITdata[i]);  // 向指定寄存器地址写入配置数据
    }
}

/****************************************
fuction: �����1��2��5��6��7��10�ֱ��ʾ������ϵ�1��6�ڵľ��⣬
         ������Ҫע�����ڵĵ�ش�����ͬʱ�������⡣���ھ����������ͬ��Ҫ�û������Լ�����������
description:
Parameters: None
******************************************/
void Battery1_Balance(void)
{
   IIC1_write_one_byte_CRC(CELLBAL1,0X01);
}

void Battery2_Balance(void)
{
   IIC1_write_one_byte_CRC(CELLBAL1,0X02);
}

void Battery5_Balance(void)
{
   IIC1_write_one_byte_CRC(CELLBAL1,0X10);
}

void Battery6_Balance(void)
{
   IIC1_write_one_byte_CRC(CELLBAL2,0X01);
}

void Battery7_Balance(void)
{
   IIC1_write_one_byte_CRC(CELLBAL2,0X02);
}

void Battery10_Balance(void)
{
   IIC1_write_one_byte_CRC(CELLBAL2,0X10);
}


/****************************************
fuction: void BQ_1_config(void)
description:BQ76930��ʼ��
Parameters: None
******************************************/
void BQ_2_config(void)
{
   char i;
   for(i=0;i<11;i++)
    {
			delay_ms(50);
    }
}
/****************************************
fuction:void SHIP_1_BQ769(void)
description:BQ76930����͹���ģʽ
Parameters: None
******************************************/
void SHIP_1_BQ769(void)
{
  IIC1_write_one_byte_CRC(SYS_CTRL1,0x19); //01
  delay_ms(20);
  IIC1_write_one_byte_CRC(SYS_CTRL1,0x1a); //10
 }

 


/****************************************
fuction:void SHIP_2_BQ769(void)
description:��BQ76930�͹���ģʽ����
Parameters: None
******************************************/
void WAKE_1_BQ769(void)
{
   MCU_WAKE_BQ_ONOFF(1);
	 delay_ms(50);
	 MCU_WAKE_BQ_ONOFF(0);
	 //NVIC_SystemReset();                       //����
 }

 
 /****************************************
fuction: void Get_BQCurrent(void)
description:BQ76940�����������������谴4m��/8����
Parameters: None
******************************************/
 /****************************************
fuction: void Get_BQ_Current(void)
description: 获取BQ76930芯片的电流值
             通过读取CC_HI_BYTE和CC_LO_BYTE寄存器获取原始电流数据
             根据数值范围判断充电或放电状态，并转换为实际电流值(mA)
             计算结果存储到Batteryval[17]和相关发送缓冲区
Parameters: None
返回值: 无，结果存储在全局变量中
******************************************/
 void Get_BQ_Current(void)
 {	 
   unsigned char readCurrentbuf[2];   // 存储读取的原始电流数据高字节和低字节
	 unsigned int    Currentbufval;     // 拼接后的16位原始电流值
	 float  Currentval;                 // 转换后的实际电流值(单位：mA)
   unsigned char Currentbuf[1];       // 预留缓冲区(未使用)
	 
	 // 读取电流值高字节寄存器
	 readCurrentbuf[1]=IIC1_read_one_byte(CC_HI_BYTE);
	 // 读取电流值低字节寄存器
   readCurrentbuf[0]=IIC1_read_one_byte(CC_LO_BYTE);
	 // 将高字节和低字节拼接成16位数据
   Currentbufval = readCurrentbuf[1];
   Currentbufval = (Currentbufval << 8)|readCurrentbuf[0];
	 // 判断电流方向：小于等于0x7D00为充电或零电流
	 if(  Currentbufval <= 0x7D00 )
	 {	 
		 // 充电状态：直接转换，单位mV，按4mΩ/8计算，结果单位mA
		 Currentval = (Currentbufval*2.11); 
		 Batteryval[17]=Currentval;        // 存储到电池数据数组
		 // 将16位电流值拆分为高字节和低字节
		 shang[36]=Batteryval[17]>>8;      // 高字节
		 shang[37]=Batteryval[17]&0X00FF;  // 低字节
		 // 复制到备用发送缓冲区
		 shang2[18]=shang[36];
		 shang2[19]=shang[37];
		 // 复制到CAN发送缓冲区
		 can_buf6[6]=(char)shang[36];
		 can_buf6[7]=(char)shang[37];
	 }
   else
	 {		  
		 // 放电状态：用0xFFFF减去原始值取补码，再转换
		 Currentval = ((0XFFFF - Currentbufval )*2.11);
		 Batteryval[17]=Currentval;
		 // 同样拆分高低字节到各发送缓冲区
		 shang[36]=Batteryval[17]>>8;
		 shang[37]=Batteryval[17]&0X00FF;
		 shang2[18]=shang[36];
		 shang2[19]=shang[37];		 
		 can_buf6[6]=(char)shang[36];
		 can_buf6[7]=(char)shang[37];
	 }		 	 
 }
 /****************************************
fuction: void Get_BQ_1_Temp(void)
description:BQ76930 103AT�¶Ȳ���
Parameters: None
******************************************/

 float  Tempval_1,Tempval_2,Tempval_3,Tempval_4;
 void Get_BQ1_1_Temp(void)
 {
	 float Rt=0;
   float Rp=10000;
   float T2=273.15+25;
   float Bx=3380;
   float Ka=273.15;
   unsigned char readTempbuf[2];
	 int  TempRes;
   unsigned char Tempbuf[1];
	 readTempbuf[1]=IIC1_read_one_byte(TS1_HI_BYTE);
   readTempbuf[0]=IIC1_read_one_byte(TS1_LO_BYTE);
   TempRes = (readTempbuf[1] << 8 ) | readTempbuf[0];
	 TempRes = (10000*(TempRes*382/1000))/(3300-(TempRes*382/1000)); 
   Tempval_1 = 1/(1/T2+(log(TempRes/Rp))/Bx)- Ka + 0.5;
	 Batteryval[18] = Tempval_1;
   	 	 
 }


 void Get_BQ1_2_Temp(void)
 {
   float Rt=0;
   float Rp=10000;
   float T2=273.15+25;
   float Bx=3380;
   float Ka=273.15;
   unsigned char readTempbuf[2];
	 int  TempRes;
   unsigned char Tempbuf[1];
	 readTempbuf[1]=IIC1_read_one_byte(TS1_HI_BYTE);
   readTempbuf[0]=IIC1_read_one_byte(TS1_LO_BYTE);
   TempRes = (readTempbuf[1] << 8 ) | readTempbuf[0];
	 TempRes = (10000*(TempRes*382/1000))/(3300-(TempRes*382/1000)); 
   Tempval_2 = 1/(1/T2+(log(TempRes/Rp))/Bx)- Ka + 0.5;
	 Batteryval[18] = Tempval_2;
   shang[38]=Batteryval[18];	 	 
	 shang3[2]=shang[38];	 
	can_buf7[2]=(char)shang[38];

 }
  
 unsigned char BMS_sta,DSG_STA,CHG_STA,DSG_STA_FLAG,CHG_STA_FLAG;	
void BMS_STA(void)
	{
		//简单说： 这个函数就是告诉系统"现在是在充电还是放电"
   BMS_sta = IIC1_read_one_byte(SYS_CTRL2);
   DSG_STA = BMS_sta&0x02;
	 CHG_STA = BMS_sta&0x01;
	 shang[39]=DSG_STA;
	 shang[40]=CHG_STA;
		
	can_buf7[3]=(char)shang[39];
	can_buf7[4]=(char)shang[40];

	}
 
 void Only_Open_CHG(void)
	{
		BMS_STA();
		if(DSG_STA!=0)
		{
	    IIC1_write_one_byte_CRC(SYS_CTRL2,0X43);	
		}
		else {IIC1_write_one_byte_CRC(SYS_CTRL2,0X41);}
	}
 void Only_Close_CHG(void)
	{
		BMS_STA();
		if(DSG_STA!=0)
		{
	    IIC1_write_one_byte_CRC(SYS_CTRL2,0X42);	
		}
		else
		{IIC1_write_one_byte_CRC(SYS_CTRL2,0X40);	}
	}
	
	void Only_Open_DSG(void)
	{
		BMS_STA();
		if(CHG_STA!=0)
		{
	    IIC1_write_one_byte_CRC(SYS_CTRL2,0X43);	
		}
		else
		{IIC1_write_one_byte_CRC(SYS_CTRL2,0X42);}	
	}
  void Only_Close_DSG(void)
	{
		BMS_STA();
		if(CHG_STA!=0)
		{
	    IIC1_write_one_byte_CRC(SYS_CTRL2,0X41);	
		}
		else
		{IIC1_write_one_byte_CRC(SYS_CTRL2,0X40);	}
	}
	
	 void Open_DSG_CHG(void)
	{
	 IIC1_write_one_byte_CRC(SYS_CTRL2,0X43);
   		
	}
 void Close_DSG_CHG(void)
	{
	 IIC1_write_one_byte_CRC(SYS_CTRL2,0X40);	
	}
 
 
 
 
 void Update_val(void)
{

	//将所有采集到的电池数据，通过串口、USART2、CAN发送出去，并在显示屏上更新显示。
  char NEW[50]={0};
	int n;

	  for(n=0;n<50;n++)

		{
			USART_SendData(USART1, shang[n]); //����һ���ֽ�����
			delay_ms(2);
			
		}
		
	  USART2_Printf( shang1,20,ASCII_CODE);	
		delay_ms(100);
		USART2_Printf( shang2,20,ASCII_CODE);
		delay_ms(100);
		USART2_Printf( shang3,20,ASCII_CODE);

    Can_Send_Msg(can_buf1,8,0x0001);
		delay_ms(2);
		Can_Send_Msg(can_buf2,8,0x0002);
		delay_ms(2);
		Can_Send_Msg(can_buf3,8,0x0003);
		delay_ms(2);
		Can_Send_Msg(can_buf4,8,0x0004);
		delay_ms(2);
		Can_Send_Msg(can_buf5,8,0x0005);
		delay_ms(2);
		Can_Send_Msg(can_buf6,8,0x0006);
		delay_ms(2);
		Can_Send_Msg(can_buf7,8,0x0007);
    delay_ms(2);
		
  UartSend("CLR(61);\r\n");
  delay_ms(100);
	UartSend("CLR(61);\r\n");
  delay_ms(100);
  UartSend("DIR(1);\r\n");
		delay_ms(100);
	sprintf(NEW,"DCV16(0,0,'%s%d%s',3);\r\n","��һ�ڵ�ѹ:",Batteryval[0],"mV"); 
  UartSend(NEW); 
  
	delay_ms(100); 

	sprintf(NEW,"DCV16(0,20,'%s%d%s',3);\r\n","�ڶ��ڵ�ѹ:",Batteryval[1],"mV"); 
  UartSend(NEW); 
		
  delay_ms(100);
  
	
	sprintf(NEW,"DCV16(0,40,'%s%d%s',3);\r\n","�����ڵ�ѹ:",Batteryval[4],"mV"); 
  UartSend(NEW); 
  
	delay_ms(100); 
	sprintf(NEW,"DCV16(0,60,'%s%d%s',3);\r\n","���Ľڵ�ѹ:",Batteryval[5],"mV"); 
  UartSend(NEW); 
  
	delay_ms(100); 
	sprintf(NEW,"DCV16(0,80,'%s%d%s',3);\r\n","����ڵ�ѹ:",Batteryval[6],"mV"); 
  UartSend(NEW); 
  
	delay_ms(100); 
	sprintf(NEW,"DCV16(0,100,'%s%d%s',3);\r\n","�����ڵ�ѹ:",Batteryval[9],"mV"); 
  UartSend(NEW); 
		delay_ms(1000);
	UartSend("CLR(61);\r\n");

  delay_ms(100); 
	sprintf(NEW,"DCV16(0,0,'%s%d%s',3);\r\n","���߽ڵ�ѹ:",Batteryval[10],"mV"); 
  UartSend(NEW);
	
	delay_ms(100); 
	sprintf(NEW,"DCV16(0,20,'%s%d%s',3);\r\n","�ڰ˽ڵ�ѹ:",Batteryval[11],"mV"); 
  UartSend(NEW);
	
	delay_ms(100); 
	sprintf(NEW,"DCV16(0,40,'%s%d%s',3);\r\n","�ھŽڵ�ѹ:",Batteryval[14],"mV"); 
  UartSend(NEW);
	
	delay_ms(100); 
	sprintf(NEW,"DCV16(0,60,'%s%d%s',3);\r\n","�ܵ�ѹ:",Batteryval[15],"mV");	
  UartSend(NEW); 
  
  delay_ms(100); 
	sprintf(NEW,"DCV16(0,80,'%s%d%s',3);\r\n","���SOCΪ:",Batteryval[16],"%"); 
  UartSend(NEW); 
  
	delay_ms(100); 
	sprintf(NEW,"DCV16(0,100,'%s%.2f%s',3);\r\n","����¶�Ϊ:",Tempval_2,"��"); 
  UartSend(NEW); 
		delay_ms(1000);
	UartSend("CLR(61);\r\n");

	delay_ms(100); 
	sprintf(NEW,"DCV16(0,00,'%s%d%s',3);\r\n","��ǰ����Ϊ:",Batteryval[17],"mA"); 
  UartSend(NEW); 
  
	delay_ms(100);	
	sprintf(NEW,"DCV16(0,20,'%s',3);\r\n","HWLLO WORLD ��"); 
  UartSend(NEW);
	
	delay_ms(1000);
	
	
	

}



void Update_val_new(void)
{
    // ֻ��ӡ��һ����ѹ����λmV
    printf("��һ�ڵ�ѹ: %d mV\r\n", Batteryval[0]);
		delay_ms(500);
}






 void Get_Update_Data(void)
{	  
    Get_Battery1();
    Get_Battery2();
    //Get_Battery3();
	 // Get_Battery4();
	  Get_Battery5();
	  Get_Battery6();
	  Get_Battery7();
	 // Get_Battery8();
	  //Get_Battery9();
	  Get_Battery10();
	  Get_Battery11();
    Get_Battery12();
    //Get_Battery13();
   // Get_Battery14();
    Get_Battery15(); 	
		Get_Update_ALL_Data();//计算总电压
	  Get_SOC();            //获取电池荷电状态(SOC)
		Get_BQ1_2_Temp();     //获取BQ芯片温度2
    Get_BQ_Current();	    //获取BQ芯片电流
    BMS_STA();	          //获取BMS状态
		Update_val();			    //更新显示数据
}

 
 
 
 
/****************************************
fuction:void readbqstate(void)
description:��ȡ�����ź�ֵ
Parameters: UV_Alarm_flag?OOV_Alarm_flag
            SCD_Alarm_flag,OCD_Alarm_flag
******************************************/

 int UV_Alarm_flag,OV_Alarm_flag,SCD_Alarm_flag,OCD_Alarm_flag;
void ALERT_1_Recognition(void)
{
	
  unsigned char sys_stat_1,sys_stat_2,UV_1,OV_1,UV_2,OV_2,SCD,OCD;
  sys_stat_1 = IIC1_read_one_byte(SYS_STAT);//��ȡ״̬
  UV_1  =  sys_stat_1&0x08;  //ȡ��UVλ
  OV_1  =  sys_stat_1&0x04;
  SCD   =  sys_stat_1&0x02;
  OCD   =  sys_stat_1&0x01;
  if((UV_1 == 0x08)||(UV_2 == 0x08))
  {
      UV_Alarm_flag = 1;    //Ƿѹ����
		  printf("pack UV\n");
  }	
   else
     UV_Alarm_flag = 0;     //û��Ƿѹ
     if((OV_1 == 0x04)||(OV_2 == 0x04))
      {
       OV_Alarm_flag = 1;			 
		   printf("pack OV\n");
      }
        else
           OV_Alarm_flag = 0;
           if(SCD == 0x02)
						{
							SCD_Alarm_flag = 1;
							printf("pack SCD\n");		
						}
							else
									SCD_Alarm_flag = 0;
 
									if(OCD == 0x01)
										{
											OCD_Alarm_flag = 1;
											printf("pack OCD\n");		
										}   
											else
													OCD_Alarm_flag = 0;	
}



unsigned char CRC8(unsigned char *ptr, unsigned char len,unsigned char key)
{
	unsigned char i;
	unsigned char crc=0;
	while(len--!=0)
	{
		for(i=0x80; i!=0; i/=2)
		{
			if((crc & 0x80) != 0)
			{
				crc *= 2;
				crc ^= key;
			}
			else
				crc *= 2;

			if((*ptr & i)!=0)
				crc ^= key;
		}
		ptr++;
	}
	return(crc);
}

