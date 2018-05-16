#include "pwm_gpio.h"
 

void pwm_Pa(int p, int pwm)
{
	switch (p)
 {
		case 6:{TIM3 -> CCR1 = pwm; break;}
	  case 7:{TIM3 -> CCR2 = pwm; break;}
 }
} 

void pwm_Pb(int p, int pwm)
{
  switch (p)
 {
    case 0: {TIM3 -> CCR3 = pwm; break;}
		case 1: {TIM3 -> CCR4 = pwm; break;}
 }		
}

void pwm_Pe(int p, int pwm)
{
  switch (p)
 {
    case 9:  {TIM1 -> CCR1 = pwm; break;}
		case 11: {TIM1 -> CCR2 = pwm; break;}
    case 13: {TIM1 -> CCR3 = pwm; break;}
		case 14: {TIM1 -> CCR4 = pwm; break;}
		
 }		
}	

void gpio_Pa(int p, int logic)
{
	  switch(p)
			{
      case 6: {GPIO_WriteBit(GPIOA, GPIO_Pin_6, (BitAction)logic); break;}	
			case 11: {GPIO_WriteBit(GPIOA, GPIO_Pin_11, (BitAction)logic); break;}
			case 15: {GPIO_WriteBit(GPIOA, GPIO_Pin_15, (BitAction)logic); break;}	
      }			
}	

void gpio_Pb(int p, int logic)
{
	  switch(p)
			{			
			case 15: {GPIO_WriteBit(GPIOB, GPIO_Pin_15, (BitAction)logic); break;}		
			}			
}	
		
void gpio_Pc(int p, int logic)
{
	  switch(p)
			{
			case 4: {GPIO_WriteBit(GPIOC, GPIO_Pin_4, (BitAction)logic); break;}	
			case 5: {GPIO_WriteBit(GPIOC, GPIO_Pin_5, (BitAction)logic); break;}				
			case 9: {GPIO_WriteBit(GPIOC, GPIO_Pin_9, (BitAction)logic); break;}		
			}			
}	
	
void gpio_Pd(int p, int logic)
{
	  switch(p)
			{
			case 9: {GPIO_WriteBit(GPIOD, GPIO_Pin_9, (BitAction)logic); break;}	
			case 11: {GPIO_WriteBit(GPIOD, GPIO_Pin_11, (BitAction)logic); break;}				
			case 13: {GPIO_WriteBit(GPIOD, GPIO_Pin_13, (BitAction)logic); break;}		
			case 15: {GPIO_WriteBit(GPIOD, GPIO_Pin_15, (BitAction)logic); break;}				
			}			
}		

void gpio_Pe(int p, int logic)
{
	  switch(p)
			{
			case 7: {GPIO_WriteBit(GPIOE, GPIO_Pin_7, (BitAction)logic); break;}	
			case 8: {GPIO_WriteBit(GPIOE, GPIO_Pin_8, (BitAction)logic); break;}	
			case 10: {GPIO_WriteBit(GPIOE, GPIO_Pin_10, (BitAction)logic); break;}	
			case 12: {GPIO_WriteBit(GPIOE, GPIO_Pin_12, (BitAction)logic); break;}				
			case 15: {GPIO_WriteBit(GPIOE, GPIO_Pin_15, (BitAction)logic); break;}							
			}			
}		
