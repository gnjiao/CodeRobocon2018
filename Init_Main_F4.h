#ifndef _INIT_MAIN_F4_H_
 #define _INIT_MAIN_F4_H_
 
 
 #include "stm32f4xx.h"

 
void pwm_Config(void);// Config, khoi tao timer 3, timer 1 chanel 1>4 

void gpio_Config(void); // Khoi tao Gpio 

void config_uart1(uint32_t baudrate);

void config_uart2(int baudrate);
 
void config_uart3(uint32_t baudrate);
 
void config_uart4(uint32_t baudrate);
 
void Config_timer67(void);

void Config_int_time6(void);

void delay_us(u32 del);

void delay_ms(u32 del);
 
 #endif  
