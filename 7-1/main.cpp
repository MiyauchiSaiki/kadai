#include "DxLib.h"
#include<time.h>

const char TITLE[] = "GC1B_19_宮内彩輝";

const int WIN_WIDTH = 600; //ウィンドウ横幅
const int WIN_HEIGHT = 400;//ウィンドウ縦幅


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);						//ウィンドウモードに設定
	//ウィンドウサイズを手動では変更できず、かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(TITLE);					// タイトルを変更
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);	//画面サイズの最大サイズ、カラービット数を設定（モニターの解像度に合わせる）
	SetWindowSizeExtendRate(1.0);				//画面サイズを設定（解像度との比率で設定）
	SetBackgroundColor(0, 0, 0);		// 画面の背景色を設定する

	//Dxライブラリの初期化
	if (DxLib_Init() == -1) { return -1; }

	//（ダブルバッファ）描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	//画像などのリソースデータの変数宣言と読み込み

	int Graph;
	Graph = LoadGraph("white.png");

	//ゲームループで使う変数の宣言
	char keys[256] = { 0 }; //最新のキーボード情報用
	char oldkeys[256] = { 0 };//1ループ（フレーム）前のキーボード情報

	int ShakeTate = 100;
	int ShakeYoko = 100;
	int ObjTimer = 1500;
	int ShakeWidth = 10;


	srand(time(NULL));

	// ゲームループ
	while (1)
	{
		//最新のキーボード情報だったものは１フレーム前のキーボード情報として保存

		//最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		//画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		//更新処理
		if (ObjTimer > 0) {
			ObjTimer -= 1;

			ShakeTate = rand() % 10 * ShakeWidth;
			ShakeYoko = rand() % 10 * ShakeWidth;

			if (ShakeWidth > 0 && ObjTimer % 150 == 0) {
				ShakeWidth -= 1;
			}

			if (rand() % 2 == FALSE) {
				ShakeTate = ShakeTate * -1;
			}

			if (rand() % 2 == FALSE) {
				ShakeYoko = ShakeYoko * -1;
			}
		}

		//描画処理

		DrawGraph(300 + ShakeTate, 200 + ShakeYoko, Graph, TRUE);


		//---------  ここまでにプログラムを記述  ---------//
		ScreenFlip();//（ダブルバッファ）裏面
		// 20ミリ秒待機（疑似60FPS）
		WaitTimer(20);
		// Windows システムからくる情報を処理する
		if (ProcessMessage() == -1)
		{
			break;
		}
		// ＥＳＣキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	//Dxライブラリ終了処理
	DxLib_End();

	return 0;
}