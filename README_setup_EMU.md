# GG for CCRX【 EMU 】セットアップ説明

## ハードウェア環境

### 基板

この例ではルネサスエレクトロニクス株式会社の [Target Board for RX130](https://www.renesas.com/jp/ja/products/microcontrollers-microprocessors/rx-32-bit-performance-efficiency-mcus/rtk5rx1300c00000br-target-board-rx130) 基板を使用します。この基板にはデバッガ(E2 エミュレータ Lite 相当)の機能が搭載されています。開発用PCとUSBでつなぐだけで、電源供給およびプログラムの書込み/デバッグができます。

### 基板とPCの接続

基板とPCをUSBでつなぎます。  
基板の以下のピンをオシロスコープと接続します。
|ピン番号|用途|接続先|
|---|---|---|
|62|GND：信号GND|オシロスコープのGND|
|80|PD6：TP1出力ピン(基板LED0兼用)|オシロスコープのCH1|
|79|PD7：TP2出力ピン(基板LED1兼用)|オシロスコープのCH2|

```mermaid
flowchart LR
    id1(Target Board RX130 基板) ---|USB|id3(開発用PC)
    id1---|GND|id4(オシロスコープ)
    id1-->|PD6->CH1|id4
    id1-->|PD7->CH2|id4
```

#### オシロスコープ

GGのコンソール機能を使うだけであれば不要です。GGのTP機能を使ってプログラムのタイミング分析をするために使用します。この例では以下を使っています。  
[SIGLENT SDS 1104X-E](https://siglent.jp/sl/sds1000x-e-series/)  
CH1,CH2,GND以外はつなぎません。

## ソフトウェア環境

ルネサスエレクトロニクス株式会社の [統合開発環境 CS+](https://www.renesas.com/jp/ja/software-tool/cs) と [CC-RXコンパイラ](https://www.renesas.com/jp/ja/software-tool/cc-compiler-package-rx-family) を使います。  

|ツール|動作確認時のバージョン|
|---|---|
|統合開発環境 CS+ for CC|V8.07.00|
|Compiler Standard V3 for RX(CC-RX)|V3.04.00|

### ソフトウェア環境の構築手順【 EMU 】

1. CS+ for CC でプロジェクトを作成（R5F51308AxFP、アプリケーション(CC-RX)、プロジェクト名=任意）
2. プロジェクトフォルダに GG_for_CCRX\src の内容を全てコピー
3. プロジェクトツリーに GG_for_CCRX_EMU.c と GG_main.c ファイルを登録
4. プロジェクトツリーに ggフォルダ 配下の 全.c ファイルを登録
5. プロジェクトツリーから プロジェクト名.c ファイルを外す
6. プロジェクトツリーのデバッグツールをRX E2 Liteに変更し、プロパティで・・
7. メインクロックソースをHOCO(32MHz)にし
8. 内蔵フラッシュメモリ書き換え時のクロック操作を許可するを"はい"にする
9. ビルドツールプロパティの・・
10. コンパイルオプションの追加のインクルードパスに . と gg を追加する
11. ビルドのリビルドプロジェクトを実行
12. デバッグのデバッグツールへダウンロードを実行(対象OSなし)
13. 表示 - デバッグコンソール でデバッグコンソールを表示する
14. デバッグコンソール上で右クリックメニューでローカルエコーバックを無効にする
15. デバッグの実行
16. デバッグコンソールでhelp[enter]と入力する

* mdコマンドでメモリダンプ中に改行が混じることがあるようです。これは既知の問題です。すいません。(EMUだけ発生します)(原因はわかっていません)

### 仕様変更のための修正箇所【 EMU 】

#### GG_main.c

* タイトル、初回プロンプト
* 初期コマンド登録

#### gg_sysdef.h

* TP機能の有効化(GG_TP_ENABLE)
* TP機能で使用する出力ポート
