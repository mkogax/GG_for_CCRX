/*
	gg_sysdef.h	GGツール システム依存部
	
	2022.06.14	M.Kogan	初版開発開始

	***********************************
	***       RenesasCCRX専用       ***
	***********************************

	・TP機能が有効な場合(GG_TP_ENABLE)は Target Board RX130 の LED1(PD6)/LED2(PD7)ポートを使用

*/

#ifndef 	__GG_SYSDEF_H__
#define 	__GG_SYSDEF_H__


//#define GG_NO_CONSOLE       // EMUがつながってないとき対応（おまじない）	2022.07.19 M.Kogan


//------------------
//	環境
//------------------
#include "iodefine.h"        	// CPUレジスタとIO定義		2022.06.13 M.Kogan


//------------------
//	TP機能(テストピン)設定
//------------------

//#define GG_TP_ENABLE	// TP機能有効	コードを生成する(なければコード生成しない)

#ifdef GG_TP_ENABLE		// TP機能有効なら
	//***
	//*** Target Board RX130 の例。 LED1(PD6)/LED2(PD7)のポートを使用
	//*** 別ポートを使用する場合は下記6行を修正する
	//***
	#define GG_TP1_SETUP()	(PORTD.PDR.BIT.B6=1)	// テストピン1(TP1)を出力指定	--> PD6=出力
	#define GG_TP2_SETUP()	(PORTD.PDR.BIT.B7=1)	// テストピン2(TP2)を出力指定	--> PD7=出力
	#define GG_TP1_ON()		(PORTD.PODR.BIT.B6=1)	// テストピン1(TP1)をON			--> PD6=1
	#define GG_TP1_OFF()	(PORTD.PODR.BIT.B6=0)	// テストピン1(TP1)をOFF		--> PD6=0
	#define GG_TP2_ON()		(PORTD.PODR.BIT.B7=1)	// テストピン2(TP2)をON			--> PD7=1
	#define GG_TP2_OFF()	(PORTD.PODR.BIT.B7=0)	// テストピン2(TP2)をOFF		--> PD7=0
	int gg_tp_start(void);							// TP機能スタート(出力ピン初期化とコマンド登録)
#else
	#define GG_TP1_SETUP()
	#define GG_TP2_SETUP()
	#define GG_TP1_ON()
	#define GG_TP1_OFF()
	#define GG_TP2_ON()
	#define GG_TP2_OFF()
	#define gg_tp_start(void)						// TP機能スタート(ダミー)
#endif

//	GG_TP_ON(x)
//		GG_TP1==xならTP1(出力ピン1)をON
//		GG_TP2==xならTP2(出力ピン2)をON
//	GG_TP_OFF(x)
//		GG_TP1==xならTP1(出力ピン1)をOFF
//		GG_TP2==xならTP2(出力ピン2)をOFF
//
#ifdef GG_TP_ENABLE		// TP機能有効なら
	extern int gg_tp1_sel;					// TP1(出力ピン1)に出力する状態番号変数
	extern int gg_tp2_sel;					// TP2(出力ピン2)に出力する状態番号変数
	#define GG_TP1			(gg_tp1_sel)	// TP1(出力ピン1)に出力する状態番号
	#define GG_TP2			(gg_tp2_sel)	// TP2(出力ピン2)に出力する状態番号
	#define GG_TP_ON(x)		{if (GG_TP1==(x)) GG_TP1_ON();  if (GG_TP2==(x)) GG_TP2_ON();  }
	#define GG_TP_OFF(x)	{if (GG_TP1==(x)) GG_TP1_OFF(); if (GG_TP2==(x)) GG_TP2_OFF(); }
#else
	#define GG_TP1
	#define GG_TP2
	#define GG_TP_ON(x)
	#define GG_TP_OFF(x)
#endif


//------------------
//	割込み禁止制御
//------------------
//【 ルネサス RXシリーズ 】		ルネサス コンパイラ CC-RX V2.05以降
#define GG_DI_ON()		__clrpsw_i()	// 割込み禁止
#define GG_DI_OFF()		__setpsw_i()	// 割込み許可
#define GG_DI_BEGIN()	{ uint32_t __psw=__get_psw(); GG_DI_ON(); GG_TP_ON(1);						// 割禁開始 TP#1=割禁状態
#define GG_DI_END()		  __set_psw(__psw); if(__psw&0x10000) GG_TP_OFF(1); 	}					// 割禁解除 TP#1=割禁状態


//------------------
//	整数型宣言
//------------------
//	以下の整数型の宣言が必要
//	int8_t,int16_t,int32_t,int64_t,uint8_t,uint16_t,uint32_t,uint64_t

#if 0		//	stdint.hが無い場合は整数型を宣言する(#if 1とする)
typedef signed char			int8_t;
typedef signed short		int16_t;
typedef signed long			int32_t;
typedef signed long long	int64_t;
typedef unsigned char		uint8_t;
typedef unsigned short		uint16_t;
typedef unsigned long		uint32_t;
typedef unsigned long long	uint64_t;
double atof(const char *nptr);
#else
#include "stdint.h"
#include "stdlib.h"
#endif

#ifndef NULL
#define NULL (0)
#endif

#endif	//	__GG_SYSDEF_H__
