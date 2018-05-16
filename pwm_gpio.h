#ifndef _PWM_GPIO_H_
 #define _PWM_GPIO_H_
 
 #include "stm32f4xx.h"
 

void pwm_Pa(int p, int pwm); // Pwm pin PA(x, muc pwm max=255). Kich muc thap

void pwm_Pb(int p, int pwm); // Pwm pin PB(x, muc pwm max=255). Kich muc thap

void pwm_Pe(int p, int pwm); // Pwm pin PE(x, muc pwm max=255). Kich muc thap

void gpio_Pa(int p, int logic); // Gpio pin PA(x, muc logic 1/0).

void gpio_Pb(int p, int logic); // Gpio pin PB(x, muc logic 1/0).

void gpio_Pc(int p, int logic); // Gpio pin PC(x, muc logic 1/0).

void gpio_Pd(int p, int logic); // Gpio pin PD(x, muc logic 1/0).

void gpio_Pe(int p, int logic); // Gpio pin PE(x, muc logic 1/0).


#endif  
