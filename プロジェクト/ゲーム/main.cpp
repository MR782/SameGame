//メモリリークを調べる
#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include<crtdbg.h>

#include "./dxlib/DxLib.h"
#include"CoreScene.h"
#include"KeyBoard.h"
#include"Mouse.h"
#include"ScreenSystem.h"
#include"ScreenFunction.h"
#include"Fps.h"

CoreScene *core;

// WinMain関数
int WINAPI WinMain(
	_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//メモリリーク確認
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//log.txtを作成しない
	SetOutApplicationLogValidFlag(FALSE);
	// 画面モードの設定
	//画面サイズ設定
	ScreenSize::height = 640;
	ScreenSize::width = 960;
	SetGraphMode(ScreenSize::width, ScreenSize::height, 32);//ウィンドウのサイズを決める
	ChangeWindowMode(TRUE);// ウィンドウモード変更

	//ウィンドウタイトル
	SetMainWindowText("Title");

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1) { return -1; };//dxlibがないなら終了

	ScreenFunction::initialize();//フェードアウト・インの初期化
	core = new CoreScene;//全てのシーンを総括するオブジェクトのインスタンス生成
	//Fps測定と待機
	Fps fps;
	//-------------------------------------------------
	SetDrawScreen(DX_SCREEN_BACK);//裏画面設定

	core->initialize();//一部の画像や音楽ファイルを読み込む
	KeyBoard::initialize();//キーボード入力に必要なメモリ確保
	Mouse::initialize();//マウス入力をとるために必要な初期化処理

	//メインループ
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {//画面更新＆メッセージ処理&画面殺害		
		KeyBoard::update();//キーボードの更新処理
		Mouse::update();//マウスの更新処理
		//ゲームの更新処理
		core->update();
		//ゲームの描画処理
		core->draw();
		//名前入力のプログラム
		//Engine::input_name();
		//FPS測定・待機(一定のFPSとする)
		fps.update();
		fps.wait();
		//Escキーを押されたらゲームを終了する
		if (KeyBoard::key_down(KEY_INPUT_ESCAPE)) {
			break;
		}
	}
	core->finalize();//読み込んだファイルやvectorの中身削除
	InitGraph();//dxlibの読み込んだ画像を全削除する関数

	delete core;//メモリ削除

	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;				// ゲーム終了
}
	