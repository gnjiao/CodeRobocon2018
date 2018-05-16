#ifndef _PWMCH3CH1_H_
 #define _PWMCH3CH1_H_
 
 #include "stm32f4xx.h"
 

void pwm_Config(void);// Config, khoi tao timer 3, timer 1 chanel 1>4 

void pwm_Pa(int p, int pwm); // Pwm pin PA(x, muc pwm max=255). Kich muc thap
 
void pwm_Pb(int p, int pwm);// Pwm pin PB(x, muc pwm max=255). Kich muc thap

void pwm_Pe(int p, int pwm); // Pwm pin PE(x, muc pwm max=255). Kich muc thap

#endif  
