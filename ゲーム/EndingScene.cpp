#include "EndingScene.h"
#include"Mouse.h"
#include"ScreenFunction.h"
#include"CoreScene.h"
#include"Engine.h"

void EndingScene::initialize()
{
	ranking.initialize();
	//テキストファイルにランキングデータを入力
	ranking.data.reset_textfile_data("./data/txt/rank.txt");//すでに入力済みのデータを削除
	ranking.data.output_textfile_data("./data/txt/rank.txt");//新しいデータを入力
}

void EndingScene::finalize()
{
	ranking.finalize();
}

void EndingScene::update()
{
	if (Mouse::left_mouse_down()) {
		//タイトルシーンに戻る
		Engine::set_fade_ioFlag(true);
	}
	if (ScreenFunction::check_brend_max()) {
		core->scene_change(Scene::title);
		Engine::set_fade_ioFlag(false);
	}
}

void EndingScene::draw()
{
	ranking.draw();
}
