#include "InputNameScene.h"
#include"Engine.h"
#include"DxLib.h"
#include <algorithm>
#include <functional>
#include"KeyBoard.h"
#include"Audio.h"
#include"CoreScene.h"
#include"ScreenFunction.h"
#include"ScreenSystem.h"

void InputNameScene::initialize()
{
	//オーディオデータ読み込み
	Audio::load("decision");
	Audio::load("input_name");
	//背景画像用のメモリ確保と画像セット
	GraphData g_data_back;
	g_data_back.anime.set("input_name_back");
	g_data_back.position = Point(0, 0);
	g_data_back.drawing_order = 1;
	g_data_back.name = "back";
	//テキストボックス画像
	GraphData g_data_txtBox;
	g_data_txtBox.anime.set("text_box");
	g_data_txtBox.position = Point(ScreenSize::width / 2 - 150 / 2, ScreenSize::height / 2);
	g_data_txtBox.drawing_order = 2;
	g_data_txtBox.name = "text_box";
	//vectorに追加
	anime.push_back(g_data_back);
	anime.push_back(g_data_txtBox);
	//昇順に並び替える
	std::sort(anime.begin(), anime.end());
}

void InputNameScene::finalize()
{
	anime.clear();
	Audio::delete_soundData_name("input_name");
}

void InputNameScene::update()
{
	Engine::input_name();
	//Enterキーが押されたら
	if (KeyBoard::key_down(KEY_INPUT_RETURN)) {
		//名前が未入力の場合デフォルトの名前を入れる
		Engine::set_default_name();
		//効果音を鳴らす
		Audio::play("decision");
		//フェードアウト開始
		Engine::set_fade_ioFlag(true);
	}
	if (ScreenFunction::check_brend_max()) {
		//シーン変更
		core->scene_change(Scene::game);
		//フェードイン開始
		Engine::set_fade_ioFlag(false);
	}
}

void InputNameScene::draw()
{
	//描画を行う
	for (auto itr = anime.begin(); itr != anime.end(); itr++) {
		(*itr).anime.draw_anime((*itr).position);
		//テキストボックスの場所に文字を出す
		if ((*itr).name == "text_box") {
			//入力した名前を可視化
			DrawString((*itr).position.x, (*itr).position.y - 50, "名前を入力してください(半角大文字英数)", GetColor(255, 255, 255));
			DrawString((*itr).position.x, (*itr).position.y + 50, "Enterで入力終了", GetColor(255, 255, 255));
			DrawFormatString((*itr).position.x, (*itr).position.y + 5, GetColor(0, 0, 0), "      %s", Engine::get_user_name());
		}
	}
}

InputNameScene::GraphData::GraphData()
{
	this->drawing_order = 0;
	this->name = "";
	this->position = Point(0, 0);
}
