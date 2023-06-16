/*==================================*/
/* インクルード						*/
/*==================================*/

/*==================================*/
/* シンボル定義						*/
/*==================================*/
// エンコーダZ相
#define ENCODER1_Z	PORTB.DR.BIT.B2
#define ENCODER2_Z	PORTB.DR.BIT.B3
#define ENCODER3_Z	PORTB.DR.BIT.B6
#define ENCODER4_Z	PORTB.DR.BIT.B7

/*==================================*/
/* プロトタイプ宣言					*/
/*==================================*/
void InitEncoder1(void);
void InitEncoder2(void);
void InitEncoder3(void);
void InitEncoder4(void);
short Encode1(void);
short Encode2(void);
short Encode3(void);
short Encode4(void);

/*==================================*/
/* 構造体定義						*/
/*==================================*/
typedef struct encoder{
	long Total;
	short Encode;
}encoder;

/*==================================*/
/* グローバル変数宣言				*/
/*==================================*/

/********************************************************************/
/* end of file														*/
/********************************************************************/
