//------------------------------------------ KHAI BAO THU VIEN------------------------------------------------------------------------
#include "stm32f4xx.h"
#include "pwm_gpio.h"
#include "delay.h"
#include "math.h"
#include "hamcon.h"
#include <stdio.h>
#include "lcd.h"
#include "Init_Main_F4.h"
#include "config_encoder.h"

//------------------------------------------KHAI BAO BIEN TOAN CUC-----------------------------------------------------------------------------

int i,demlcd,ttssk0, ttswk1, ttkup;
volatile uint8_t rxdata1_index = 0;
int demss1=0, demss2=0, demss3=0, demss4=0, demss5=0, demss6=0, demss7=0, demss8=0; 
int sensor1, sensor2, sensor3,sensor4,sensor5,sensor6,sensor7;

u8 ss1, ss2, ss3, ss4, ss5, ss6, ss7, ss8;
u8 tt=0, step=0; // 
u8 swk0, swk1, swkup; // trang thai nut nhan
u8 ena,sendrx;
u8 vquay;
u8 ena1, ena2, ena3, ena4, ena5, ena6;
u8 stepban;

int16_t gocset2, goclech2,gocrb;
  int16_t vantocquay;
vs16 goclabanget = 0;

u32 tick_time_gu32; // gia tri system tick 
u32 TimeDelay,timer=0;// bien dung trong delay bang system tick

vs32 TestencoderTimer3;
vs32 TestencoderTimer2;
vs32 TestencoderTimer4;
vs32 TestencoderTimer5;
vs32 tangtocban, giamtocban, giamtoclaycon;
int nhandata;

char line[15]; //gia tri doc duoc tu line
char swread[20];//luu gia tri doc duoc tu nhan
char trangthaichay[10];//trang thai chay, mode rb
char goc[20]; // mang goc
char demlinedong1[20]; // mang dem line dong 1
char demlinedong2[20]; // mang dem line dong 2
char modelcd[20]; // mang mode LCD
char speed[20]; // mang toc do
char goc2[20]; //mang goc 2
char encoder[20]; // mang doc encoder
char vector1[20]; // mang vecto1
char vector2[20]; // mang vecto2
char vector3[20]; // mang vecto3
char vector4[20]; // mang vecto4

float vecto1, vecto2;
float vecto3, vecto4;


vu32 var_i=0;
u8 getchar_u8=0;
#define MAX_STRLEN 100
char received_string[MAX_STRLEN+1]; // this will hold the recieved string
u8 JoysticXL;
u8 JoysticYL;
u8 JoysticXR;
u8 JoysticYR;
char str_rev[MAX_STRLEN];
char str[MAX_STRLEN];

int GetUSART(USART_TypeDef* USARTx)
{
  while (USART_GetFlagStatus(USARTx, USART_IT_RXNE) == RESET)
  {}
  return USART_ReceiveData(USARTx);
}

//----------------------------------------------------CHUONG TRINH CHINH---------------------------------------------------------------------
int main()




{




	Config_timer67();
	 pwm_Config();
   gpio_Config(); 

	 lcd_Init();
	 ConfigEncoder();
   config_uart1(115200);
	config_uart2(115200);
	config_uart3(115200);
	 USART_SendData(USART1, 'a');
	 SysTick_Config(SystemCoreClock / 1000); 


	 while(1)
     {

//	nhandata=GetUSART(USART2);
       ReadLine();
			 ReadSensor();
			 TestencoderTimer4=ReadEncoder(4);
			 TestencoderTimer5=ReadEncoder(5);
     // DungGiuViTri();
      ChayAllV1();
			// BanTz1Nghich(95, -10300,9);
			 //DongCoBan(10,1);
			// Ban(60,5000,12);
			 //tinhtiencolaban(30,90,30,0);
//if(sensor2==0)
//	{
//	 KhiNen(1,1);
//	}
//	else{KhiNen(1,0);}
			// TestCamBien();
}
		 
}
