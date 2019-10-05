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
	game_ui.initialize();
	Engine::set_score(0);
	Engine::set_gameclear_flag(false);
	Engine::set_gameover_flag(false);
}

void GameScene::finalize()
{
	game_ui.finalize();
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
	//UIの更新処理
	game_ui.update();
}

void GameScene::draw()
{
	//ゲーム盤の描画
	model::board->draw();
	//UIの描画
	game_ui.draw();
}
