#include "KeyBoard.h"
#include"./dxlib/DxLib.h"

char* KeyBoard::current;
char* KeyBoard::previous;
//char* KeyBoard::work;

void KeyBoard::initialize()
{
	//領域確保
	current = new char[KEY_BOARD_BUF];
	previous = new char[KEY_BOARD_BUF];
}

void KeyBoard::finalize()
{
	//領域開放
	delete[] current;
	delete[] previous;
}

void KeyBoard::update()
{
	//作業領域と１フレーム前の入れ替え
	static char* work;

	work = current;     
	current = previous;  
	previous = work;    

	GetHitKeyStateAll(current);
}

bool KeyBoard::key_down(int k_)
{
	//今は押されているが１フレーム前は押されていない
	return *(current + k_) == 1 && *(previous + k_) == 0;
}

bool KeyBoard::key_up(int k_)
{
	//今は押されていないが1フレーム前は押されていた
	return *(current + k_) == 0 && *(previous + k_) == 1;
}

bool KeyBoard::key_press(int k_)
{
	//今現在押されているなら
	return *(current + k_) == 1;
}

char KeyBoard::check_hitkey()
{
	//----------------アルファベット------------------
	if (KeyBoard::key_down(KEY_INPUT_A)) return 'A';
	else if (KeyBoard::key_down(KEY_INPUT_B)) return 'B';
	else if (KeyBoard::key_down(KEY_INPUT_C)) return 'C';
	else if (KeyBoard::key_down(KEY_INPUT_D)) return 'D';
	else if (KeyBoard::key_down(KEY_INPUT_E)) return 'E';
	else if (KeyBoard::key_down(KEY_INPUT_F)) return 'F';
	else if (KeyBoard::key_down(KEY_INPUT_G)) return 'G';
	else if (KeyBoard::key_down(KEY_INPUT_H)) return 'H';
	else if (KeyBoard::key_down(KEY_INPUT_I)) return 'I';
	else if (KeyBoard::key_down(KEY_INPUT_J)) return 'J';
	else if (KeyBoard::key_down(KEY_INPUT_K)) return 'K';
	else if (KeyBoard::key_down(KEY_INPUT_L)) return 'L';
	else if (KeyBoard::key_down(KEY_INPUT_M)) return 'M';
	else if (KeyBoard::key_down(KEY_INPUT_N)) return 'N';
	else if (KeyBoard::key_down(KEY_INPUT_O)) return 'O';
	else if (KeyBoard::key_down(KEY_INPUT_P)) return 'P';
	else if (KeyBoard::key_down(KEY_INPUT_Q)) return 'Q';
	else if (KeyBoard::key_down(KEY_INPUT_R)) return 'R';
	else if (KeyBoard::key_down(KEY_INPUT_S)) return 'S';
	else if (KeyBoard::key_down(KEY_INPUT_T)) return 'T';
	else if (KeyBoard::key_down(KEY_INPUT_U)) return 'U';
	else if (KeyBoard::key_down(KEY_INPUT_V)) return 'V';
	else if (KeyBoard::key_down(KEY_INPUT_W)) return 'W';
	else if (KeyBoard::key_down(KEY_INPUT_X)) return 'X';
	else if (KeyBoard::key_down(KEY_INPUT_Y)) return 'Y';
	else if (KeyBoard::key_down(KEY_INPUT_Z)) return 'Z';
	//-----------------数字--------------------------
	else if (KeyBoard::key_down(KEY_INPUT_1)) return '1';
	else if (KeyBoard::key_down(KEY_INPUT_2)) return '2';
	else if (KeyBoard::key_down(KEY_INPUT_3)) return '3';
	else if (KeyBoard::key_down(KEY_INPUT_4)) return '4';
	else if (KeyBoard::key_down(KEY_INPUT_5)) return '5';
	else if (KeyBoard::key_down(KEY_INPUT_6)) return '6';
	else if (KeyBoard::key_down(KEY_INPUT_7)) return '7';
	else if (KeyBoard::key_down(KEY_INPUT_8)) return '8';
	else if (KeyBoard::key_down(KEY_INPUT_9)) return '9';
	else if (KeyBoard::key_down(KEY_INPUT_0)) return '0';
	//-------------------その他-----------------------
	else if (KeyBoard::key_down(KEY_INPUT_SPACE)) return ' ';
	else if (KeyBoard::key_down(KEY_INPUT_RETURN)) return '*';//ENTERを押されたら入力終了の合図を送る
	//どこにも当てはまらないなら空を返す
	return '\0';
}
