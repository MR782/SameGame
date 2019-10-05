#pragma once
#include<iostream>
#include"Purpose.h"
#include"Animation.h"

struct Text {
	Text();
	const char* str;//描画する文字
	int text_width;//テキストの長さ
	Point pos;//表示座標
	int font;//フォントハンドル
	int color;//色
};

struct Button {
	Button();
	std::unique_ptr<Animation> anime;//画像
	Point pos;//座標
	std::string message;//ボタン内表示メッセージ
	Rect hitBox;//当たり判定矩形
	void is_push(void (*funcB)());//押されたら引数の処理(戻り値void)を実行する
};

Text set_font(const char* str, Point pos, int font, int color);

int create_font(int size,int thick,bool is_anti_alias);

void draw_font(Text handle);