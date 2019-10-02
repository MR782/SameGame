#include "Mouse.h"
#include"DxLib.h"

//左クリック
int Mouse::left_previous;//1フレーム前
int Mouse::left_current;//作業領域
//右クリック用
int Mouse::right_previous;//１フレーム前
int Mouse::right_current;//作業領域
//マウス座標
Point Mouse::previous_pos;//1フレーム前
Point Mouse::current_pos;//作業領域

void Mouse::initialize()
{
	//初期化
	left_current = 0;
	left_previous = 0;
	right_current = 0;
	right_previous = 0;
	previous_pos = Point(0, 0);
	current_pos = Point(0, 0);
}

void Mouse::update()
{
	//1フレーム前の座標
	previous_pos << current_pos;
	//1フレーム前のマウスの状態
	left_previous = left_current;
	right_previous = right_current;

	//座標判定
	GetMousePoint(&current_pos.x,&current_pos.y);
	//クリック判定
	left_current = (GetMouseInput() & MOUSE_INPUT_LEFT);
	right_current = (GetMouseInput() & MOUSE_INPUT_RIGHT);
}

//---------------------------------------------------------------------------
//左クリック
//---------------------------------------------------------------------------
bool Mouse::left_mouse_down()
{
	return left_previous == 0 && left_current != 0;
}

bool Mouse::left_mouse_up()
{
	return left_previous != 0 && left_current == 0;
}

bool Mouse::left_mouse_press()
{
	return left_current != 0 && left_previous != 0;
}

bool Mouse::left_mouse_not_press()
{
	return left_current == 0 && left_previous == 0;
}
//---------------------------------------------------------------------------
//右クリック
//---------------------------------------------------------------------------
bool Mouse::right_mouse_down()
{
	return right_previous == 0 && right_current != 0;
}

bool Mouse::right_mouse_up()
{
	return right_previous != 0 && right_current == 0;
}

bool Mouse::right_mouse_press()
{
	return right_previous != 0 && right_current != 0;
}

bool Mouse::right_mouse_not_press()
{
	return right_previous == 0 && right_current == 0;
}

bool Mouse::check_current_pos()
{			//          X座標                           Y座標
	return previous_pos.x != current_pos.x || previous_pos.y != current_pos.y;
}

Point Mouse::get_mouse_pos()
{
	return previous_pos;
}
