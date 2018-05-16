#ifndef _HAMCON_H_
 #define _HAMCON_H_
 
 #include "stm32f4xx.h"
 
void TestRunAll(void);

void Ban(int tocdoban, int diemban, int hesoiatoca);
void testban(void); 

void ReadLine(void); 
void ReadSw(void);
void ReadSensor(void);

void DungGiuViTri(void);

void TienThang(void);
void giugoc(int gocset, int speedquay);
void tinhtienkhonglaban(int vtinhtien, int goctinhtien);
void tinhtienkhonglaban3banh(int vtinhtien, int goctinhtien);
void tinhtiencolaban(int vtinhtien, int goctinhtien, int vquay, int gocquay);
void tinhtiencolaban3banh(int vtinhtien, int goctinhtien, int vquay, int gocquay);
void testled(void);
void KhiNen(int sothutu, int trangthai);
void DongCoBan(int vantoc, int chieu);
void BanTz1Nghich(int tocdoban, int diemban, int hesogiatoca);
void ChayAllV1(void);
void ChayAllV2(void);
void TestCamBien(void);
//void run_angle(int angle,int a,int vtt);

#endif
