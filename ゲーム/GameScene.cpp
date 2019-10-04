#include "GameScene.h"
#include"DxLib.h"
#include"KeyBoard.h"
#include"Audio.h"
#include"Engine.h"
#include"ScreenFunction.h"
#include"CoreScene.h"
#include"ScreenSystem.h"

std::unique_ptr<GameBoard> model::board;

//オブジェクト
GameScene::GameScene()
{
	//メモリ確保
	model::board = std::make_unique<GameBoard>();
}

void GameScene::initialize()
{
	//データの初期化-----------------------------------
	model::board->initialize();
	Engine::set_score(0);
}

void GameScene::finalize()
{
}

void GameScene::update()
{
	model::board->update();
	//Enterキーが押されたら
	if (KeyBoard::key_down(KEY_INPUT_RETURN)) {
		//フェードアウト開始
		Engine::set_fade_ioFlag(true);
	}
	if (ScreenFunction::check_brend_max()) {
		Engine::set_fade_ioFlag(false);
		core->scene_change(Scene::result);
	}
}

void GameScene::draw()
{
	model::board->draw();
	DrawFormatString(0, 490, GetColor(255, 255, 0), "Score : %d", Engine::get_score());
	if (Engine::get_gameclear_flag() == true) {
		DrawString(ScreenSize::width / 2, 490, "Game Clear!", GetColor(255, 255, 0));
	}
	else if (Engine::get_gameover_flag() == true) {
		DrawString(ScreenSize::width / 2, 490, "Game Over!", GetColor(255, 255, 0));
	}
}
