/*==================================*/
/* インクルード						*/
/*==================================*/
#include "iodefine.h"				// レジスタ定義ファイル
#include "PwmLib.h"					// PWMライブラリ

/*==================================*/
/* シンボル定義						*/
/*==================================*/

/*==================================*/
/* プロトタイプ宣言					*/
/*==================================*/

/*==================================*/
/* グローバル変数宣言				*/
/*==================================*/

/********************************************************************/
/* Pwm0,Pwm1端子の初期化設定										*/
/* 戻り値：なし														*/
/* 引　数：クロック設定値, PWM周波数								*/
/********************************************************************/
void InitPwm01(unsigned char Clock, unsigned int Cycle)
{
	// PWM出力端子を出力に設定
	PORT3.DDR.BIT.B2 = 1;
	PORT3.DDR.BIT.B4 = 1;

	// MTU0をPWMモード1に設定
	// PWM周期 = (Cycle - 1 + 1) / PCLK
	MSTP(MTU0) = 0;							// MTU0設定
	MTU0.TCR.BIT.TPSC = Clock;				// MTU0:クロック設定
	MTU0.TCR.BIT.CKEG = 1;					// MTU0:立ち上がりエッジでカウント
	MTU0.TCR.BIT.CCLR = 1;					// MTU0:TGRAのコンペアマッチでTCNTクリア
	MTU0.TMDR.BIT.MD = 2;					// MTU0:PWMモード1
	MTU0.TMDR.BIT.BFA = 0;					// TGRA,TGRC通常動作
	MTU0.TMDR.BIT.BFB = 0;					// TGRB,TGRD通常動作
	MTU0.TIORH.BIT.IOA = 6;					// MTU0.TGRA:初期出力High、ｺﾝﾍﾟｱﾏｯﾁでHigh
	MTU0.TIORH.BIT.IOB = 5;					// MTU0.TGRB:初期出力High、ｺﾝﾍﾟｱﾏｯﾁでLow
	MTU0.TIORL.BIT.IOC = 6;					// MTU0.TGRA:初期出力High、ｺﾝﾍﾟｱﾏｯﾁでHigh
	MTU0.TIORL.BIT.IOD = 5;					// MTU0.TGRB:初期出力High、ｺﾝﾍﾟｱﾏｯﾁでLow
	MTU0.TGRA = MTU0.TGRC = Cycle - 1;		// 周期
	MTU0.TGRB = 0;							// P34のデューティ比
	MTU0.TGRD = 0;							// P32のデューティ比
	MTU0.TCNT = 0;							// MTU0:TCNT初期化
	MTUA.TSTR.BIT.CST0 = 1;					// MTU0:カウント動作開始
}

/********************************************************************/
/* Pwm2,Pwm3端子の初期化設定										*/
/* 戻り値：なし														*/
/* 引　数：クロック設定値, PWM周波数								*/
/********************************************************************/
void InitPwm23(unsigned char Clock, unsigned int Cycle)
{
	// PWM出力端子を出力に設定
	PORT2.DDR.BIT.B4 = 1;
	PORT2.DDR.BIT.B5 = 1;

	// MTU4をPWMモード1に設定
	// PWM周期 = (Cycle - 1 + 1) / PCLK
	MSTP(MTU4) = 0;							// MTU4設定
	MTUA.TOER.BIT.OE4A = 1;					// MTIOC4A出力許可
	MTUA.TOER.BIT.OE4C = 1;					// MTIOC4C出力許可
	MTU4.TCR.BIT.TPSC = Clock;				// MTU4:クロック設定
	MTU4.TCR.BIT.CKEG = 1;					// MTU4:立ち上がりエッジでカウント
	MTU4.TCR.BIT.CCLR = 1;					// MTU4:TGRAのコンペアマッチでTCNTクリア
	MTU4.TMDR.BIT.MD = 2;					// MTU4:PWMモード1
	MTU4.TMDR.BIT.BFA = 0;					// TGRA,TGRC通常動作
	MTU4.TMDR.BIT.BFB = 0;					// TGRB,TGRD通常動作
	MTU4.TIORH.BIT.IOA = 6;					// MTU4.TGRA:初期出力High、ｺﾝﾍﾟｱﾏｯﾁでHigh
	MTU4.TIORH.BIT.IOB = 5;					// MTU4.TGRB:初期出力High、ｺﾝﾍﾟｱﾏｯﾁでLow
	MTU4.TIORL.BIT.IOC = 6;					// MTU4.TGRA:初期出力High、ｺﾝﾍﾟｱﾏｯﾁでHigh
	MTU4.TIORL.BIT.IOD = 5;					// MTU4.TGRB:初期出力High、ｺﾝﾍﾟｱﾏｯﾁでLow
	MTU4.TGRA = MTU4.TGRC = Cycle - 1;		// MTU4.周期
	MTU4.TGRB = 0;							// P24のデューティ比
	MTU4.TGRD = 0;							// P25のデューティ比
	MTU4.TCNT = 0;							// MTU4:TCNT初期化
	MTUA.TSTR.BIT.CST4 = 1;					// MTU4:カウント動作開始
}

/********************************************************************/
/* Pwm4,Pwm5端子の初期化設定										*/
/* 戻り値：なし														*/
/* 引　数：クロック設定値, PWM周波数								*/
/********************************************************************/
void InitPwm45(unsigned char Clock, unsigned int Cycle)
{
	// PWM出力端子を出力に設定
	PORTA.DDR.BIT.B0 = 1;
	PORTA.DDR.BIT.B2 = 1;

	// MTU6をPWMモード1に設定
	// PWM周期 = (Cycle - 1 + 1) / PCLK
	MSTP(MTU6) = 0;							// MTU6設定
	MTU6.TCR.BIT.TPSC = Clock;				// MTU6:クロック設定
	MTU6.TCR.BIT.CKEG = 1;					// MTU6:立ち上がりエッジでカウント
	MTU6.TCR.BIT.CCLR = 1;					// MTU6:TGRAのコンペアマッチでTCNTクリア
	MTU6.TMDR.BIT.MD = 2;					// MTU6:PWMモード1
	MTU6.TMDR.BIT.BFA = 0;					// TGRA,TGRC通常動作
	MTU6.TMDR.BIT.BFB = 0;					// TGRB,TGRD通常動作
	MTU6.TIORH.BIT.IOA = 6;					// MTU6.TGRA:初期出力High、ｺﾝﾍﾟｱﾏｯﾁでHigh
	MTU6.TIORH.BIT.IOB = 5;					// MTU6.TGRB:初期出力High、ｺﾝﾍﾟｱﾏｯﾁでLow
	MTU6.TIORL.BIT.IOC = 6;					// MTU6.TGRA:初期出力High、ｺﾝﾍﾟｱﾏｯﾁでHigh
	MTU6.TIORL.BIT.IOD = 5;					// MTU6.TGRB:初期出力High、ｺﾝﾍﾟｱﾏｯﾁでLow
	MTU6.TGRA = MTU6.TGRC = Cycle - 1;		// 周期
	MTU6.TGRB = 0;							// PA0のデューティ比
	MTU6.TGRD = 0;							// PA2のデューティ比
	MTU6.TCNT = 0;							// MTU6:TCNT初期化
	MTUB.TSTR.BIT.CST0 = 1;					// MTU6:カウント動作開始
}

/********************************************************************/
/* Pwm6,Pwm7端子の初期化設定										*/
/* 戻り値：なし														*/
/* 引　数：クロック設定値, PWM周波数								*/
/********************************************************************/
void InitPwm67(unsigned char Clock, unsigned int Cycle)
{
	// PWM出力端子を出力に設定
	PORTB.DDR.BIT.B0 = 1;
	PORTB.DDR.BIT.B1 = 1;

	// MTU9をPWMモード1に設定
	// PWM周期 = (Cycle - 1 + 1) / PCLK
	MSTP(MTU9) = 0;							// MTU9設定
	MTU9.TCR.BIT.TPSC = Clock;				// MTU9:クロック設定
	MTU9.TCR.BIT.CKEG = 1;					// MTU9:立ち上がりエッジでカウント
	MTU9.TCR.BIT.CCLR = 1;					// MTU9:TGRAのコンペアマッチでTCNTクリア
	MTU9.TMDR.BIT.MD = 2;					// MTU9:PWMモード1
	MTU9.TMDR.BIT.BFA = 0;					// TGRA,TGRC通常動作
	MTU9.TMDR.BIT.BFB = 0;					// TGRB,TGRD通常動作
	MTU9.TIORH.BIT.IOA = 6;					// MTU9.TGRA:初期出力High、ｺﾝﾍﾟｱﾏｯﾁでHigh
	MTU9.TIORH.BIT.IOB = 5;					// MTU9.TGRB:初期出力High、ｺﾝﾍﾟｱﾏｯﾁでLow
	MTU9.TIORL.BIT.IOC = 6;					// MTU9.TGRA:初期出力High、ｺﾝﾍﾟｱﾏｯﾁでHigh
	MTU9.TIORL.BIT.IOD = 5;					// MTU9.TGRB:初期出力High、ｺﾝﾍﾟｱﾏｯﾁでLow
	MTU9.TGRA = MTU9.TGRC = Cycle - 1;		// 周期
	MTU9.TGRB = 0;							// PB0のデューティ比
	MTU9.TGRD = 0;							// PB1のデューティ比
	MTU9.TCNT = 0;							// MTU9:TCNT初期化
	MTUB.TSTR.BIT.CST3 = 1;					// MTU9:カウント動作開始
}

/********************************************************************/
/* Pwm8,Pwm9端子の初期化設定										*/
/* 戻り値：なし														*/
/* 引　数：クロック設定値, PWM周波数								*/
/********************************************************************/
void InitPwm89(unsigned char Clock, unsigned int Cycle)
{
	// PWM出力端子を出力に設定
	PORTB.DDR.BIT.B4 = 1;
	PORTB.DDR.BIT.B5 = 1;

	// MTU10をPWMモード1に設定
	// PWM周期 = (Cycle - 1 + 1) / PCLK
	MSTP(MTU10) = 0;						// MTU10設定
	MTUB.TOER.BIT.OE4A = 1;					// MTIOC10A出力許可
	MTUB.TOER.BIT.OE4C = 1;					// MTIOC10C出力許可
	MTU10.TCR.BIT.TPSC = Clock;				// MTU10:クロック設定
	MTU10.TCR.BIT.CKEG = 1;					// MTU10:立ち上がりエッジでカウント
	MTU10.TCR.BIT.CCLR = 1;					// MTU10:TGRAのコンペアマッチでTCNTクリア
	MTU10.TMDR.BIT.MD = 2;					// MTU10:PWMモード1
	MTU10.TMDR.BIT.BFA = 0;					// TGRA,TGRC通常動作
	MTU10.TMDR.BIT.BFB = 0;					// TGRB,TGRD通常動作
	MTU10.TIORH.BIT.IOA = 6;				// MTU10.TGRA:初期出力High、ｺﾝﾍﾟｱﾏｯﾁでHigh
	MTU10.TIORH.BIT.IOB = 5;				// MTU10.TGRB:初期出力High、ｺﾝﾍﾟｱﾏｯﾁでLow
	MTU10.TIORL.BIT.IOC = 6;				// MTU10.TGRA:初期出力High、ｺﾝﾍﾟｱﾏｯﾁでHigh
	MTU10.TIORL.BIT.IOD = 5;				// MTU10.TGRB:初期出力High、ｺﾝﾍﾟｱﾏｯﾁでLow
	MTU10.TGRA = MTU10.TGRC = Cycle - 1;	// 周期
	MTU10.TGRB = 0;							// PB4のデューティ比
	MTU10.TGRD = 0;							// PB5のデューティ比
	MTU10.TCNT = 0;							// MTU10:TCNT初期化
	MTUB.TSTR.BIT.CST4 = 1;					// MTU10:カウント動作開始
}

/********************************************************************/
/* Pwm0端子出力設定													*/
/* 戻り値：なし														*/
/* 引　数：ON時間（設定周期以下にすること）							*/
/********************************************************************/
void Pwm0(unsigned int Duty)
{
	MTU0.TGRB = Duty;
}

/********************************************************************/
/* Pwm1端子出力設定													*/
/* 戻り値：なし														*/
/* 引　数：ON時間（設定周期以下にすること）							*/
/********************************************************************/
void Pwm1(unsigned int Duty)
{
	MTU0.TGRD = Duty;
}

/********************************************************************/
/* Pwm2端子出力設定													*/
/* 戻り値：なし														*/
/* 引　数：ON時間（設定周期以下にすること）							*/
/********************************************************************/
void Pwm2(unsigned int Duty)
{
	MTU4.TGRB = Duty;
}

/********************************************************************/
/* Pwm3端子出力設定													*/
/* 戻り値：なし														*/
/* 引　数：ON時間（設定周期以下にすること）							*/
/********************************************************************/
void Pwm3(unsigned int Duty)
{
	MTU4.TGRD = Duty;
}

/********************************************************************/
/* Pwm4端子出力設定													*/
/* 戻り値：なし														*/
/* 引　数：ON時間（設定周期以下にすること）							*/
/********************************************************************/
void Pwm4(unsigned int Duty)
{
	MTU6.TGRB = Duty;
}

/********************************************************************/
/* Pwm5端子出力設定													*/
/* 戻り値：なし														*/
/* 引　数：ON時間（設定周期以下にすること）							*/
/********************************************************************/
void Pwm5(unsigned int Duty)
{
	MTU6.TGRD = Duty;
}

/********************************************************************/
/* Pwm6端子出力設定													*/
/* 戻り値：なし														*/
/* 引　数：ON時間（設定周期以下にすること）							*/
/********************************************************************/
void Pwm6(unsigned int Duty)
{
	MTU9.TGRB = Duty;
}

/********************************************************************/
/* Pwm7端子出力設定													*/
/* 戻り値：なし														*/
/* 引　数：ON時間（設定周期以下にすること）							*/
/********************************************************************/
void Pwm7(unsigned int Duty)
{
	MTU9.TGRD = Duty;
}

/********************************************************************/
/* Pwm8端子出力設定													*/
/* 戻り値：なし														*/
/* 引　数：ON時間（設定周期以下にすること）							*/
/********************************************************************/
void Pwm8(unsigned int Duty)
{
	MTU10.TGRB = Duty;
}

/********************************************************************/
/* Pwm9端子出力設定													*/
/* 戻り値：なし														*/
/* 引　数：ON時間（設定周期以下にすること）							*/
/********************************************************************/
void Pwm9(unsigned int Duty)
{
	MTU10.TGRD = Duty;
}

/********************************************************************/
/* end of file														*/
/********************************************************************/
