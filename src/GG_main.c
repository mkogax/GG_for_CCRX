/*
    GG_main.c           メインプログラム

    2022.06.14  初版


    main()  メインエントリとループ

*/


#include "GG.h"             // GGツールヘッダ


void main(void)
{

    gg_start("** GG for CCRX **\n>");   // Start processing GG for CCRX
    gg_con_RegistMemCMD();              // メモリ系コマンド登録
#ifdef GG_TP_ENABLE
    gg_tp_start();                      // TP機能の開始(TPコマンド登録)
#endif

    while(1) {
        gg_con_Check();                 // console processing (returns immediately if nothing is done)
    }

}
