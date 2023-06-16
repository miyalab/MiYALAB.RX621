/*==================================*/
/* インクルード						*/
/*==================================*/

/*==================================*/
/* シンボル定義						*/
/*==================================*/
#define SPEED_9600		1
#define SPEED_115200	2
#define SPEED_1500000	3

#define CALL_BACK_ON	1
#define CALL_BACK_OFF	0

/*==================================*/
/* プロトタイプ宣言					*/
/*==================================*/

/*==================================*/
/* グローバル変数宣言				*/
/*==================================*/
void InitSCI0(unsigned char Baudrate);
void InitSCI2(unsigned char Baudrate);
void CallBackScanf(unsigned char Mode);
void charput(unsigned char c);
unsigned char charget(void);
void CharPutSci2(unsigned char c);
unsigned char CharGetSci2(void);

/********************************************************************/
/* end of file														*/
/********************************************************************/
