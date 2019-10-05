#include "GameSceneUI.h"
#include"DxLib.h"
#include"ScreenSystem.h"
#include"Engine.h"

GameSceneUI::GameSceneUI()
{
}

void GameSceneUI::initialize()
{
	//サイズ32のフォント作成
	this->game_ui.font = create_font(32, 16, false);
	//文字列の長さをとるために仮の値を代入
	this->game_ui.str = "★Game Clear!★";
	this->game_ui.text_width = (unsigned int)strlen(this->game_ui.str);
	//値は入れ終えたので空に戻す
	this->game_ui.str = "";
	this->game_ui.color = GetColor(255, 255, 255);
	this->game_ui.pos = Point((ScreenSize::width / 2) - (this->game_ui.text_width / 2), ScreenSize::height / 5 * 4);
}

void GameSceneUI::finalize()
{
	//作成したフォントを削除
	DeleteFontToHandle(this->game_ui.font);
}

void GameSceneUI::update()
{
	if (Engine::get_gameclear_flag()) {
		this->game_ui.str = "★Game Clear!★";
	}
	else if (Engine::get_gameover_flag()) {
		this->game_ui.str = "★Game Over!★";
	}
}

void GameSceneUI::draw()
{
	DrawFormatString(0, 490, GetColor(255, 255, 0), "Score : %d", Engine::get_score());
	draw_font(this->game_ui);
}
