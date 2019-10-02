#include "CoreScene.h"
#include"KeyBoard.h"
#include"Audio.h"
#include"Resource.h"
#include"ScreenFunction.h"
#include"ScreenHelperGraph.h"
#include"Engine.h"
#include"DxLib.h"

CoreScene::CoreScene()
{
	//メモリ確保
	title = new TitleScene();
	game = nullptr;
	input_name = nullptr;
	ending_scene = nullptr;
	//初期シーン設定
	scene = Scene::title;
}

void CoreScene::initialize()
{
	//画像と音楽の読み込みの準備
	GraphicResource::init();
	Audio::init();

	//使用画像をロード
	GraphicResource::load("all");

	//初期シーンの初期化
	title->initialize();
	//ゲーム内で使うデータの初期化
	Engine::initialize();
	ScreenFunction::initialize();
}

void CoreScene::finalize()
{
	//キーボードや読み込んだデータ、作成したデータを削除
	KeyBoard::finalize();
	GraphicResource::finalize();
	Audio::finalize();
	ScreenFunction::finalize();
	//シーンの終了処理
	//終了時のシーンに応じて処理を変える
	switch (this->scene)
	{
	case Scene::game:
		game->finalize();
		delete game;
		break;
	case Scene::name_input:
		input_name->finalize();
		delete input_name;
		break;
	case Scene::result:
		ending_scene->finalize();
		break;
	case Scene::title:
		title->finalize();
		delete title;
		break;
	default://どのシーンにも当てはまらないなら
		"Scene is exception";//例外を投げる
		break;
	}
}

void CoreScene::update()
{
	//現在のシーンに合わせて処理変える
	switch (scene)
	{
	case Scene::title:
		title->update();
		break;
	case Scene::game:
		game->update();
		break;
	case Scene::result:
		ending_scene->update();
		break;
	case Scene::name_input:
		input_name->update();
		break;
	default://どのシーンにも当てはまらないなら
		"Scene is exception";//例外を投げる
		break;
	}
	//フェードアウト・インの更新処理
	ScreenFunction::update();
}

//描画の総括
void CoreScene::draw()
{
	//シーンに合わせて描画するものを変える
	switch (scene)
	{
	case Scene::title:
		title->draw();
		break;
	case Scene::game:
		game->draw();
		break;
	case Scene::result:
		ending_scene->draw();
		break;
	case Scene::name_input:
		input_name->draw();
		break;
	default://どのシーンにも当てはまらないなら
		"Scene is exception";//例外を投げる
		break;
	}
	//フェードアウト・インの描画
	ScreenFunction::draw(ScreenHelperGraph::white_graph);
}

void CoreScene::scene_change(Scene scene_)
{
	//シーンを変える前に初期化処理を行う
	//現在のシーンの終了処理を行う
	switch (this->scene) {
	case Scene::title:
		title->finalize();
		delete title;
		break;
	case Scene::game:
		game->finalize();
		delete game;
		break;
	case Scene::result:
		ending_scene->finalize();
		delete ending_scene;
		break;
	case Scene::name_input:
		input_name->finalize();
		delete input_name;
		break;
	default://どのシーンにも当てはまらないなら
		"Scene is exception";//例外を投げる
		break;
	}
	//遷移するシーンの初期化を行う
	switch (scene_)
	{
	case Scene::title:
		title = new TitleScene();
		title->initialize();
		break;
	case Scene::game:
		game = new GameScene();
		game->initialize();
		break;
	case Scene::result:
		ending_scene = new EndingScene();
		ending_scene->initialize();
		break;
	case Scene::name_input:
		input_name = new InputNameScene();
		input_name->initialize();
		break;
	default://どのシーンにも当てはまらないなら
		"Scene is exception";//例外を投げる
		break;
	}
	scene = scene_;//シーンの更新
}
