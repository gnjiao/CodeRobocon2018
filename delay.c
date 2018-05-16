#include "delay.h"
extern u32 TimeDelay;
void Delay_ms_Systemtick(u32 time)
	{
		TimeDelay=time;
		while (TimeDelay !=0){}
		
	}
//	void delay_us( u32 del)
//	{
//		int a;
//		while(del--)
//		{
//		a=168000/4000;
//		while(--a);
//		}
//		
//	}
//	
//	void delay_ms(u32 del)
//	{
//		int a;
//		while(del--)
//		{
//		a=168000/4;
//		while(--a);
//		}
//		
//	}

