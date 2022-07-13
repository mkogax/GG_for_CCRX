# GG for CCRX

GG はシリアルコンソールを実現するための支援ライブラリです。コンソールを組み込むための補助的なツール（例えば書式付出力や文字列変換）を含みます。

[GG for CCRX](https://github.com/mkogax/GG_for_CCRX) は ルネサスエレクトロニクス株式会社の [RX 32ビット高性能・高効率MCU](https://www.renesas.com/jp/ja/products/microcontrollers-microprocessors/rx-32-bit-performance-efficiency-mcus) でのポーティング例です。ここにあるソースを使ってご自分でプロジェクトを作り自動生成プログラム（FITモジュール）を導入してご利用ください。（サンプルとしてプロジェクトファイルごと全部公開できないか考えたのですが、確認取れてないので自前で作った分だけ公開しています)  

[GG for Arduino](https://github.com/mkogax/GG_for_Arduino) は Arduinoでのポーティング例です。Arduinoの公式ライブラリに登録されておりArduino IDEのライブラリマネージャからダウンロードできます。  

ここでは GG for CCRX について説明します。  

https://user-images.githubusercontent.com/11693904/174795973-64f355ec-863e-4973-9ffd-dcf78ff891ba.mp4

## ソフトウェア環境

ルネサスエレクトロニクス株式会社の [統合開発環境 CS+](https://www.renesas.com/jp/ja/software-tool/cs) と [CC-RXコンパイラ](https://www.renesas.com/jp/ja/software-tool/cc-compiler-package-rx-family) を使います。

|ツール|動作確認時のバージョン|
|---|---|
|統合開発環境 CS+ for CC|V8.07.00|
|Compiler Standard V3 for RX(CC-RX)|V3.04.00|

## シリアル通信の種類とセットアップ

3種類のシリアル通信についてセットアップ方法を説明します。

### 【 SCI 】SCIのシリアル通信

SCIのシリアル通信を接続したパソコン上のターミナルソフト(TeraTermなど)で利用します。  
ソフトウェア環境は CS+ を想定しています。  
ハードウェアは Target Board for RX130基板 を想定しています。  
SCIのシリアル通信とPCはUSBシリアル変換器で中継します。  
[**【 SCI 】セットアップ説明**](README_setup_SCI.md)

### 【 EMU 】エミュレータ経由のシリアル通信

エミュレータ(E2 Liteなど)経由のシリアル通信をCS+付属のデバッグコンソールで利用します。  
ソフトウェア環境は CS+ を想定しています。  
ハードウェアは Target Board for RX130基板 を想定しています。  
[**【 EMU 】セットアップ説明**](README_setup_EMU.md)

### 【 SIM 】シミュレータ経由のシリアル通信

シミュレータ経由のシリアル通信をCS+付属のデバッグコンソールで利用します。  
ソフトウェア環境は CS+ を想定しています。  
ハードウェアは使用しません。  
[**【 SIM 】セットアップ説明**](README_setup_SIM.md)

## GG for CCRX　機能説明

[**GG for CCRX　機能説明**](README_spec.md)

## GG for CCRX　使用例

[**NORTi を RX Smartconfigurator と一緒に使う方法**](https://github.com/mkogax/How-to-use-NORTi-with-RX-Smartconfigurator)

* エミュレータ経由のシリアル通信で利用しています。
* NORTiのタスク状態表示/操作をGGのコンソールコマンド(taskコマンド)として実装しています。
* 実行タイミングをTP機能で観測しています。
