/*
*	file name: HS081.c
*	model	:	HS081C
*	date	:	2015/11/7
*	description：
*	history	:	
*	
*/
/*					   		   PMC234-s24
*				   			-----------------
*	(C2)				PC2| *				 |PC3						(C3)
*	(C1)				PC1|				 |PC4						(SEG1)
*	(C0)		  PC0/CIN3-| 				 |PC5/CIN+					(SEG2)
*	(Tad)	PB0/AD0/INT1/CO|				 |PA4/AD9/CIN2-				(SEG3)
*	(bt134)	   PB1/AD1/Vref|				 |PA7/X1					(SEG4)
*	(Khigh)			PB2/AD2|				 |PA6/X2					(SEG5)
*						GND|				 |VDD
*	(Klow)			PB3/AD3|				 |PA3/AD8/PWM/COM3/CIN1-	(SEG6)
*	(Konoff)		PB4/AD4|				 |PA2/PWM/COM2				(SEG7)
*	(LEDR)			PB5/AD5|				 |PA1/PWM/COM1				(SEG8)
*	(LEDG)			PB6/AD6|				 |PA5/RESET#
*	(LEDB)			PB7/AD7|				 |PA0/INT0/COM0      		(INT0)
*				   			-----------------
*	voltage:
*			N|--680K--|D4007>|---6.8K--|0V
*	TAD:
*						|+--ad2
*			5V|--100K-VR10K-4.7K--|0V
*	+---------------------------------------------------------------------------------------------------+
*	|											lcd data												|
*	+----+------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
*	|pin |1		|2		|3		|4		|5		|6		|7		|8		|9		|10		|11		|12		|
*	+----+------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
*	|no. |com0	|com1	|com2	|com3	|seg0	|seg1	|seg2	|seg3	|seg4	|seg5	|seg6	|seg7	|
*	+----+------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
*	|com0|com0	|		|		|		|1F		|1A		|2F		|2A		|3F		|3A		|MOON-T1|P1		|
*	+----+------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
*	|com1|		|com1	|		|		|1G		|1B		|2G		|2B		|3G		|3B		|T2		|P2		|
*	+----+------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
*	|com2|		|		|com2	|		|1E		|1C		|2E		|2C		|3E		|3C		|T3		|P3		|
*	+----+------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
*	|com3|		|		|		|com3	|1D		|HEAT	|2D		|'F		|3D		|'C		|T4		|P4		|
*	+----+------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
***********************************************************
*	说明：
*	1. 通电时显示OFF,背光源呈Flash闪动状态， 显蓝色光；
*	2. 长按ON/OFF2S， 开关机， 开机默认370℉ ， 温度范围170-450℉， 每档按10℉单位加减， 开机默认温度单位为： ℉；
*	3. 开机默认定时为120分钟， 可以手动可调定时时间， 调节为0-120分钟0分钟时为没有定时， 定时分7档为： 0,10,20,30,40,50,60,120；
*	4. 进行定时设定时长按"-"键， 亮红色光， 再按-或+键， 选择所要求的设定；
*	5. 定时到后无论按哪个键， 都须跳回设定值工作， 定时到后显示OFF， 背光源呈Flash闪动状态， 亮红色光；
*	6. 正常工作时， 加温时背光源显示蓝光， 达到设定温度后背光源显示绿灯,但最大显示不超过450℉ ， 最低显示为实时显示；
*	7. 当设定温度后， 显示的温度是夹板实时的温度， 当达到设定温度后， 显示的温度不变（不管温度如何变化） ；
*	8.ON/OFF键： 开关机， 每长按2S， 开机（背光源亮蓝色光， 显示370℉， 120分钟自动关机功能） 或关机（亮蓝光OFF闪烁） ；
*	9."+"键： 短按一次温度加10℉， 直到450℉， 长按2S温度单位℉和℃相互转换；
*	10."-"键： 短按一次温度减10℉， 直到170℉ ,长按背光源亮红色后可以设定自动关机的时间0,10,20,30,40,50,60,120分钟。
*	11.关于定时方面做一个宏定义选择。 默认120分钟与可调时间选择。
* 11.10
1.    通电时显示OFF,背光源呈Flash闪动状态，显蓝色背光；
2.    长按ON/OFF 2S，开关机，开机默认370℉，温度范围170-450℉，每档按20℉单位加减，
	开机默认温度单位为：℉；（也可能是开机默认400℉，10℉一档，）
3.    开机默认定时为120分钟，可以手动可调定时时间，调节为10-120分钟，定时分12档为：
		120,110,100,90,80,70,60,50,40,30,20,10；
4.    进行定时设定时长按"-"键，亮红色光，再按-或+键，选择所要求的定时时间；
5.    定时到后无论按哪个键，都须跳回设定值工作，定时到后显示OFF，背光源呈Flash闪动状态，亮红色背光；
6.    正常工作时，加温时背光源稳定显示蓝光，但加热进度条动态显示，达到设定温度后背光源显示绿灯,
	加热进度条稳定显示，但最大显示不超过450℉，注意工作时不显示实时温度值，只显示设定温度；
7.    当设定温度后，显示的温度是设定的温度，当达到设定温度后，显示的温度不变（不管温度如何变化），
	只是背光由蓝光变为绿光；
8.    ON/OFF键：开关机，每长按2S，开机（背光源亮蓝色光，显示370℉，120分钟自动关机功能）或关机
	（亮蓝光OFF闪烁）；
9.    "+"键：短按一次温度加10℉，直到450℉，长按2S温度单位℉和℃相互转换；
10. "-"键：短按一次温度减10℉，直到170℉,长按背光源亮红色后可以设定自动关机的时间
	0,10,20,30,40,50,60,120分钟。
11.     做一个正常功能版本跟测试版本选择的宏定义，正常功能为以上1~10所描述的功能，
	测试版本主要是长时间煲机测试使用，要求开机自动设定到最高温度档，同时不自动关机。
*/
#include "extern.h"

//打开宏 DEBUG 关机显示电压，开机显示温度ad
//#define 	DEBUG

#define uint8_t byte
#define uint16_t word
#define uint32_t dword
.RAMADR 0
uint16_t Point;
.RAMADR SYSTEM

#define ON 1
#define	OFF 0
#define CM 1
#define FM 0

#define LED_RED(a) PB.5 = !a
#define LED_GREEN(a) PB.6 = !a
#define LED_BLUE(a) PB.7 = !a
#define BT134(m) PB.1 = m

//#define	RESET_HEAT_TEMP	10	/* 重新显示加热值<不需要此功能时屏蔽掉此行*/
#define EINT_CNT_220V	1		//220v时N个中断加热一次
#define EINT_CNT_120V	1		//120V时N个中断加热一次
#define TEMP_SLOWUP		1		//接近目标N度时减慢加热速度
#define TEMP_SLOW_GAIN	2		//减慢加热速度的倍数
//定时时间可设定 on:<1> off:<0>
#define EN_TIMESET		1
#define EN_FTC          1



//默认开机温度*根据默认温度模式设置相应值
#define DEFAULT_TEMP	410
//定温设定步进
#define SETTEMP_STEPV 20



/*
//默认开机温度*根据默认温度模式设置相应值
#define DEFAULT_TEMP	200
//定温设定步进
#define SETTEMP_STEPV 10
*/


/*
//默认开机温度*根据默认温度模式设置相应值
#define DEFAULT_TEMP	400
//定温设定步进
#define SETTEMP_STEPV 10
*/

//默认温度模式C/F CM  FM
#define DEFAULT_MODE	FM
//默认定时时间
#define DEFAULT_TIME	60
//定时设定步进
#define SETTIME_STEPV	10
//最大定时时间*(时间不可调时没用
#define MAX_TIME	60 //分钟单位
#define MIN_TIME	0 //分钟单位 **设0时，可调到0分钟，无定时*
//最大定温温度(单位根据默认温度模式


#define MAX_TEMP	450
//最小定温温度
#define MIN_TEMP	170


/*
#define MAX_TEMP	230
//最小定温温度
#define MIN_TEMP	100
*/

//显示实时温度 on:<1> off:<0>
#define DISP_REAL_TEMP 1

//#define VAD_CH	6
#define TAD_CH	0
//#define KAD_CH	7

#define DSEG_A	(1<<1)
#define	DSEG_B	(1<<3)
#define DSEG_C	(1<<5)
#define DSEG_D	(1<<6)
#define DSEG_E	(1<<4)
#define DSEG_F	(1<<0)
#define DSEG_G	(1<<2)

#define DCode_0 (DSEG_A|DSEG_B|DSEG_C|DSEG_D|DSEG_E|DSEG_F)
#define DCode_1	(DSEG_B|DSEG_C)
#define DCode_2	(DSEG_A|DSEG_B|DSEG_G|DSEG_E|DSEG_D)
#define DCode_3	(DSEG_A|DSEG_B|DSEG_G|DSEG_C|DSEG_D)
#define	DCode_4	(DSEG_B|DSEG_C|DSEG_F|DSEG_G)
#define DCode_5 (DSEG_A|DSEG_F|DSEG_G|DSEG_C|DSEG_D)
#define DCode_6 (DSEG_A|DSEG_F|DSEG_C|DSEG_D|DSEG_E|DSEG_F|DSEG_G)
#define DCode_7 (DSEG_A|DSEG_B|DSEG_C)
#define DCode_8	(DSEG_A|DSEG_B|DSEG_C|DSEG_D|DSEG_E|DSEG_F|DSEG_G)
#define DCode_9	(DSEG_A|DSEG_B|DSEG_C|DSEG_D|DSEG_G|DSEG_F)
#define DCode_A	(DSEG_A|DSEG_B|DSEG_C|DSEG_E|DSEG_F|DSEG_G)
#define DCode_B	(DSEG_C|DSEG_D|DSEG_E|DSEG_F|DSEG_G)
#define DCode_C	(DSEG_A|DSEG_D|DSEG_E|DSEG_F)
#define DCode_D	(DSEG_B|DSEG_C|DSEG_D|DSEG_E|DSEG_G)
#define DCode_E	(DSEG_A|DSEG_D|DSEG_E|DSEG_F|DSEG_G)
#define DCode_F	(DSEG_A|DSEG_E|DSEG_F|DSEG_G)
#define	DCode_R	(DSEG_E|DSEG_G)
// 		b	7	6	5	4	3	2 	1	0
// DRAM-seg	s4	s5	s2	s1	s6	s7	s8	s3
#define LCD_HEAT(a) Dram[3]=(Dram[3]&(~0x20))|(a<<5)
#define LCD_F(a) Dram[3]=(Dram[3]&(~0x80))|(a<<7)
#define LCD_C(a) Dram[3]=(Dram[3]&(~0x08))|(a<<3)
#define LCD_T4(a) Dram[3]=(Dram[3]&(~0x04))|(a<<2)
#define LCD_P4(a) Dram[3]=(Dram[3]&(~0x02))|(a<<1)
#define LCD_T3(a) Dram[2]=(Dram[2]&(~0x04))|(a<<2)
#define LCD_P3(a) Dram[2]=(Dram[2]&(~0x02))|(a<<1)
#define LCD_T2(a) Dram[1]=(Dram[1]&(~0x04))|(a<<2)
#define LCD_P2(a) Dram[1]=(Dram[1]&(~0x02))|(a<<1)
#define LCD_T1(a) Dram[0]=(Dram[0]&(~0x04))|(a<<2)
#define LCD_P1(a) Dram[0]=(Dram[0]&(~0x02))|(a<<1)
	
//BIT COM3 :PB.0
//BIT COM2 :PB.1
//BIT COM1 :PB.2
//BIT COM0 :PB.5

BIT COM3 :PC.3
BIT COM2 :PC.2
BIT COM1 :PC.1
BIT COM0 :PC.0



uint8_t W_Stat;
uint8_t W_Dly;
uint8_t W_RealTempC;	//摄氏度
uint8_t W_TempC;	//设定值 摄氏度
uint16_t W_TempF;	//设定值 华氏度
uint8_t W_Time;
uint8_t W_SetTime;


uint8_t KeyMsgCode;
uint8_t KeyMsgPressed;

//#define K_UP	0x01
//#define K_DOWN	0x02
//#define K_ONOFF	0x04



#define K_UP	0x04
#define K_DOWN	0x08
#define K_ONOFF	0x10

#define ON_MODE	0X01
#define S_TIME	0x02
#define	HEAT_HOLD	0X08
#define C_MODE	0X10
#define ERR		0X20
#define HEAT	0X40
#define EN_TAD	0x80

uint8_t ExtInitCnt,TriacOnPeriod,TM0Cnt;
uint8_t EnAD,IntegsBak;
uint16_t Tad,Vad;
uint8_t TmMs[6],Dram[4];

BYTE bPara1,bPara2;//,bPara3,bPara4;
WORD wPara1,wPara2;
EWORD ePara1;

const uint16_t DCode_tbl[]={
	DCode_0,
	DCode_1,
	DCode_2,
	DCode_3,
	DCode_4,
	DCode_5,
	DCode_6,
	DCode_7,
	DCode_8,
	DCode_9,
	DCode_A,
	DCode_B,
	DCode_C,
	DCode_D,
	DCode_E,
	DCode_F,
	DCode_R
};
// 电压温度对照表1 (0~126度)
const uint16_t  vt_table1[]=				
{//热敏电阻100k B = 3990
	/*
//0	1	 2	  3	   4    5    6    7    8    9     
62  ,65  ,69  ,72  ,76  ,80  ,84  ,88  ,92  ,97  ,
102 ,106 ,111 ,117 ,122 ,128 ,134 ,140 ,146 ,153 ,
160 ,167 ,174 ,181 ,189 ,197 ,206 ,214 ,223 ,233 ,
242 ,252 ,262 ,273 ,283 ,295 ,306 ,318 ,330 ,343 ,
356 ,369 ,383 ,397 ,412 ,427 ,442 ,458 ,474 ,491 ,
508 ,524 ,542 ,559 ,577 ,596 ,615 ,634 ,654 ,675 ,
696 ,717 ,739 ,761 ,784 ,807 ,831 ,855 ,880 ,905 ,
930 ,956 ,982 ,1009,1036,1063,1091,1119,1147,1175,
1204,1233,1262,1291,1321,1350,1380,1409,1439,1468,
1498,1528,1558,1588,1618,1647,1677,1707,1737,1766,
1796,1822,1848,1874,1900,1927,1953,1980,2007,2034,
2060,2087,2114,2140,2167,2193,2219,2245,2271,2297,
2322,2347,2372,2397,2421,2446,2468,2490,2512,2534,
2555,2577,2597,2618,2639,2659,2679,2699,2718,2738,
2757,2776,2795,2813,2832,2850,2868,2886,2904,2921,
2938,2954,2969,2983,2997,3011,3025,3038,3052,3064,
3077,3089,3102,3113,3125,3136,3148,3158,3169,3180,
3190,3200,3210,3220,3229,3239,3248,3257,3266,3275,
3283,3292,3300,3309,3317,3325,3333,3340,3348,3355,
3363,3370,3377,3385,3392,3399,3405,3412,3419,3425,
3432,3437,3441,3446,3451,3455,3460,3464,3469,3473,
3478,3482,3487,3491,3496,3500,3504,3508,3512,3516,
3520,3524,3528,3532,3535,3539,3543,3546,3550,3553,
3556,3559,3563,3566,3569,3572,3574,3577,3580,3583,
3585,3588,3590,3593,3595,3598,3600,3602,3604,3606


63,66,70,74,77,81,86,90,94,99,
104,109,114,119,125,131,137,143,150,156,
163,170,178,186,194,202,211,219,229,238,
248,258,269,279,291,302,314,326,339,352,
365,379,393,408,423,439,455,471,488,505,
523,540,558,576,595,615,634,655,676,697,
719,741,764,788,811,836,861,886,912,939,
966,993,1021,1049,1077,1106,1136,1165,1195,1226,
1257,1287,1319,1350,1382,1413,1445,1477,1509,1541,
1573,1605,1637,1670,1702,1734,1767,1799,1832,1864,
1896,1925,1953,1982,2011,2040,2069,2099,2128,2157,
2187,2216,2246,2275,2305,2334,2363,2392,2421,2449,
2478,2506,2534,2562,2589,


2616,2641,2666,2691,2715,
2740,2763,2787,2810,2834,2857,2879,2902,2924,2946,
2968,2989,3011,3032,3053,3074,3094,3115,3135,3155,
3175,3192,3209,3226,3242,3258,3274,3290,3305,3319,
3334,3348,3362,3376,3389,3402,3415,3428,3440,3452,
3464,3476,3487,3499,3510,3521,3531,3542,3552,3562,
3573,3582,3592,3602,3611,3620,3630,3639,3647,3656,
3665,3673,3682,3690,3698,3706,3714,3722,3730,3738,
3745,3751,3756,3762,3767,3773,3778,3783,3789,3794,
3799,3804,3810,3815,3820,3825,3830,3835,3839,3844,
3849,3853,3858,3862,3867,3871,3875,3879,3883,3887,
3891,3895,3898,3902,3906,3909,3912,3916,3919,3922,
3925,3928,3931,3934,3937,3940,3942,3945,3947,3950
*/


117,123,129,136,143,150,157,165,173,181,
190,199,208,218,227,238,248,259,271,282,
295,307,320,334,347,362,376,392,407,423,
440,457,474,493,511,530,550,570,590,611,
633,655,678,701,725,749,774,799,825,851,
878,905,931,959,986,1015,1044,1073,1103,1133,
1164,1196,1227,1260,1292,1325,1359,1393,1427,1461,
1496,1531,1566,1602,1637,1673,1709,1745,1780,1816,
1852,1888,1924,1959,1995,2030,2065,2100,2134,2168,
2202,2236,2269,2302,2335,2368,2400,2432,2463,2495,
2526,2552,2579,2606,2633,2659,2686,2712,2738,2764,
2790,2816,2841,2866,2891,2916,2940,2964,2988,3011,
3034,3056,3078,3100,3122,

3143,3162,3181,3200,3219,
3237,3255,3272,3289,3306,3323,3339,3356,3371,3387,
3402,3418,3433,3447,3462,3476,3490,3504,3518,3531,
3544,3556,3567,3578,3589,3600,3610,3620,3630,3639,
3649,3658,3667,3675,3684,3692,3700,3708,3716,3724,
3731,3738,3745,3752,3759,3766,3772,3779,3785,3791,
3797,3803,3809,3815,3821,3826,3832,3837,3842,3848,
3853,3858,3863,3868,3873,3877,3882,3887,3891,3896,
3900,3903,3906,3910,3913,3916,3919,3922,3925,3928,
3931,3934,3937,3940,3943,3946,3949,3951,3954,3957,
3959,3962,3965,3967,3970,3972,3974,3977,3979,3981,
3983,3985,3987,3989,3991,3993,3995,3997,3999,4001,
4002,4004,4006,4007,4009,4010,4012,4013,4016,4020

};

void Word_Mul_Byte(void);
void EWord_Div_Word(void);
void GetSineWaveVPP(void);
void GetTempC(void);
void Display_Time(void);
void ReadADC(void);
void HeatCtrl(void);
void DisplayHexDigit(void);
void DisplayDecDigit(void);
void DisplayERR(void);
void DisplayOFF(void);
void F_to_C(void);
void C_to_F(void);
void OnOffHit(void);
void TimeHit(void);
void F2CHit(void);
void UpHit(void);
void DownHit(void);
void KeyCtrl(void);

void	FPPA0 (void)
{
	.ADJUST_IC	SYSCLK=IHRC/2, IHRC=16MHz, VDD=5V, Bandgap=On;
		//	WatchDog Disable, RAM 0 ~ 3 temporary be used
	//	You can add the follow Code :
	CLKMD.En_WatchDog	=	1;		// WatchDog Enable

	clkmd.En_Reset	=	1;			//	PA.5 as Reset pin
	//	Insert Initial Code
	DISGINT	
	Point   =   _SYS(SIZE.RAM) - 1;
	A = 0;
    do
    {  
		*Point = A;
	}while(--Point$0);

	PAC = 0B11011110;		//PA0,PA5设为输入，其它输出
	PBC = 0B11100010;		//PB0,PB2~4设为输入，其它输出
	PCC = 0xff;				//PC 输出

	$ T16M SYSCLK,/4,BIT8;	//256us = 4/8*512 @SYSCLK 8M
	$ INTEN T16,PA0;
	
	$ PBDIER 0B11111110;
	$ ADCM 12BIT,/16;		// 2us @SYSCLK 8M

	IntegsBak = 0x01;		// 上升沿中断
	INTEGS = IntegsBak;
	ENGINT

	BT134(OFF);			//关闭可控硅
	LED_GREEN(OFF);
	LED_RED(OFF);
	LED_BLUE(OFF);
	TmMs[3] = 50;			//蜂鸣50ms
	W_Time = 0xff;
/*
	KeyMsgCode=K_ONOFF;
	KeyMsgPressed=0x12;
	TmMs[1] = 20;
*/
	while(1) {
		wdreset;

		GetSineWaveVPP();
		KeyCtrl();
		HeatCtrl();
		Display_Time();
	}	
}
/*
* function name : ReadADC
* input : bpara1	0~7 ADC通道
*			
* output :	wpara1  12bit 转换结果
* Description: 平均算法<最多16次取平均>
*/
void ReadADC(void)
{
	uint8_t i;
	uint16_t sum;

	i = 0;
	sum = 0;
	bPara1 <<= 2;
	do {
		ADCC = 0x80+bPara1;
		AD_START = 1;
		WAIT1 AD_DONE;
		if(i>=2) {
			sum += ADCRH<<4;
			sum += ADCRL>>4;
		}
		i++;
	} while(i<6);
	wPara1 = sum>>2;
}

/*
* function name : GetSineWaveVPP
* input :	none
*			
* output :	
* Description: 
*/
void GetSineWaveVPP(void)
{
	uint8_t tflg;
static	uint16_t max,v,t;
	v = 0;
	t = 0;
	tflg =0;
	while(EnAD==2) {
//		bPara1 = VAD_CH;		// v
//		ReadADC();
//		if(wPara1>v)v = wPara1;
		bPara1 = TAD_CH;		// 	t
		ReadADC();		
		if(wPara1>t)t = wPara1;
		tflg |= 1;
	}
	if(tflg) {
		Vad = v;
		Tad = t;
		GetTempC();
	}
}

/*
* function name : 
* input :	none
*			
* output :
* Description: 
*/


/*
* function name : GetTempC
* input :	none
*			
* output :	
* Description: 
*/
void GetTempC(void)
{
	static uint8_t c;

	if((Tad<=10)||(Tad>=4086)) {
		if(TmMs[5]==0) {
			TmMs[5] = 10;
			c++;
			if(c>=20) {
				W_Stat |= ERR;
			}
		}
	} else {
		c = 0;
	byte	i = 0;
		while(i<250) {				// 查表获得实际温度值<摄氏度>
			wPara1 = vt_table1+i;
			wPara2 = *wPara1 $ W;
			if(Tad <= wPara2) break;
			i++;
		}
		W_RealTempC = i;
	}
}
/*
* function name : ReadKeyCode
* input :	none
*			
* output :	keyCode
* Description: 按下1 ，释放2 长按3 
*/
/*
void ReadKeyCode(void)
{
	uint8_t Code;
	static uint8_t tm;
	if(TmMs[1]==0) {
		TmMs[1] = 20;
		
		bPara1 = KAD_CH;
		ReadADC();
		Code = 0;
		if(wPara1>3072) {	//>3.75V
			Code = K_ONOFF;
		} else if(wPara1>1638) { //>2V
			Code = K_DOWN;
		} else if(wPara1>819) {	//>1v
			Code = K_UP;
		}
			
		if(Code>0) {
			if(tm)tm--;
			if(Code!=KeyMsgCode) {
				KeyMsgCode = Code;
			} else {
				if(KeyMsgPressed==0) {	//无按键时可触发
					KeyMsgPressed = 1;
					tm = 100;
				} else {
					A = KeyMsgPressed&0x0f;
					if((A==1)&&(tm==0)) {		//2S长按键
						KeyMsgPressed = 3;
					}
				} 
			}
		} else {
			if(tm) {
				tm = 0;
				KeyMsgPressed = 2;
			} else {
				KeyMsgPressed = 0;
			}
		}
	}
}
*/


void ReadKeyCode(void)
{
	uint8_t Code;
	static uint8_t tm;
	if(TmMs[1]==0) {
		TmMs[1] = 20;
		Code = PB&0x1C;	//P62(+),P63(-),P64(ONOFF)
		if(Code>0) {
			if(tm)tm--;
			if(Code!=KeyMsgCode) {
				KeyMsgCode = Code;
			} else {
				if(KeyMsgPressed==0) {	/*无按键时可触发*/
					KeyMsgPressed = 1;
					tm = 100;
				} else {
					A = KeyMsgPressed&0x0f;
					if((A==1)&&(tm==0)) {		//2S长按键
						KeyMsgPressed = 3;
					}
				} 
			}
		} else {
			if(tm) {
				tm = 0;
				KeyMsgPressed = 2;
			} else {
				KeyMsgPressed = 0;
			}
		}
	}
}



/*
* function name :KeyCtrl
* input :	none
*			
* output :
* Description:
*/
void KeyCtrl(void)
{	
	ReadKeyCode();
	if(KeyMsgPressed&&(KeyMsgPressed<16)) {
		KeyMsgPressed += 0x10;

/*
		if(W_Time==0) {
			W_Time = 0xff;
			return;
		}
//不重新开机
*/

/*
		
		if(W_Time==0) {
			W_Time = W_SetTime;
			W_Stat |= ON_MODE;//在定时关机时，按任何一个键重新开机
			return;
		}
//定时值调到0后不能重新加
*/


		if(W_Time==0) {
			if(W_SetTime==0) {
				W_Time = 0xff;
			} else {
				W_Time = W_SetTime;
			}
			W_Stat |= ON_MODE;//在定时关机时，按任何一个键重新开机
			W_Stat &= ~HEAT_HOLD;
			return;
		}




		if(KeyMsgCode==K_ONOFF) {
			if(KeyMsgPressed==0x13) { //长按响应
				OnOffHit();
				W_Dly = 3;		//3s
				TmMs[3] = 50;			//蜂鸣50ms
			}
		}
		A = W_Stat&ON_MODE;
		if(!A) return;
		switch(KeyMsgCode) {
			case K_UP:
				if(KeyMsgPressed==0x13) { //长按响应
					F2CHit();
					W_Dly = 3;		//3s
					TmMs[3] = 50;			//蜂鸣50ms
				} else if(KeyMsgPressed==0x12) {
					UpHit();
					W_Dly = 3;		//3s
					TmMs[3] = 50;			//蜂鸣50ms
				}
			break;
			case K_DOWN:
				if(KeyMsgPressed==0x13) { //长按响应
#if	EN_TIMESET == 1
					TimeHit();
					W_Dly = 3;		//3s
					TmMs[3] = 50;			//蜂鸣50ms
#endif
				} else if(KeyMsgPressed==0x12) {
					DownHit();
					W_Dly = 3;		//3s
					TmMs[3] = 50;			//蜂鸣50ms
				}
			break;
			default:break;
		} /*switch*/
	}
}
void DisTime(void)
{
	if(W_Time!=0xff) {

		LCD_T1(1);
		if(W_Time>90) {
			LCD_T2(1);
			LCD_T3(1);
			LCD_T4(1);
		} else if(W_Time>60) {
			LCD_T2(0);
			LCD_T3(1);
			LCD_T4(1);
		} else if(W_Time>30) {
			LCD_T2(1);
			LCD_T3(0);
			LCD_T4(1);
		} else if(W_Time) {
			LCD_T2(0);
			LCD_T3(1);
			LCD_T4(0);
		} else {
			LCD_T1(0);
			LCD_T2(0);
			LCD_T3(0);
			LCD_T4(0);	
		}
	} else {
		LCD_T1(0);
		LCD_T2(0);
		LCD_T3(0);
		LCD_T4(0);
	}
}
void Display_Time(void)
{
	static uint8_t blkg,Sec,Min,cnt;
	if(TmMs[2]==0) {
		TmMs[2] = 200;
		A = W_Stat&ON_MODE;
		if(A) {
			A = W_Stat&ERR;
			if(!A) {
				if(W_Dly==0) {
					A = W_Stat&S_TIME;
					if(A) {
						W_Stat &= ~S_TIME;
						if(W_SetTime==0)W_Time=0xff;
					}
#ifdef DEBUG
					wPara1 = Tad;
					DisplayHexDigit();
#else
					A = W_Stat&C_MODE;
					if(A) {
						A = W_Stat&HEAT_HOLD;
						if(A) {
							LED_GREEN(ON);
							LED_BLUE(OFF);
							LED_RED(OFF);
							wPara1 = W_TempC;
						} else {
							LED_GREEN(OFF);
							LED_BLUE(ON);
							LED_RED(OFF);
#if	DISP_REAL_TEMP == 1
							wPara1 = W_RealTempC;
#else
							wPara1 = W_TempC;
#endif
						}
						bPara1 = 1;			//高位0不显示
						DisplayDecDigit();
						LCD_C(1);
						LCD_F(0);
					} else {
						A = W_Stat&HEAT_HOLD;
						if(A) {
							wPara1 = W_TempF;
							LED_GREEN(ON);
							LED_BLUE(OFF);
							LED_RED(OFF);
						} else {
							LED_GREEN(OFF);
							LED_BLUE(ON);
							LED_RED(OFF);
#if	DISP_REAL_TEMP == 1
							bPara1 = W_RealTempC;
							C_to_F();
#else
							wPara1 = W_TempF;
#endif
						}
						bPara1 = 1;			//高位0不显示
						DisplayDecDigit();
						LCD_C(0);
						LCD_F(1);
					}
#endif					
				}
				LCD_HEAT(1);
				A = W_Stat&HEAT_HOLD;
				if(!A) {
					LCD_P1(1);
					cnt++;
					if(cnt==1) {
						LCD_P2(0);
						LCD_P3(0);
						LCD_P4(0);
					} else if(cnt==2) {
						LCD_P2(1);
						LCD_P3(0);
						LCD_P4(0);
					} else if(cnt==3) {
						LCD_P2(1);
						LCD_P3(1);
						LCD_P4(0);
					} else if(cnt==4) {
						LCD_P2(1);
						LCD_P3(1);
						LCD_P4(1);
						cnt = 0;
					}	
				} else {
					LCD_P1(1);
					LCD_P2(1);
					LCD_P3(1);
					LCD_P4(1);
				}
				DisTime();
				Sec++;
				if(Sec>=5) { //1s
					Sec = 0;
					if(W_Dly && (KeyMsgPressed==0)) {
						W_Dly--; 	// 显示延时倒计时
					}
					A = W_Stat&S_TIME;
					if(!A) {
						if(W_Time != 0xff) { // 定时器不为ff时启动
							Min++;
							if(Min>=60) { //60s
								Min = 0;
								if(W_Time) {
									W_Time--;
								} else {
                               	W_Stat &= ~ON_MODE;//定时关机时只是关机，其他标志保持不变。
								W_Stat &= ~HEAT_HOLD;//定时关机时将锁屏信号清除
									//	W_Stat = 0;
								}
							}
						}
					}
				}
			} else {
				DisplayERR();
			}
		} else {
			blkg++;
			if(blkg>=6)blkg=0;
			LED_GREEN(OFF);
			LED_RED(OFF);
			LED_BLUE(OFF);
			if(W_Time) {
				if(blkg>=3) {
					LED_BLUE(ON);//通电待机状态
				}
			} else {
				if(blkg>=3) {
					LED_RED(ON);//定时到状态
				}
			}
#ifdef DEBUG
			wPara1 = Vad;
			DisplayHexDigit();
#else
			DisplayOFF();
#endif
		}
	}
}

void HeatCtrl(void)
{
	uint8_t tc;
	A = W_Stat&ON_MODE;
	if(A) {
		A = W_Stat&ERR;
		if(!A) {
#ifdef	RESET_HEAT_TEMP
			A = W_TempC-W_RealTempC;
			if(A>RESET_HEAT_TEMP) {
				W_Stat &= ~HEAT_HOLD;
			}
#endif
			if(W_RealTempC<W_TempC) {
				W_Stat |= HEAT;
			} else {
				W_Stat |= HEAT_HOLD;
				W_Stat &= ~HEAT;
			}
//			A = Vad>>4;
//			if(A>115) { //220v
				TriacOnPeriod = EINT_CNT_220V;
				A = W_TempC-W_RealTempC;
				if(A<TEMP_SLOWUP) {
					TriacOnPeriod = EINT_CNT_220V*TEMP_SLOW_GAIN;
//				}	
//			} else {		//120V
//				TriacOnPeriod = EINT_CNT_120V;
//				A = W_TempC-W_RealTempC;
//				if(A<TEMP_SLOWUP) {
//					TriacOnPeriod = EINT_CNT_120V*TEMP_SLOW_GAIN;
//				}

			}
		} else {
			W_Stat &= ~HEAT;
		}
	} else {
		W_Stat &= ~HEAT;
	}
}

void	FPPA1 (void)
{
	goto	$;
}


void	Interrupt (void)
{
	pushaf;

	if (Intrq.T16)
	{	//	T16 Trig
		//	User can add Code
		Intrq.T16	=	0;
		wdreset;

		if(TmMs[4])TmMs[4]--; 			// TmMs4 可控硅导通时间
		else BT134(OFF);				//关闭可控硅
		TM0Cnt++;
	  	if(TM0Cnt>=4) {
	  		TM0Cnt = 0;
		  	if(TmMs[0])TmMs[0]--;				// TmMs0 显示扫描时间
		  	if(TmMs[1])TmMs[1]--;				// TmMs1 按键扫描时间
		  	if(TmMs[2])TmMs[2]--;				// TmMs2 显示处理周期
		  	if(TmMs[3])TmMs[3]--; 				// TmMs[3] 蜂鸣器时间
			if(TmMs[5])TmMs[5]--;
				
			$ COM0 IN;
			$ COM1 IN;
			$ COM2 IN;
			$ COM3 IN;
// 		b	7	6	5	4	3	2	1	0
// DRAM-seg	s4	s5	s2	s1	s6	s7	s8	s3
//			pa7	pa6	pc5	pc4	pa3	pa2	pa1	pa4
		  	switch(TmMs[0]) {
		  		case 0:
		  			TmMs[0] = 8;
					PA = (Dram[0]&0xce)|((Dram[0]&0x01)<<4)|(PA&(~0xde));
					PC = (Dram[0]&0x30)|(PC&(~0x30));
					$ COM0 OUT,LOW;
		  			break;
		  		case 1:
					PA = (Dram[1]&0xce)|((Dram[1]&0x01)<<4)|(PA&(~0xde));
					PC = (Dram[1]&0x30)|(PC&(~0x30));
					$ COM1 OUT,LOW;
		  			break;
		  		case 2:
		  			PA = (Dram[2]&0xce)|((Dram[2]&0x01)<<4)|(PA&(~0xde));
					PC = (Dram[2]&0x30)|(PC&(~0x30));
					$ COM2 OUT,LOW;
		  			break;
		  		case 3:
		  			PA = (Dram[3]&0xce)|((Dram[3]&0x01)<<4)|(PA&(~0xde));
					PC = (Dram[3]&0x30)|(PC&(~0x30));
					$ COM3 OUT,LOW;
		  			break;
		  		case 4:
		  			PA = (~Dram[0]&0xce)|((~Dram[0]&0x01)<<4)|(PA&(~0xde));
					PC = (~Dram[0]&0x30)|(PC&(~0x30));
					$ COM0 OUT,HIGH;
		  			break;
		  		case 5:
		  			PA = (~Dram[1]&0xce)|((~Dram[1]&0x01)<<4)|(PA&(~0xde));
					PC = (~Dram[1]&0x30)|(PC&(~0x30));
					$ COM1 OUT,HIGH;
		  			break;
		  		case 6:
		  			PA = (~Dram[2]&0xce)|((~Dram[2]&0x01)<<4)|(PA&(~0xde));
					PC = (~Dram[2]&0x30)|(PC&(~0x30));
					$ COM2 OUT,HIGH;
		  			break;
		  		case 7:
		  			PA = (~Dram[3]&0xce)|((~Dram[3]&0x01)<<4)|(PA&(~0xde));
					PC = (~Dram[3]&0x30)|(PC&(~0x30));
					$ COM3 OUT,HIGH;
		  			break;
		  		default:
		  			break;
		  	}
		}
		//...
	}
	if(Intrq.PA0) {
		Intrq.PA0 = 0;

		ExtInitCnt++;
		if(ExtInitCnt>=TriacOnPeriod) {
	  		ExtInitCnt = 0;
			A = W_Stat&HEAT;
	  		if(A) {
	  			W_Stat |= EN_TAD;
				BT134(ON);			//触发可控硅导通
				TmMs[4] = 3;			//750us
			}
	  	}
		IntegsBak ^= 0x03;
		INTEGS = IntegsBak;
		EnAD = IntegsBak;
		if(EnAD==1) { //调整开可控硅时为上升沿，检测温度
			W_Stat &= ~EN_TAD;
			A = (TriacOnPeriod-ExtInitCnt)&1;
			if(A==0) {
				IntegsBak ^= 0x03;
				INTEGS = IntegsBak;	//调整到下次下降沿
			}
		}

	}
	popaf;
}

/*
* function name : Word_Mul_Byte
* input : 	wpara1	16bit
*			bpara1	8bit
* output :	epara1
* Description: 16bit * 8bit = 24bit
*/
void Word_Mul_Byte(void)
{	//	ePara1[E]	=	bPara1[B] * wPara1[W]
	ePara1$1	=	0;
	ePara1$2	=	0;
	BYTE	cnt;
	cnt	=	8;

	do {
		bPara1	>>=	1;
		if (CF) {
			ePara1	+=	(wPara1 << 8);
		}
		ePara1	>>>=	1;
	} while (--cnt);
}
/*
* function name : EWord_Div_Word
* input : 	epara1	24bit
*			wpara1	16bit
* output :	商 epara1 余 wpara2  
* Description: 24bit / 16bit = 16bit
*/
void EWord_Div_Word(void)
{	//	ePara1[E] / wPara1[W]	=	ePara1[E] * wPara1[W] + wPara2[W]
	BYTE	div_cnt, div_tmp;
	div_cnt		=	8;
	wPara2	=	0;

	do {
		ePara1	<<=		1;
		wPara2	<<<=	1;
		div_tmp		<<<=	1;
		div_cnt++;
		A	=	(wPara2 - wPara1) >> 8;

		if (div_tmp.0 || ! CF) {
			wPara2$1	=	A;
			wPara2$0	-=	wPara1$0;
			ePara1.0	=	1;
		}
	} while (! div_cnt.5);
}
/*
* function name : Word_Div_Word
* input : 	wpara1	16bit
*			bpara1	8bit
* output :	商wpara1 余bPara2
* Description: 16bit / 8bit = 16bit
*/
void Word_Div_Byte (void)
{	//	wPara1[W] / bPara1[B]	=	wPara1[W] * bPara1[B] + bPara2[B]
	BYTE	div_cnt, div_tmp;
	div_cnt	=	0;
	bPara2	=	0;

	do
	{
		wPara1	<<=	1;
		slc		bPara2;
		slc		div_tmp;
		div_cnt++;
		A	=	bPara2	- bPara1;

		if (div_tmp.0 || !CF)
		{
			bPara2		=	A;
			wPara1.0	=	1;
		}
	} while (! div_cnt.4);
}

/*
* function name : F_to_C
* input : 
*			wpara1	16bit
* output :	bpara1  
* Description: (t-32)*5/9
*/
#if EN_FTC==1
void F_to_C(void)
{
	wPara1 -= 32;
	bPara1 = 5;
	Word_Mul_Byte();
	wPara1 = 9;
	EWord_Div_Word();
	bPara1 = ePara1;
}
#endif


/*
* function name : C_to_F
* input : 
*			bpara1
* output :	wpara1  
* Description: (t*9)/5+32
*/
void C_to_F(void)
{
	wPara1 = 9;
	Word_Mul_Byte();
	wPara1 = 5;
	EWord_Div_Word();
	wPara1 = ePara1+32;
}
/*
* function name :DisplayHexDigit 
* input :	wPara1	数据
*
* output :	none
* Description: hex码显示到3位数码管,从右到左显示
*/
#ifdef DEBUG 
void DisplayHexDigit(void)
{
	uint8_t tmp[3],x;
	wpara2 = DCode_tbl+(wPara1&0x000f);
	tmp [2] = *wpara2 $ L;
	wPara1 >>= 4;
	wpara2 = DCode_tbl+(wPara1&0x000f);
	tmp [1] = *wpara2 $ L;
	wPara1 >>= 4;
	wpara2 = DCode_tbl+(wPara1&0x000f);
	tmp [0] = *wpara2 $ L;
	x = 0;
// 		b	7	6	5	4	3	2	1	0
// DRAM-seg	s4	s5	s2	s1	s6	s7	s8	s3
	while(x<4) {
		wPara2 = Dram+x;
		if(x==3) {
			*wPara2 = (*wPara2&0xae)|((tmp[0]&0x01)<<4)|((tmp[1]&0x01))|((tmp[2]&0x01)<<6);
		} else {
			*wPara2 = (*wPara2&0x06)|((tmp[0]&0x03)<<4)|((tmp[1]&0x01))|((tmp[1]&0x02)<<6)|((tmp[2]&0x01)<<6)|((tmp[2]&0x02)<<2);
		}
		tmp[0] >>=2;
		tmp[1] >>=2;
		tmp[2] >>=2;
		x++;
	}
}
#endif
/*
* function name :DisplayDecDigit 
* input :	wPara1	数据
*			bPara1	1:不显示高位零 0:显示高位零
* output :	none
* Description: dec码显示到3位数码管,从右到左显示
*/
void DisplayDecDigit(void)
{
	uint8_t tmp[3],x;
	bPara1 = 10;
	Word_Div_Byte();
	wPara2 = DCode_tbl+bPara2;
	tmp[2] = *wPara2 $ L;
	Word_Div_Byte();
	if((bPara1==0) || (bPara2||wPara1)) { 
		wPara2 = DCode_tbl+bPara2;
		tmp[1] = *wPara2 $ L;
	} else {
		tmp[1] = 0;
	}
	Word_Div_Byte();
	if((bPara1==0) || bPara2) { 
		wPara2 = DCode_tbl+bPara2;
		tmp[0] = *wPara2 $ L;
	} else {
		tmp[0] = 0;
	}
	
	x = 0;
// 		b	7	6	5	4	3	2	1	0
// DRAM-seg	s4	s5	s2	s1	s6	s7	s8	s3
	while(x<4) {
		wPara2 = Dram+x;
		if(x==3) {
			*wPara2 = (*wPara2&0xae)|((tmp[0]&0x01)<<4)|((tmp[1]&0x01))|((tmp[2]&0x01)<<6);
		} else {
			*wPara2 = (*wPara2&0x06)|((tmp[0]&0x03)<<4)|((tmp[1]&0x01))|((tmp[1]&0x02)<<6)|((tmp[2]&0x01)<<6)|((tmp[2]&0x02)<<2);
		}
		tmp[0] >>=2;
		tmp[1] >>=2;
		tmp[2] >>=2;
		x++;
	}	
}
/*
* function name :DisplayERR 
* input :	
* output :	none
* Description:
*/
void DisplayERR(void)
{
	uint8_t tmp[3],x;
	
	wPara1 = DCode_tbl+14;
	tmp[0] = * wPara1 $ L; //E
	wPara1 = DCode_tbl+16;
	tmp[1] = * wPara1 $ L; //R
	tmp[2] = * wPara1 $ L; //R
	x = 0;
// 		b	7	6	5	4	3	2	1	0
// DRAM-seg	s4	s5	s2	s1	s6	s7	s8	s3
	while(x<4) {
		wPara2 = Dram+x;	
		*wPara2 = ((tmp[0]&0x03)<<4)|((tmp[1]&0x01))|((tmp[1]&0x02)<<6)|((tmp[2]&0x01)<<6)|((tmp[2]&0x02)<<2);
		tmp[0] >>=2;
		tmp[1] >>=2;
		tmp[2] >>=2;
		x++;
	}
}
#ifndef DEBUG
void DisplayOFF(void)
{
	uint8_t tmp[3],x;
	
	wPara1 = DCode_tbl+0;
	tmp[0] = * wPara1 $ L; //0
	wPara1 = DCode_tbl+15;
	tmp[1] = * wPara1 $ L; //f
	tmp[2] = tmp[1]; //f
	x = 0;
// 		b	7	6	5	4	3	2	1	0
// DRAM-seg	s4	s5	s2	s1	s6	s7	s8	s3
	while(x<4) {
		wPara2 = Dram+x;	
		*wPara2 = ((tmp[0]&0x03)<<4)|((tmp[1]&0x01))|((tmp[1]&0x02)<<6)|((tmp[2]&0x01)<<6)|((tmp[2]&0x02)<<2);
		tmp[0] >>=2;
		tmp[1] >>=2;
		tmp[2] >>=2;
		x++;
	}
}
#endif
void OnOffHit(void) 
{
	A = W_Stat&ON_MODE;
	if(A) {
		W_Stat = 0;
		W_SetTime = 0xff;
		W_Time = W_SetTime;
	} else {
#if DEFAULT_MODE == CM
		W_Stat = ON_MODE|C_MODE;
		W_TempC = DEFAULT_TEMP;	//默认温度
		bPara1 = W_TempC;
		C_to_F();
		W_TempF = wPara1;
		LCD_C(ON);
		wPara1 = W_TempC;
		bPara1 = 1;			//高位0不显示
		DisplayDecDigit();
#else
		W_Stat = ON_MODE;
		W_TempF = DEFAULT_TEMP;	//默认温度
		wPara1 = W_TempF;
		F_to_C();
		W_TempC = bPara1;
		LCD_F(ON);
		wPara1 = W_TempF;
		bPara1 = 1;			//高位0不显示
		DisplayDecDigit();
#endif
		W_SetTime = DEFAULT_TIME;
		W_Time = W_SetTime;
		LED_BLUE(ON);
	}
}
#if EN_TIMESET == 1
void TimeHit(void)
{
	A = W_Stat&S_TIME;
	if(!A) {
		W_Stat |= S_TIME;
		
		DisplayERR(); //清屏
		W_Time = W_SetTime;
		wPara1 = W_Time;
		bPara1 = 1;			//高位0不显示
		DisplayDecDigit();
		LED_GREEN(OFF);
		LED_RED(ON);
		LED_BLUE(OFF);
		DisTime();
	}
}
#endif

//#if EN_FTC==1
void F2CHit(void)
{
	W_Stat ^= C_MODE;
	A = W_Stat&C_MODE;
	if(A) {
		A = W_Stat&HEAT_HOLD;
		if(A) {
			wPara1 = W_TempC;
		} else {
			wPara1 = W_RealTempC;
		}
		bPara1 = 1;			//高位0不显示
		DisplayDecDigit();
		LCD_C(1);
		LCD_F(0);
	} else {
		A = W_Stat&HEAT_HOLD;
		if(A) {
			wPara1 = W_TempF;
		} else {
			bPara1 = W_RealTempC;
			C_to_F();
		}
		bPara1 = 1;			//高位0不显示
		DisplayDecDigit();
		LCD_C(0);
		LCD_F(1);
	}	
}
//#endif


void UpHit(void)
{
	A = W_Stat&S_TIME;
	if(A) {
		if(W_SetTime<=MAX_TIME) {
            if(W_SetTime<MAX_TIME)
			{
			W_SetTime += SETTIME_STEPV;
			}
			W_Time = W_SetTime;
			wPara1 = W_Time;
			bPara1 = 1;			//高位0不显示
			DisplayDecDigit();
		}
		else
		{
         W_SetTime=0;
		}


		LED_GREEN(OFF);
		LED_RED(ON);
		LED_BLUE(OFF);
		DisTime();
	} else {
#if	DEFAULT_MODE == CM
		if(W_TempC<MAX_TEMP) {
			W_TempC += SETTEMP_STEPV;
			
			bPara1 = W_TempC;
			C_to_F();
			W_TempF = wPara1;
			
			A = W_Stat&C_MODE;
			if(A) {
				wPara1 = W_TempC;
			} else {
				wPara1 = W_TempF;
			}
			bPara1 = 1;			//高位0不显示
			DisplayDecDigit();
		}
#else
		if(W_TempF<MAX_TEMP) {
			W_TempF += SETTEMP_STEPV;
			
			wPara1 = W_TempF;
			F_to_C();
			W_TempC = bPara1;
			
			A = W_Stat&C_MODE;
			if(A) {
				wPara1 = W_TempC;
			} else {
				wPara1 = W_TempF;
			}
			bPara1 = 1;			//高位0不显示
			DisplayDecDigit();
		}
#endif
		LED_GREEN(OFF);
		LED_RED(OFF);
		LED_BLUE(ON);
		W_Stat &= ~HEAT_HOLD;
	}
}

void DownHit(void)
{
	A = W_Stat&S_TIME;
	if(A) {
		if(W_SetTime>=SETTIME_STEPV) {
			W_SetTime -= SETTIME_STEPV;
			if(W_SetTime<=MIN_TIME)W_SetTime=MIN_TIME;
			W_Time = W_SetTime;
			wPara1 = W_Time;
			bPara1 = 1;			//高位0不显示
			DisplayDecDigit();
		}
		LED_GREEN(OFF);
		LED_RED(ON);
		LED_BLUE(OFF);
		DisTime();
	} else {
#if	DEFAULT_MODE == CM
		if(W_TempC>MIN_TEMP) {
			W_TempC -= SETTEMP_STEPV;
			
			bPara1 = W_TempC;
			C_to_F();
			W_TempF = wPara1;
			
			A = W_Stat&C_MODE;
			if(A) {
				wPara1 = W_TempC;
			} else {
				wPara1 = W_TempF;
			}
			bPara1 = 1;			//高位0不显示
			DisplayDecDigit();
		}
#else
		if(W_TempF>MIN_TEMP) {
			W_TempF -= SETTEMP_STEPV;
			
			wPara1 = W_TempF;
			F_to_C();
			W_TempC = bPara1;
			
			A = W_Stat&C_MODE;
			if(A) {
				wPara1 = W_TempC;
			} else {
				wPara1 = W_TempF;
			}
			bPara1 = 1;			//高位0不显示
			DisplayDecDigit();
		}
#endif
		LED_GREEN(OFF);
		LED_RED(OFF);
		LED_BLUE(ON);
		W_Stat &= ~HEAT_HOLD;
	}
}
