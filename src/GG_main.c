/*
    GG_main.c           メインプログラム

    2022.06.14  初版


    main()  メインエントリとループ

*/


#include "GG.h"             // GGツールヘッダ


int C_test1(int argc, char **argv)  // test1コマンド実行部
{
  int i;
  gg_printf("argc=%d\n", argc);
  for (i=0; i<argc; i++) {
    long x = 0;
    if (gg_isdigit(argv[i][0])) x = gg_asc2int(argv[i]);
    gg_printf("argv[%2d] %-16s (0x%08lX,%ld)\n", i, argv[i], x, x);
  }
  return 0;
}

int dummy(int n)            // ダミーソフト負荷
{
    static int c = 0;
    while(n>0) {
        c += n--;
    }
    return c;
}

void main(void)
{

    gg_start("** GG for CCRX **\n>");   // Start processing GG for CCRX
    gg_con_RegistMemCMD();              // メモリ系コマンド登録

    // Register with console command (you can add more and more in this way)
    GG_CON_CMDMRK("-- Example of original command registration --");     // Delimited line (displayed in the command list)
    GG_CON_CMDADD(C_test1, "test1", "[...]", "Display command line arguments when executing this command" );  // [1]command(function),[2]command(name),[3]help(parameters),[4]help(description)

#ifdef GG_TP_ENABLE
    gg_tp_start();                      // TP機能の開始(TPコマンド登録)
#endif

    while(1) {

        // Turn number 10 twice on and off at the beginning of loop
        GG_TP_ON(10);   // number 10 ON
        GG_TP_OFF(10);  // number 10 OFF
        GG_TP_ON(10);   // number 10 ON
        GG_TP_OFF(10);  // number 10 OFF

        // number 20 : Observe the processing time of gg_con_Check()
        GG_TP_ON(20);   // number 20 ON
        gg_con_Check(); // console processing (returns immediately if nothing is done)
        GG_TP_OFF(20);  // number 20 OFF

        // number 30 : Observe the processing time of dummy(50)
        GG_TP_ON(30);   // number 30 ON
        dummy(50);
        GG_TP_OFF(30);  // number 30 OFF

    }

}
