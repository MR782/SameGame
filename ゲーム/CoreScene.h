#pragma once
#include<memory>
#include"Engine.h"
#include"TitleScene.h"
#include"GameScene.h"
#include"InputNameScene.h"
#include"EndingScene.h"

//シーン管理
enum Scene {
	title,//タイトル
	name_input,
	game,//ゲームシーン
	result//リザルト画面
};

class CoreScene {
	Scene scene;//シーンを管理する列挙体
public:
	//メソッド
	CoreScene();
	void initialize();//全シーンの初期化
	void finalize();//全シーンの最終処理を行う
	void update();//シーンごとのupdate()を呼ぶ
	void draw();//シーンごとのdraw()を呼ぶ(ポーズなどでゲームのdraw()のみ呼びたいときのため作成)
	void scene_change(Scene);
	//メンバ変数
	GameScene *game;
	TitleScene *title;
	InputNameScene *input_name;
	EndingScene* ending_scene;

};

extern CoreScene *core;