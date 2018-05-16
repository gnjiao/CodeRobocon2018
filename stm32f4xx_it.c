
#include "stm32f4xx_it.h"
#include "stdlib.h"
#include "stdio.h"

extern uint8_t rxdata1_index;
char rxdata1[2];
extern uint32_t GocLaBan;
extern u32 tick_time_gu32;
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
//extern vu32 tick_time_gu32;
////extern char Command_compass;
void robotAnalytics(void);

void TIM6_DAC_IRQHandler(void)// INTERRUPTS TIM6
{ 
  
	TIM_ClearITPendingBit(TIM6, TIM_IT_Update);//xóa co ngat
	//robotAnalytics();
	
}

extern u32 TimeDelay,timer;
void SysTick_Handler(void)
{
	if( TimeDelay!=0)
		{
			TimeDelay--;
		}
	if (++timer>10)
		{
			 USART_SendData(USART1, 'z');
			 timer=0;
		}
	tick_time_gu32++;
}
extern volatile int16_t rx1[2]; //mang hien thi lcd 
extern vs16 goclabanget;
extern volatile int16_t byteH;
extern volatile int16_t byteL;
extern vs16 IMU;
extern vu8 RX_USART1[15];
void DMA2_Stream5_IRQHandler(void)// ngat DMA uart1 RX
{
	    
			DMA_ClearITPendingBit(DMA2_Stream5,DMA_IT_TCIF5);
			goclabanget=((RX_USART1[0]<<8)|RX_USART1[1]);

}
extern u8 getchar_u8;
#define MAX_STRLEN 100 // this is the maximum string length of our string in characters
extern char received_string[MAX_STRLEN+1]; // this will hold the recieved string
extern char str_rev[MAX_STRLEN];
extern char str[MAX_STRLEN];
extern u8 JoysticXL;
extern u8 JoysticYL;
extern u8 JoysticXR;
extern u8 JoysticYR;
void USART2_IRQHandler(void) 
	{
	int i;
	int j;
	static char ch[10];
	if(USART_GetITStatus(USART2,USART_IT_RXNE)==SET) // Cho ky tu
	{
		static u8 cnt;
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);// Xoa co ngat
		getchar_u8=USART_ReceiveData(USART2); // Lay mot ky tu
		if( (getchar_u8 != '\n') && (getchar_u8 < MAX_STRLEN) ){ 
			received_string[cnt] = getchar_u8; // Lay mot chuoi ky tu
			cnt++;
			
		}else{ // otherwise reset the character counter and print the received string
			cnt = 0;
		}
		if(received_string[0]=='W' && received_string[4]=='P' ){//
				for(i = 0; i < 8 ; i++){//
					str_rev[i] = received_string[i];//
					if(str_rev[i] == 13) str_rev[i] = 32;//
				}
				if(atoi(&str_rev[5]) == 0 ) str_rev[6]=str_rev[7]=32;//
				
					JoysticXL = atoi(&received_string[1]);
					JoysticYL = atoi(&received_string[5]);

				
		}else if(received_string[0]=='W' && received_string[3]=='P' ){
				for(i = 0; i < 8 ; i++){
					str_rev[i] = received_string[i];
					if(str_rev[i] == 13) str_rev[i] = 32;
				}
				if(atoi(&str_rev[4]) == 0 ) str_rev[6]=str_rev[7]=32;
				
				JoysticXL = atoi(&received_string[1]);
				JoysticYL = atoi(&received_string[4]);
				
		}else if(received_string[0]=='W' && received_string[2]=='P' ){
				for(i = 0; i < 8 ; i++){
					str_rev[i] = received_string[i];
					if(str_rev[i] == 13) str_rev[i] = 32;
				}
				if(atoi(&str_rev[3]) == 0 ) str_rev[5]=str_rev[6]=str_rev[7]=32;
				if(atoi(&str_rev[1]) == 0 ) str_rev[6]=str_rev[7]=32;
				
				JoysticXL = atoi(&received_string[1]);
				JoysticYL = atoi(&received_string[3]);
				
		}
		if(received_string[0]=='Q' && received_string[4]=='S' ){
				for(j = 0; j < 8 ; j++){
					str[j] = received_string[j];
					if(str[j] == 13) str[j] = 32;
				}
				if(atoi(&str[5]) == 0 ) str[6]=str[7]=32;
				
					JoysticXR = atoi(&received_string[1]);
					JoysticYR = atoi(&received_string[5]);				
				
		}else if(received_string[0]=='Q' && received_string[3]=='S' ){
				for(j = 0; j < 8 ; j++){
					str[j] = received_string[j];
					if(str[j] == 13) str[j] = 32;
				}
				if(atoi(&str[4]) == 0 ) str[6]=str[7]=32;
				
					JoysticXR = atoi(&received_string[1]);
					JoysticYR = atoi(&received_string[4]);				
				
		}else if(received_string[0]=='Q' && received_string[2]=='S' ){
				for(j = 0; j < 8 ; j++){
					str[j] = received_string[j];
					if(str[j] == 13) str[j] = 32;
				}
				if(atoi(&str[3]) == 0 ) str[5]=str[6]=str[7]=32;
				if(atoi(&str[1]) == 0 ) str[6]=str[7]=32;
				
					JoysticXR = atoi(&received_string[1]);
					JoysticYR = atoi(&received_string[3]);				
				
		}		
	}			
}
		
	
void USART1_IRQHandler(void) 
{

//	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET) // Cho ky tu
//	{
//		if(rxdata1_index < 2)
//		{
//			
//			rx1[rxdata1_index] = USART_ReceiveData(USART1);
//			rxdata1_index++;
//		}
//		if (rxdata1_index == 2)
//		{

//			 goclabanget =  ((rx1[0]) << 8) + rx1[1];// Lay ket qua
//			 rxdata1_index = 0;
//		}
//		USART_ClearITPendingBit(USART1,USART_IT_RXNE);// Xoa co ngat
//	}
}





	
/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
