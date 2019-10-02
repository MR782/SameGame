#pragma once
#include"Purpose.h"

//マウス入力を受け取る

class Mouse {
	//左クリック用
	static int left_previous;//1フレーム前
	static int left_current;//作業領域
	//右クリック用
	static int right_previous;//1フレーム前
	static int right_current;//作業領域
	//マウス座標
	static Point current_pos;//1フレーム前
	static Point previous_pos;//作業領域
public:
	static void initialize();
	static void update();
	//左クリック用
	static bool left_mouse_down();
	static bool left_mouse_up();
	static bool left_mouse_press();
	static bool left_mouse_not_press();
	//右クリック用
	static bool right_mouse_down();
	static bool right_mouse_up();
	static bool right_mouse_press();
	static bool right_mouse_not_press();
	//マウス座標
	static bool check_current_pos();//1フレーム前と今の座標を比べて移動しているか判定(フリック判定)
	static Point get_mouse_pos();
};