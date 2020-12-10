#include "DxLib.h"

const char TITLE[] = "学籍番号名前：タイトル";

const int WIN_WIDTH = 1200; //ウィンドウ横幅
const int WIN_HEIGHT = 400;//ウィンドウ縦幅


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);						//ウィンドウモードに設定
	//ウィンドウサイズを手動では変更できず、かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(TITLE);					// タイトルを変更
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);	//画面サイズの最大サイズ、カラービット数を設定（モニターの解像度に合わせる）
	SetWindowSizeExtendRate(1.0);				//画面サイズを設定（解像度との比率で設定）
	SetBackgroundColor(0x00, 0x00, 0xFF);		// 画面の背景色を設定する

	//Dxライブラリの初期化
	if (DxLib_Init() == -1) { return -1; }

	//（ダブルバッファ）描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	//画像などのリソースデータの変数宣言と読み込み



	//ゲームループで使う変数の宣言
	char keys[256] = { 0 }; //最新のキーボード情報用
	char oldkeys[256] = { 0 };//1ループ（フレーム）前のキーボード情報

	int MouseX, MouseY;
	double EasingX1[] = { 100.0 };
	double EasingX2[] = { 100 };
	double Vel1[] = { 50.0 };
	double Vel2[] = { 1.0 };
	int num = 0;

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


		if (keys[KEY_INPUT_SPACE] == 1) {
			num = 0;
		}

		num += 1;

　　　　　　　　　printf("ローカルうんたら");
		
		SetDrawBlendMode(DX_BLENDMODE_ADD, 170);

		DrawBox(100, 100, 116, 116, GetColor(255, 0, 0), TRUE);

		for (int i = 0; i < num; i++) {

			if (EasingX1[i] >= 900.0) {
				EasingX1[i] = 900.0;
				DrawBox(EasingX1[i], 100, EasingX1[i] + 16, 116, GetColor(255, 0, 0), TRUE);
				break;
			}

			else if (i >0) {
				Vel1[i] = Vel1[i - 1] * 1.1;
				EasingX1[i] = Vel1[i] + 100;
				DrawBox(EasingX1[i], 100, EasingX1[i] + 16, 116, GetColor(255, 255, 255), TRUE);
			}
		}

		DrawBox(100, 200, 116, 216, GetColor(255, 0, 0), TRUE);

		for (int i = 0; i < num; i++) {

			if (EasingX2[i] >= 900.0) {
				EasingX2[i] = 900.0;
				DrawBox(EasingX2[i], 100, EasingX2[i] + 16, 116, GetColor(255, 0, 0), TRUE);
				break;
			}

			else if (i >0) {
				Vel2[i] = Vel2[i - 1] * 0.9;
				EasingX2[i] = EasingX2[i - 1] + Vel2[i];
				DrawBox(EasingX2[i], 200, EasingX2[i] + 16, 216, GetColor(255, 255, 255), TRUE);
			}
		}


		//描画処理




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
