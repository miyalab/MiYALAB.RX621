/*==================================*/
/* インクルード						*/
/*==================================*/

/*==================================*/
/* シンボル定義						*/
/*==================================*/
#define PCLK64		3				// PCLK / 64
#define PCLK16		2				// PCLK / 16
#define PCLK4		1				// PCLK / 4
#define PCLK		0				// PCLK

/*==================================*/
/* プロトタイプ宣言					*/
/*==================================*/
void InitPwm01(unsigned char Clock, unsigned int Cycle);
void InitPwm23(unsigned char Clock, unsigned int Cycle);
void InitPwm45(unsigned char Clock, unsigned int Cycle);
void InitPwm67(unsigned char Clock, unsigned int Cycle);
void InitPwm89(unsigned char Clock, unsigned int Cycle);
void Pwm0(unsigned int Duty);
void Pwm1(unsigned int Duty);
void Pwm2(unsigned int Duty);
void Pwm3(unsigned int Duty);
void Pwm4(unsigned int Duty);
void Pwm5(unsigned int Duty);
void Pwm6(unsigned int Duty);
void Pwm7(unsigned int Duty);
void Pwm8(unsigned int Duty);
void Pwm9(unsigned int Duty);

/*==================================*/
/* グローバル変数宣言				*/
/*==================================*/

/********************************************************************/
/* end of file														*/
/********************************************************************/
