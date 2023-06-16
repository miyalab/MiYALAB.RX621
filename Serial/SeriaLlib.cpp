/*==================================*/
/* インクルード						*/
/*==================================*/
#include <stdio.h>					// 標準入出力ライブラリ
#include <machine.h>				// マシンライブラリ
#include "iodefine.h"				// レジスタ定義ファイル
#include "SerialLib.h"				// シリアル通信ライブラリ

/*==================================*/
/* シンボル定義						*/
/*==================================*/
#define RECV_BUFF_SIZE	128			// 受信バッファサイズ
#define SEND_BUFF_SIZE	128			// 送信バッファサイズ

/*==================================*/
/* プロトタイプ宣言					*/
/*==================================*/

/*==================================*/
/* グローバル変数宣言				*/
/*==================================*/
// SCI0受信関連
volatile static unsigned char RecvBuff[RECV_BUFF_SIZE];
volatile static unsigned char Position;

// SCI2受信関連
volatile static unsigned char RecvBuffSci2[RECV_BUFF_SIZE];
volatile static unsigned char PositionSci2;

// printf、scanf関連
volatile static unsigned char CallBack;

/********************************************************************/
/* 調歩同期式SCI0初期化関数											*/
/* 戻り値：なし														*/
/* 引　数：なし														*/
/********************************************************************/
void InitSCI0(unsigned char Baudrate)
{
	// RxD0端子, TxD0端子の入出力設定
	PORT2.DDR.BIT.B0 = 1;			// TxD0端子を出力端子に設定
	PORT2.DDR.BIT.B1 = 0;			// RxD0端子を入力端子に設定
	PORT2.ICR.BIT.B1 = 1;			// RxD0端子の入力バッファを有効

	// SCI0の設定
	MSTP(SCI0) = 0;					// 消費電力低減機能の解除
	IEN(SCI0, RXI0) = 1;			// シリアル受信割込み許可
	IPR(SCI0, RXI0) = 10;			// シリアル受信割込みレベル10
	SCI0.SMR.BIT.CM = 0;			// 調歩同期(非同期)モード
	SCI0.SMR.BIT.CKS = 0;			// PCLK
	SCI0.SMR.BIT.CHR = 0;			// キャラクタ長:8bit
	SCI0.SMR.BIT.STOP = 0;			// 1ストップビット
	SCI0.SMR.BIT.PE = 0;			// パリティビットなし
	SCI0.SMR.BIT.PM = 0;			// パリティモード設定

	// SCI0通信速度設定
	// BRR = PCLK[Hz] / (64*2^(2 * SMR.CKS - 1) * BaudRate) - 1
	// Baudrate = PCLK[Hz] / ((BBR + 1)*64*2^(2 * SMR.CKS - 1))
	if (Baudrate == SPEED_9600) SCI0.BRR = 155;
	if (Baudrate == SPEED_115200) SCI0.BRR = 12;
	if (Baudrate == SPEED_1500000) SCI0.BRR = 0;
	nop();

	SCI0.SCR.BYTE = 0xf0;			// シリアル送受信、送受信割り込み許可
}

/********************************************************************/
/* 調歩同期式SCI2初期化関数											*/
/* 戻り値：なし														*/
/* 引　数：なし														*/
/********************************************************************/
void InitSCI2(unsigned char Baudrate)
{
	// RxD2端子, TxD2端子の入出力設定
	IOPORT.PFFSCI.BIT.SCI2S = 1;	// P52:RxD2,P51:SCK2,P50:TxD2に設定
	PORT5.DDR.BIT.B2 = 1;			// TxD2端子を出力端子に設定
	PORT5.DDR.BIT.B0 = 0;			// RxD2端子を入力端子に設定
	PORT5.ICR.BIT.B0 = 1;			// RxD2端子の入力バッファを有効

	// SCI2の設定
	MSTP(SCI2) = 0;					// 消費電力低減機能の解除
	IEN(SCI2, RXI2) = 1;			// シリアル受信割込み許可
	IPR(SCI2, RXI2) = 9;			// シリアル受信割込みレベル9
	SCI2.SMR.BIT.CM = 0;			// 調歩同期(非同期)モード
	SCI2.SMR.BIT.CKS = 0;			// PCLK
	SCI2.SMR.BIT.CHR = 0;			// キャラクタ長:8bit
	SCI2.SMR.BIT.STOP = 0;			// 1ストップビット
	SCI2.SMR.BIT.PE = 0;			// パリティビットなし
	SCI2.SMR.BIT.PM = 0;			// パリティモード設定

	// SCI2通信速度設定
	// BRR = PCLK[Hz] / (64*2^(2 * SMR.CKS - 1) * BaudRate) - 1
	// Baudrate = PCLK[Hz] / ((BBR + 1)*64*2^(2 * SMR.CKS - 1))
	if (Baudrate == SPEED_9600) SCI2.BRR = 155;
	if (Baudrate == SPEED_115200) SCI2.BRR = 12;
	if (Baudrate == SPEED_1500000) SCI2.BRR = 0;
	nop();

	SCI2.SCR.BYTE = 0xf0;			// シリアル送受信、送受信割り込み許可
}

/********************************************************************/
/* scanf関数コールバック指定関数									*/
/* 戻り値：なし														*/
/* 引　数：CALL_BACK_ON or CALL_BACK_OFF							*/
/********************************************************************/
void CallBackScanf(unsigned char Mode)
{
	CallBack = Mode;
}

/********************************************************************/
/* 1文字出力（printfで呼び出される）								*/
/********************************************************************/
void charput(unsigned char c)
{
	while (SCI0.SSR.BIT.TEND == 0);	// 前回の送信処理が終了するまで待機
	SCI0.TDR = c;
	SCI0.SSR.BIT.TEND = 0;
}

/********************************************************************/
/* 1文字入力（scanfで呼び出される）									*/
/********************************************************************/
unsigned char charget(void)
{
	unsigned char i;
	unsigned char c;

	// 受信データを検出するまで待機
	do {
		c = RecvBuff[0];
	} while (c == '\0');

	// 読み込んだデータの削除
	for (i = 0; i<Position; i++) {
		RecvBuff[i] = RecvBuff[i + 1];
	}
	
	RecvBuff[i] = '\0';
	Position--;
	
	if(CallBack == CALL_BACK_ON) charput(c);

	return c;
}

/********************************************************************/
/* 1文字出力														*/
/********************************************************************/
void CharPutSci2(unsigned char c)
{
	while (SCI2.SSR.BIT.TEND == 0);	// 前回の送信処理が終了するまで待機
	SCI2.TDR = c;
	SCI2.SSR.BIT.TEND = 0;
}

/********************************************************************/
/* 1文字入力														*/
/********************************************************************/
unsigned char CharGetSci2(void)
{
	unsigned char i;
	unsigned char c;

	// 受信データを検出するまで待機
	do {
		c = RecvBuffSci2[0];
	} while (c == '\0');

	// 読み込んだデータの削除
	for (i = 0; i<PositionSci2; i++) {
		RecvBuffSci2[i] = RecvBuffSci2[i + 1];
	}
	
	RecvBuffSci2[i] = '\0';
	PositionSci2--;
	
	return c;
}

/********************************************************************/
/* SCI0 受信割り込み												*/
/********************************************************************/
#pragma interrupt Excep_SCI0_RXI0(vect = 215)
void Excep_SCI0_RXI0(void)
{
	unsigned char c;

	c = SCI0.RDR;				// 受信データを一時的に保存
	RecvBuff[Position] = c;		// 受信バッファに保存
	Position++;					// 受信データ保存アドレスを次のアドレスへ

	// 受信サイズを超えたら、バッファをリフレッシュ
	if (Position > RECV_BUFF_SIZE) {
		Position = 0;
	}
}

/********************************************************************/
/* SCI2 受信割り込み												*/
/********************************************************************/
#pragma interrupt Excep_SCI0_RXI2(vect = 223)
void Excep_SCI2_RXI2(void)
{
	unsigned char c;

	c = SCI2.RDR;					// 受信データを一時的に保存
	RecvBuffSci2[PositionSci2] = c;	// 受信バッファに保存
	PositionSci2++;					// 受信データ保存アドレスを次のアドレスへ

	// 受信サイズを超えたら、バッファをリフレッシュ
	if (Position > RECV_BUFF_SIZE) {
		Position = 0;
	}
}

/********************************************************************/
/* end of file														*/
/********************************************************************/
