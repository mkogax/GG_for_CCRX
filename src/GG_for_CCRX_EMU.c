/*
    GG_for_CCRX_EMU.c   ルネサスCCRX用GGツール(EMU使用版)(実行コード)
    
    2022.06.14  M.Kogan 初版開発開始


    エミュレータ(E1/E2/E2 Lite..)のデバッグコンソールでシリアル入出力する

*/

#include "GG.h"             // GGツールヘッダ


#define FC2E0   (*(volatile uint32_t *)0x00084080)
#define FE2C0   (*(volatile uint32_t *)0x00084090)
#define DBGSTAT (*(volatile uint32_t *)0x000840C0)
#define RXFL0EN (0x00001000)
#define TXFL0EN (0x00000100)

void charputEMU(int c)      // 1文字出力(EMU)
{
    while(DBGSTAT&TXFL0EN)  ;
    FC2E0 = c;
}
int chargetEMU(void)        // 1文字入力(EMU)   -1=なし
{
    if (!(DBGSTAT&RXFL0EN)) return -1;
    return FE2C0;
}


static int std_putc_sub(int c)
{
    charputEMU(c);
    return 0;
}
static int std_putc(int c)
{
    if (c=='\n') std_putc_sub('\r'); 
    return std_putc_sub(c);
}
static int std_getc()
{
    return chargetEMU();
}


int gg_start(const char *title)     // GGの処理開始
{
    gg_std_putc = std_putc;     // SCI1への出力ルーチン
    gg_std_getc = std_getc;     // SCI1からの入力ルーチン

    // GGツールベース初期化
    gg_con_MonInit();           // GGモニタ初期化
    gg_con_RegistHelpCMD();     // helpコマンド登録

    // デバッグモニタ開始(タイトル表示) 旧:gg_con_MonStart()
    if (title) gg_PutS(title);

    return 0;
}

//
//  TP機能
//
#ifdef GG_TP_ENABLE     // TP機能有効な場合

int gg_tp1_sel = -1;            // TP1(出力ピン1)状態番号変数
int gg_tp2_sel = -1;            // TP2(出力ピン2)状態番号変数
static int C_tp(int argc, char**argv)                   // TP設定
{
    if (argc<=4) {
        if (argc>1) GG_TP1   = gg_asc2int(argv[1]);
        if (argc>2) GG_TP2   = gg_asc2int(argv[2]);
        gg_printf("<TP status number(The specified status number appears in TP)>\n");
        gg_printf("TP1 = %3d (-1=do nothing)\n", GG_TP1);
        gg_printf("TP2 = %3d (-1=do nothing)\n", GG_TP2);
    } else {
        gg_con_CmdHelp(argv[0]);
    }
    return 0;
}
int gg_tp_start(void)                                   // TP機能スタート(出力ピン初期化とコマンド登録)
{
    // TP出力の初期化(出力に初期化)
    GG_TP1_SETUP();         // テストピン1(TP1)を出力指定
    GG_TP2_SETUP();         // テストピン2(TP2)を出力指定

    // コマンド登録
    GG_CON_CMDMRK("-- TP command --");      // 区切り行（helpでコマンド一覧のときに表示）
    GG_CON_CMDADD(C_tp,     "tp",       "[#1 [#2]]",            "TP(test point) select" );      //
    return 0;
}

#endif  // GG_TP_ENABLE
