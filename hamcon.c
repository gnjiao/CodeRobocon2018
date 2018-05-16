#include "hamcon.h"
#include "pwm_gpio.h"
#include <stdio.h>
#include <math.h>
#include "lcd.h"
#include <stdlib.h>
#include "config_encoder.h"
#include "delay.h"
u8 stepquay, stepchayve;
extern vs32 TestencoderTimer3,TestencoderTimer2,TestencoderTimer4,TestencoderTimer5;
vs32 x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12;
vs32 xdiemmoc1, xdiemmoc2;
int lanbantz1, lanbantz2, lanbantz3;
vs32 readencoder;
extern vs32 tangtocban, giamtocban, giamtoclaycon;
vs32 diemkhong, diemlaycon, diemdung, diemnhacon;
extern u8 stepban;
int tocdothucban;
u8 hesogiatoc;
int xungdemduoc;
extern int ttssk0, ttswk1, ttkup;
extern int demlcd;
int ttss1=0, ttss2=0, ttss3=0, ttss4=0, ttss5=0, ttss6=0, ttss7=0, ttss8=0; // trang thai ss1>ss8
extern int demss1, demss2, demss3, demss4, demss5, demss6, demss7, demss8; // bien dem ss1>ss8
int16_t goclech;
float vtt, vtt1, vtt2, vtt3, vtt4; // Van toc goc tinh tien va van toc quay goc
extern int16_t goclabanget; // goc la ban tra ve
extern u8 ss1, ss2, ss3, ss4, ss5, ss6, ss7, ss8; // gia tri cua 8 sensor do line
extern u8 tt, step; // tt la trang thai, ttss8 la so lan cham line ss8, step la buoc hien tai thuc hien
extern u8 swk0, swk1, swkup; // gia tri nut nhan tren board
extern u8 ena, vquay ; // cho phep/khong cho phep rb chay 1 step nao do
extern int16_t gocset2, goclech2, gocrb,vantocquay;

extern float vecto1, vecto2;
extern float vecto3, vecto4;

extern int sensor1, sensor2, sensor3,sensor4,sensor5,sensor6,sensor7;
int stepchay; 
int dir1, dir2, dir3, dir4;
int buoctocdoban, hesotocdoban,hesodiemgiatoc;

float Pi=3.141492654;
float Gocradian = 0.01745329252;
void ReadLine()
{
   ss8 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_12); // ss so 1 v
   ss7 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_10); // ss so 2 v	
   ss6 = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12); // ss so 3 v
   ss5 = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8);  // ss so 4 v
   ss4 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_11); // ss so 5 v
   ss3 = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15); // ss so 6 v		
   ss2 = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11); // ss so 7
   ss1 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9);  // ss so 8 		
	
	 if(ss1==1&&ttss1==0)
       {
			  demss1++;
			  ttss1=1;}
   if(ss1==0)
       {ttss1=0;}
			 
	 if(ss2==1&&ttss2==0)
       {
			  demss2++;
			  ttss2=1;}
   if(ss2==0)
       {ttss2=0;}	
			 
	 if(ss3==1&&ttss3==0)
       {
			  demss3++;
			  ttss3=1;}
   if(ss3==0)
       {ttss3=0;}	  

   if(ss4==1&&ttss4==0)
       {
			  demss4++;
			  ttss4=1;}
   if(ss4==0)
       {ttss4=0;}
			 
	 if(ss5==1&&ttss5==0)
       {
			  demss5++;
			  ttss5=1;}
   if(ss5==0)
       {ttss5=0;}	
			 
	 if(ss6==1&&ttss6==0)
       {
			  demss6++;
			  ttss6=1;}
   if(ss6==0)
       {ttss6=0;}		

	 if(ss7==1&&ttss7==0)
       {
			  demss7++;
			  ttss7=1;}
   if(ss7==0)
       {ttss7=0;}	
			 
	 if(ss8==1&&ttss8==0)
       {
			  demss8++;
			  ttss8=1;}
   if(ss8==0)
       {ttss8=0;}						 
			 
}
void ReadSw()
	{
	 swk0 = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4);
	 swk1 = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3);	
	 //swkup = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);	
	 //if(swk0==0){ena=1;}	// sw k0 nhan thi cho phep chay rb 
	 if(swk1==0&&ena==0){demlcd++;	lcd_Clear();ena=1;}	// sw k1 nhan thi reset step = 0
	 //if(swkup == 1 && ttkup == 0){demlcd++;	lcd_Clear(); ttkup=1;}	// Thay doi mode hien thi
	 if(swkup == 0){ttkup=0;}
	 if(demlcd==6){demlcd=0;}
	}
	
void ReadSensor()
	{
    sensor1=(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0));
    sensor2=(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1));		
    sensor3=(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8));
    sensor4=(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9));				
		sensor5=(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6));		
    sensor6=(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7));
    sensor7=(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3));		
	}

void tinhtienkhonglaban(int vtinhtien, int goctinhtien)
	{
		
vecto1 = vtinhtien*(float)cos((Gocradian*goctinhtien)-(135*Gocradian));
vecto2 = vtinhtien*(float)cos((Gocradian*goctinhtien)+(135*Gocradian));
vecto3 = vtinhtien*(float)cos((Gocradian*goctinhtien)+(45*Gocradian));
vecto4 = vtinhtien*(float)cos((Gocradian*goctinhtien)-(45*Gocradian));

if(vecto1>=0){dir1=1; vtt1=vecto1;}
if(vecto2>=0){dir2=1; vtt2=vecto2;}
if(vecto3>=0){dir3=1; vtt3=vecto3;}
if(vecto4>=0){dir4=1; vtt4=vecto4;}

if(vecto1<0){dir1=0; vtt1=-vecto1;}
if(vecto2<0){dir2=0; vtt2=-vecto2;}
if(vecto3<0){dir3=0; vtt3=-vecto3;}
if(vecto4<0){dir4=0; vtt4=-vecto4;}

pwm_Pa(7, vtt1);
gpio_Pc(5, dir1);

pwm_Pb(1, vtt2);
gpio_Pe(8, dir2);

pwm_Pb(0, vtt3);
gpio_Pe(7, dir3);


pwm_Pa(6, vtt4);
gpio_Pc(4, dir4);

	}	
void tinhtienkhonglaban3banh(int vtinhtien, int goctinhtien)
	{
		
vecto1 = vtinhtien*(float)cos((Gocradian*goctinhtien)-(180*Gocradian));
vecto2 = vtinhtien*(float)cos((Gocradian*goctinhtien)+(60*Gocradian));
vecto3 = vtinhtien*(float)cos((Gocradian*goctinhtien)-(60*Gocradian));


if(vecto1>=0){dir1=1; vtt1=vecto1;}
if(vecto2>=0){dir2=1; vtt2=vecto2;}
if(vecto3>=0){dir3=1; vtt3=vecto3;}

if(vecto1<0){dir1=0; vtt1=-vecto1;}
if(vecto2<0){dir2=0; vtt2=-vecto2;}
if(vecto3<0){dir3=0; vtt3=-vecto3;}




pwm_Pb(1, vtt1);
gpio_Pe(8, dir1);

pwm_Pa(6, vtt2);
gpio_Pc(4, dir2);

pwm_Pb(0, vtt3);
gpio_Pe(7, dir3);
	
	}	
	
	
void tinhtiencolaban(int vtinhtien, int goctinhtien, int vquay, int gocquay)
	{
goclech = (goclabanget)/10-gocquay;
		
		
	 if((goclech>=0))
		 {      
			      vantocquay=goclech*2;
			 if(vantocquay>vquay){vantocquay=vquay;}

			 
		 }
	  if(goclech<0)
		 {    
      			vantocquay=(goclech*2);
			 if(vantocquay<-vquay){vantocquay=-vquay;}

		 
		 } 	


vecto1 = vtinhtien*(float)cos((Gocradian*goctinhtien)-(Gocradian*gocquay)-(135*Gocradian)) - vantocquay;
vecto2 = vtinhtien*(float)cos((Gocradian*goctinhtien)-(Gocradian*gocquay)+(135*Gocradian)) - vantocquay;
vecto3 = vtinhtien*(float)cos((Gocradian*goctinhtien)-(Gocradian*gocquay)+(45*Gocradian))  - vantocquay;
vecto4 = vtinhtien*(float)cos((Gocradian*goctinhtien)-(Gocradian*gocquay)-(45*Gocradian))  - vantocquay;

		 


		 
if(vecto1>=0){dir1=1; vtt1=vecto1;}
if(vecto2>=0){dir2=1; vtt2=vecto2;}
if(vecto3>=0){dir3=1; vtt3=vecto3;}
if(vecto4>=0){dir4=1; vtt4=vecto4;}

if(vecto1<0){dir1=0; vtt1=-vecto1;}
if(vecto2<0){dir2=0; vtt2=-vecto2;}
if(vecto3<0){dir3=0; vtt3=-vecto3;}
if(vecto4<0){dir4=0; vtt4=-vecto4;}

pwm_Pa(7, vtt1);
gpio_Pc(5, dir1);

pwm_Pb(1, vtt2);
gpio_Pe(8, dir2);

pwm_Pb(0, vtt3);
gpio_Pe(7, dir3);


pwm_Pa(6, vtt4);
gpio_Pc(4, dir4);

	}	
	
void tinhtiencolaban3banh(int vtinhtien, int goctinhtien, int vquay, int gocquay)
	{
goclech = (goclabanget)/10-gocquay;
		
		
	 if((goclech>=0))
		 {      
			      vantocquay=goclech*2;
			 if(vantocquay>vquay){vantocquay=vquay;}

			 
		 }
	  if(goclech<0)
		 {    
      			vantocquay=(goclech*2);
			 if(vantocquay<-vquay){vantocquay=-vquay;}

		 
		 } 	


vecto1 = vtinhtien*(float)cos((Gocradian*goctinhtien)-(Gocradian*gocquay)-(180*Gocradian)) - vantocquay;
vecto2 = vtinhtien*(float)cos((Gocradian*goctinhtien)-(Gocradian*gocquay)+(60*Gocradian)) - vantocquay;
vecto3 = vtinhtien*(float)cos((Gocradian*goctinhtien)-(Gocradian*gocquay)-(60*Gocradian))  - vantocquay;


		 
if(vecto1>=0){dir1=1; vtt1=vecto1;}
if(vecto2>=0){dir2=1; vtt2=vecto2;}
if(vecto3>=0){dir3=1; vtt3=vecto3;}


if(vecto1<0){dir1=0; vtt1=-vecto1;}
if(vecto2<0){dir2=0; vtt2=-vecto2;}
if(vecto3<0){dir3=0; vtt3=-vecto3;}

pwm_Pb(1, vtt1);
gpio_Pe(8, dir1);

pwm_Pa(6, vtt2);
gpio_Pc(4, dir2);

pwm_Pb(0, vtt3);
gpio_Pe(7, dir3);

	}	
	

void giugoc(int gocset, int speedquay)
	{
	 // la ban quay nguoc chieu kim dong ho tang, nguoc chieu giam	
	 // logic = 0 >> quay cung chieu dong ho tinh tu tam rb	
	 //	>> goc lech > 0 >> quay cung chieu, locgic=0; goc lech < 0 >>quay nguoc chieu, locgic-1

	 goclech = ((goclabanget)/10)-gocset;
	
//	 vqa=	ki*goclech;
//	 vqb=	ki*goclech;
//	 vqc=	ki*goclech;
//	 vqd=	ki*goclech;	
		
//	 if(vquay>vmax){vquay=vmax;}	// toc do gioi han la 255 ( co the thay doi o day )
   
	 if(goclech<(-30))
		 {      
			      vquay=speedquay;
		   		  gpio_Pc(5,1);
						gpio_Pc(4,1);
						gpio_Pe(8,1);
			      gpio_Pe(7,1);
						pwm_Pa(7,vquay);
						pwm_Pa(6,vquay);
						pwm_Pb(1,vquay);
			      pwm_Pb(0,vquay);
		 }
	 if((goclech>=(-30))&&(goclech<=0))
		 {      
			      vquay=-goclech*2;
		  		  gpio_Pc(5,1);
						gpio_Pc(4,1);
						gpio_Pe(8,1);
			      gpio_Pe(7,1);
						pwm_Pa(7,vquay);
						pwm_Pa(6,vquay);
						pwm_Pb(1,vquay);
			      pwm_Pb(0,vquay);
			 
		 }
	  if((goclech>0)&&(goclech<=30))
		 {    
      			vquay=goclech*2;
		  		  gpio_Pc(5,0);
						gpio_Pc(4,0);
						gpio_Pe(8,0);
            gpio_Pe(7,0);
						pwm_Pa(7,vquay);
						pwm_Pa(6,vquay);
						pwm_Pb(1,vquay);
			      pwm_Pb(0,vquay);
			 
		 } 	
		if(goclech>30)
		 {    
      			vquay=speedquay;
		  		  gpio_Pc(5,0);
						gpio_Pc(4,0);
						gpio_Pe(8,0);
            gpio_Pe(7,0);
						pwm_Pa(7,vquay);
						pwm_Pa(6,vquay);
						pwm_Pb(1,vquay);
			      pwm_Pb(0,vquay);
			 
		 } 	 
	}
	
void DungGiuViTri()
 {
	 
					  gpio_Pc(5,0);
						gpio_Pc(4,0);
						gpio_Pe(8,0);
	          gpio_Pe(7,0);
						pwm_Pa(7,2);
						pwm_Pa(6,2);
						pwm_Pb(1,2);
	          pwm_Pb(0,2);
 }	

void DongCoBan(int vantoc, int chieu)
{
  pwm_Pe(11,vantoc);
  gpio_Pe(12,chieu);
}	

void KhiNen(int sothutu, int trangthai)
	{
	  if(sothutu==1)
			{
			 gpio_Pe(10, trangthai);
			}
		if(sothutu==2&&trangthai==1)
      {
			 pwm_Pe(9,255);
			}	
		if(sothutu==2&&trangthai==0)
      {
			 pwm_Pe(9,0);
			}		
	}

void testban()
{

}
void TestRunAll()
	{
if(step==0){tinhtiencolaban(100, 105, 90, 0); gpio_Pe(10,0); if(demss1==2){step=1;}}// van toc tinh tien, goc tinh tien, van toc quay, goc quay}	
if(step==1){DungGiuViTri(); step=2;} // Dung o line lan 2 cho con (tz1)
if(step==2){Delay_ms_Systemtick(2000);gpio_Pe(10,1);step=3;} // delay cho con roi chay vao Tz1
if(step==3){
            tinhtiencolaban(70,180,90,0);if(demss1==3){step=4;} // bat line lan 4 thi dung  // diem ban tz1     
           }
if(step==4){
            DungGiuViTri(); // dung
           	Ban(110,10650,5);
	        if(stepban==12){step=5;stepban=2;}
           }
if(step==5){tinhtiencolaban(100,0,90,0);if(demss1==6){step=6;}}//Diem bat line 
if(step==6){DungGiuViTri();
            Delay_ms_Systemtick(2000);
	          step=7; 
           }
if(step==7)
	         {
					  tinhtiencolaban(60,90,90,0); // chay tinh tien len cho con Tz2
						if(demss1==8){step=8;}  
					 }
if(step==8){DungGiuViTri();
            Delay_ms_Systemtick(2000);
	          gpio_Pe(10,1); //lay con roi chay vao Tz2
	          step=9;
           }
if(step==9)
	         {
					  tinhtiencolaban(100,180,90,0);
						if(demss1==10){step=10;} 
					 }
if(step==10)
	         {
	          DungGiuViTri();
						Delay_ms_Systemtick(1000);
						Ban(110,10650,5);
						 if(stepban==12)
						 {step=11; stepban=0;}
	         } 
if(step==11)
           {
					 tinhtiencolaban(100,0,90,0);
					 if(demss1==12){step=12;}	 
					 }
if(step==12)
	         {
					 DungGiuViTri();
					Delay_ms_Systemtick(1000);
           step=13;						 
					 }
if(step==13)
	         {
					 tinhtiencolaban(100,180,90,0);
					 if(demss1==17){step=14;}	 
					 }
if(step==14){DungGiuViTri();}		 
		 
		 
		 
		 
	}
	
void RunTz1Ban()
{
 if(demss1==0){
              gpio_Pe(10,0);
              step=0;}
 if(step==0){tinhtiencolaban(70,90,90,0);
             if(demss1==2){DungGiuViTri();
						              Delay_ms_Systemtick(2000);
							                
							             step=1;  
						              }
            }
 if(step==1){ 
               
            }

}	

 void Ban(int tocdoban, int diemban, int hesogiatoca)
 {
   hesodiemgiatoc=(diemban +3750)/hesogiatoca; // do chia so xung 
   xungdemduoc= TestencoderTimer5 + 3750;
	 hesogiatoc= xungdemduoc/hesodiemgiatoc; // he so nhan voi toc do ban
	 tocdothucban=(tocdoban*hesogiatoc)/hesogiatoca+(tocdoban/hesogiatoca);
	 if(tocdothucban>tocdoban){tocdothucban=tocdoban;}
	 

//	if(stepban==2){pwm_Pe(11,10);
//               	gpio_Pe(12,1);
//		           
//	             if(TestencoderTimer4<=-3750){stepban=3;} // diem on dinh con 
//	              }
	if(stepban==0)
	             {
							 KhiNen(1,1);	 
							 pwm_Pe(11,2);
               gpio_Pe(12,1);
               //Delay_ms_Systemtick(1000);
							 stepban=1;
							 }
	 if(stepban==1)
	 {
	 						 pwm_Pe(11,(tocdothucban));
               gpio_Pe(12,0);	 
							 if(TestencoderTimer5>=diemban){gpio_Pe(10,0);stepban=2;}
	 }		 
	if(stepban==2)
	{
		 			
		        if(TestencoderTimer5>=diemban+1000)
						{stepban=3;}
						
	}
	if(stepban==3)
	{
	  	 				pwm_Pe(11,0); // dung dong co khong ham
              gpio_Pe(12,0);
		          Delay_ms_Systemtick(500);
		          stepban=4;
	}
	if(stepban==4)
	{ 
	    	  	 	 pwm_Pe(11,2);
               gpio_Pe(12,0);
		           lanbantz1++;
		           stepban=0;
	}

 }
void BanTz1Nghich(int tocdoban, int diemban, int hesogiatoca)
 {
	 
/* */
	 hesodiemgiatoc=(diemban +3750)/hesogiatoca; // do chia so xung 
   xungdemduoc= TestencoderTimer5 + 3750;
	 hesogiatoc= xungdemduoc/hesodiemgiatoc; // he so nhan voi toc do ban
	 tocdothucban=(tocdoban*hesogiatoc)/hesogiatoca+(tocdoban/hesogiatoca);
	 if(tocdothucban>tocdoban){tocdothucban=tocdoban;}
	 

//	if(stepban==2){pwm_Pe(11,10);
//               	gpio_Pe(12,1);
//		           
//	             if(TestencoderTimer4<=-3750){stepban=3;} // diem on dinh con 
//	              }
	if(stepban==0)
	             {
							 KhiNen(1,1);	 
							 pwm_Pe(11,2);
               gpio_Pe(12,1);
               //Delay_ms_Systemtick(1000);
							 stepban=1;
							 }
	 if(stepban==1)
	 {
	 						 pwm_Pe(11,(tocdothucban));
               gpio_Pe(12,1);	 
							 if(TestencoderTimer5<=diemban){gpio_Pe(10,0);stepban=2;}
	 }		 
	if(stepban==2)
	{
		 			
		        if(TestencoderTimer5<=diemban+1000)
						{stepban=3;}
						
	}
	if(stepban==3)
	{
	  	 				pwm_Pe(11,0); // dung dong co khong ham
              gpio_Pe(12,1);
		          Delay_ms_Systemtick(500);
		          stepban=4;
	}
	if(stepban==4)
	{ 
	    	  	 	 pwm_Pe(11,2);
               gpio_Pe(12,1);
		           lanbantz1++;
		           stepban=0;
	}
/**/
	
	
 }
void ChayAllV1()
{
	// encoder timer 5: encoder ban
	//encoder timer 4: encoder ra duong
	// x1=..., x2=....;
	x1=1000; // chay toc do cham
	x2= 14000; // max speed
	x3= 16000; // giam toc lan 1
	x4= 17000; // giam toc lan 2
	x5= 18500; // giam toc lan 3
	x6= 5000; // diem chay nhanh toi luc giam toc 
	x7= 6000; 
	x8= 5000;
	x9= 30000;
  
 if(stepquay==0) // quay ve vi tri cho con
	 {
		if(TestencoderTimer5>-1610) // quay ve vi tri cho con
		 {
	    DongCoBan(10,1);
		 }
    if(TestencoderTimer5<=-1610)
     {
		  DongCoBan(2,1);
			stepquay=1;
		 }			
	 }
	
 if(stepchay==0) // o vi tri xuat phat chay tinh tien quang duong x1
	 {
	   if(TestencoderTimer4<=x1) // x1 la diem tang toc
			 {
				 tinhtiencolaban(40,105,50,0); // tinh tien 105 do goc quay 0		//80	  
			 }
		 if(TestencoderTimer4 >x1){stepchay=1;} 
	 }
	if(stepchay==1) 
   {
	   	   if(TestencoderTimer4<=x2) //x2 la diem giam tocdothucban lan 1
			 {
				 tinhtiencolaban(180,105,50,0); // tinh tien 105 do goc quay 20//230
			 }
			 if(TestencoderTimer4 >x2){stepchay=2;} // chay du quang duong thi chyen qua step 2
	 }		
	if(stepchay==2) // sau khi chay quang duong x2 thi chay toi x3 (giamtoc lan 1);
   {
	   	   if(TestencoderTimer4<=x3) //neu quang duong <x3 thi .....
			 {tinhtiencolaban(100,110,50,0); // tinh tien 105 do goc quay 20 //120
			  
			 }
			 if(TestencoderTimer4 > x3){stepchay=3;} // chay du quang duong thi chyen qua step 3
	 }	
	if(stepchay==3) // sau khi chay quang duong x3 thi chay toi x4 (giamtoc lan 2);
   {
	   	   if(TestencoderTimer4<=x4) //neu quang duong <x4 thi .....
			 {tinhtiencolaban(60,115,50,0); // tinh tien 105 do goc quay 20//
			  
			 }
			 if(TestencoderTimer4 > x4){stepchay=4;} // chay du quang duong thi chyen qua step 4
	 }	//toi day ok
	if(stepchay==4) // sau khi chay quang duong x4 thi chay toi x5 (giamtoc lan 3);
   {
      if(stepchayve==0)
		    {
			  tinhtiencolaban(30,115,50,0); // tinh tien 105 do goc quay 20 
			  }
		  if(ss3==1)// neu ss1 nhan thi dung giu vi tri va cho con
					 {
					  DungGiuViTri(); // cho con ( if (ssban==1){stepchay=5;KhiNen(1,1);}
				    stepchayve=1; 
		        }
      			
			 if(stepchayve==1&&sensor2==0)
           {
						Delay_ms_Systemtick(500);
					  stepchay=5;
						KhiNen(1,1);
						 Delay_ms_Systemtick(500);
					 }				 
	 }
	 
	if(stepchay==5) // sau khi bat duoc line thi chay tinh tien 180 goc quay -10
   {
		 tinhtiencolaban(60, 180, 50, -7); //chay vào tz1 //70
		 if(TestencoderTimer5>=-3750){DongCoBan(20,1);} // quay qua con ve vi tri on dinh
		 if(TestencoderTimer5<-3750){DongCoBan(2,1);stepquay=2;}
		 if(ss8==1){DungGiuViTri();stepchayve=2;}
		 if(stepquay==2&&stepchayve==2){stepchay=6;ClearEncoder(4);} 
		 // sau khi toi dc vi tri ban van toi diem on dinh con thi chuyen qua step chay 6
	   // clear encoder
	 }	  	
  
	  	
  if(stepchay==6) // toi day ok
		{
		  BanTz1Nghich(100, -10700, 10);
			if(lanbantz1==1){stepchay=7;lanbantz1=0;}
			// sau khi ban Tz1 thi reset stepban , neu so lan ban la x thi qua step 7
		}
	if(stepchay==7) // chay ra cho con tz2 va quay canh tay ve diem lay con
    {     
	              if(stepquay==2)
								{	
								DongCoBan(30,0);
								}
								
		           if(TestencoderTimer5>=-1610)  // ve diem lay con thi step quay = 3
                {
								DongCoBan(2,1);
								stepquay=3;
								}
							 
      	   	   if(TestencoderTimer4<=x6) // tinh tien 10 do	toc do 120  
			          {
								tinhtiencolaban(60,0,50,0);
								} 
			 
               if(TestencoderTimer4 > x6)
                {
								tinhtiencolaban(30,0,50,0);
								} // diem giam toc là x6

		           if((ss8==1)&&(TestencoderTimer4>x6)) // bat duoc line thi stepchay =3
				       {
					      stepchayve=3;
								DungGiuViTri(); 
				       }
							 if(stepchayve==3 && stepquay==3)
							 {
							   ClearEncoder(4);
						     stepchay=8;
								 //sensor1=1;
								 
							 }	 
							 
		} // toi day Ok
		

		
	if((stepchay==8)&&(sensor2==0)) // && cam bien bat duoc con thi dong khi nen
      { 

			  Delay_ms_Systemtick(500);
				KhiNen(1,1);
				Delay_ms_Systemtick(500);
			  stepchay=9;

			} 

if(stepchay==9)
{
    if(TestencoderTimer4<x7)
			{
			 tinhtiencolaban(100,95,30,0);
			}
	  if(TestencoderTimer4>=x7)
      {
			 tinhtiencolaban(30,95,30,0);
			}
    if(TestencoderTimer4>=x7 && ss3==1)
      {
			 stepchay=10;
			}			
}  

if(stepchay==10) // sau khi bat duoc line thi chay tinh tien 180 goc quay 20
   {

		 tinhtiencolaban(60, 180, 100, -7); //chay vào tz2 //70
		 if(TestencoderTimer5>=-3750){DongCoBan(20,1);} // quay qua con ve vi tri on dinh
		 if(TestencoderTimer5<-3750){DongCoBan(2,1);stepquay=2;}
		 if(ss8==1){DungGiuViTri();stepchayve=2;}
		 if(stepquay==2&&stepchayve==2){stepchay=11;ClearEncoder(4);} 
		 // sau khi toi dc vi tri ban van toi diem on dinh con thi chuyen qua step chay 6
	   // clear encoder		 
		 
//		 tinhtiencolaban(50, 180, 50, -7);//50
//		 if(ss8==1)
//      {DungGiuViTri(); stepchay=11;}
	 }	  	
  
if(stepchay==11)
 	{
		
		
		
	    Ban(95, 12000, 7);
			if(lanbantz1==1)
        {
				lanbantz1=0;	
				stepchay=12;
				ClearEncoder(4);
				}
	}

if(stepchay==12)
	{
	  	           if(stepquay==2)
								{	
								DongCoBan(30,1);
								}
								
		           if(TestencoderTimer5<=-1610)  // ve diem lay con thi step quay = 3
                {
								DongCoBan(2,1);
								stepquay=3;
								}
							 
      	   	   if(TestencoderTimer4<=x8) // tinh tien 10 do	toc do 120  
			          {
								tinhtiencolaban(60,0,50,0);
								} 
			 
               if(TestencoderTimer4 > x8)
                {
								tinhtiencolaban(30,0,50,0);
								} // diem giam toc là x6

		           if((ss8==1)&&(TestencoderTimer4>x8)) // bat duoc line thi stepchay =3
				       {
					      stepchayve=3;
								DungGiuViTri();
               								 
								  
				       }
							 if(stepchayve==3 && stepquay==3)
								 {
								   
									 stepchay=13;
									 //USART_SendData(USART1, 'a');
								 }

	}
	
          if(stepchay==13)
	{
		if(stepchayve==3)
			{
	     giugoc(-90,50);
				//stepchayve=4;
			}
		 if(sensor4==0&&goclech<3)
      {
				KhiNen(2,1);
			 stepchay=14;
			}			 

	}
 
if(stepchay==14)
{
  if(TestencoderTimer4<=x9)
		{
	tinhtiencolaban(100,180,60,-90);
		}
   if(TestencoderTimer4>x9&&ss3==1)
    {
		 DungGiuViTri();
			stepchay=15;
		}		 
}	

if(stepchay==15)
	{
	  giugoc(0,60);
		if(goclech<5&&goclech>-5)
			{
		DungGiuViTri();	
    //Delay_ms_Systemtick(800);				
		stepchay=16;
			}
	}
	
if(stepchay==16)
  {
		if(sensor2==0)
	{		Delay_ms_Systemtick(500);
		KhiNen(1,1);
		Delay_ms_Systemtick(500);
stepchay=17;
	}	
				
  }	
	
if(stepchay==17)
	{

     if(TestencoderTimer5>=-3750){DongCoBan(10,1);} // quay qua con ve vi tri on dinh
		 if(TestencoderTimer5<-3750){DongCoBan(2,1);Delay_ms_Systemtick(500);stepchay=18;}

  }
	
if(stepchay==18)
  {
	  		Ban(150, 11900, 10);
		if(lanbantz1==1)
        {
				stepchay=19;
				}	

	}	
	
if(stepchay==19)
   {
	 					

								if(TestencoderTimer5>-1610)
									{
									DongCoBan(20,1);
									}

								
		           if(TestencoderTimer5<=-1610)  // ve diem lay con thi step quay = 3
                {
									lanbantz1=0;
								DongCoBan(2,1);
								stepchay=16;
								}
	
	 
	 }


	 
}	

void TestCamBien()
	{
	 if(sensor2==0)
		 {
		  KhiNen(1,1);
		 }
		if(sensor2==1)
		 {
		  KhiNen(1,0);
		 }
		 
		 	 if(sensor4==0)
		 {
		  KhiNen(2,1);
		 }
		if(sensor4==1)
		 {
		  KhiNen(2,0);
		 }
	}
 
//					}					
//int8_t 		1 byte signed		-128 to 127
//uint8_t		1 byte unsigned		0 to 255
//int16_t		2 bytes signed		-32768 to 32767
//uint16_t	2 bytes unsigned	0 to 65535
//int32_t		4 bytes signed		-2147483648 to 2147483647
//uint32_t	4 bytes unsigned	0 to 4294967295
//int64_t		8 bytes signed		-9223372036854775808 to 9223372036854775807
//uint64_t	8 bytes unsigned	0 to 18446744073709551615
