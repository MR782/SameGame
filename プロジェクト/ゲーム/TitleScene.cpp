#include "TitleScene.h"
#include"Audio.h"
#include"Mouse.h"
#include"CoreScene.h"
#include"ScreenFunction.h"
#include"ScreenSystem.h"
#include"Resource.h"
#include"DxLib.h"

void TitleScene::initialize()
{
	this->back_graph = GraphicResource::get_handle("title_back")[0];
	//テキストの表示位置
	this->title_ui.initialize();

	//タイトルBGM
	Audio::load("title");
	//タイトルSE
	Audio::load("decision");
	//タイトルBGM再生
	Audio::play("title");
}

void TitleScene::finalize()
{
	this->title_ui.finalize();
	//音楽を止める
	Audio::stop("title");
	//オーディオデータの削除
	Audio::delete_soundData_scope("title");
}

void TitleScene::update()
{
	//左クリックされたら
	if (Mouse::left_mouse_down()) {
		//フェードアウト開始
		Engine::set_fade_ioFlag(true);
		Audio::play("decision");
	}
	//真っ暗になったら
	if (ScreenFunction::check_brend_max()) { 
		//シーンを変える
		core->scene_change(Scene::name_input);//名前入力シーンに遷移
		Engine::set_fade_ioFlag(false);
	}
}

void TitleScene::draw()
{
	//背景画像を拡縮描画
	DrawExtendGraph(0, 0, ScreenSize::width, ScreenSize::height, this->back_graph, FALSE);
	//UIの描画
	this->title_ui.draw();
}
