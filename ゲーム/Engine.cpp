#include "Engine.h"
#include"Audio.h"
#include"KeyBoard.h"
#include"DxLib.h"
//-------------------------------------
// 実体化
//-------------------------------------
bool Engine::fade_ioFlag;//フェードを管理するフラグ
User Engine::user;//ユーザーデータ
int Engine::buf_num;
bool Engine::gameover_flag;
bool Engine::gameclear_flag;

void Engine::initialize()
{
	//初期化
	fade_ioFlag = false;
	//ユーザーデータ
	for (int i = 0; i < 6; i++) {
		user.name[i] = '\0';
	}
	user.score = 0;
	buf_num = 0;
	gameover_flag = false;
	gameclear_flag = false;
}

void Engine::set_fade_ioFlag(bool flag)
{
	fade_ioFlag = flag;
}

void Engine::set_score(int point)
{
	user.score = point;
}

void Engine::input_name()
{
	//バックスペースが押されて　かつ　先頭データでないなら
	if (KeyBoard::key_down(KEY_INPUT_BACK) && buf_num != 0) {
		user.name[buf_num - 1] = '\0';//一つ前のデータを削除
		buf_num--;//1つ前に戻す
	}
	//全て入力し終わってないなら入力処理を行う
	if (buf_num < 5) {
		//配列にデータが入っていないならその中身に値を入れる
		if (user.name[buf_num] != '\0') buf_num++;
		buf_num = min(6, buf_num);//7バイト以上書き込む可能性を阻止
		//値(char型)を入れる
		user.name[buf_num] = KeyBoard::check_hitkey();

		//ENTERが押されて*が入ったら現在の入力内容を削除して処理を終える
		if (user.name[buf_num] == '*') {
			for (int i2 = buf_num; i2 < 5; i2++) {
				//それ以降に空きがあるなら空白として扱う
				user.name[i2] = ' ';
			}
			buf_num = 5;
		}
	}
}

void Engine::set_default_name()
{
	if (user.name[0] == ' ') {
		//何も入っていないならNULLという名前が入る
		user.name[0] = 'N';
		user.name[1] = 'U';
		user.name[2] = 'L';
		user.name[3] = 'L';
		user.name[4] = ' ';
		user.name[5] = ' ';
	}
}

void Engine::set_gameover_flag(bool flag)
{
	gameover_flag = flag;
}

void Engine::set_gameclear_flag(bool flag)
{
	gameclear_flag = flag;
}

bool Engine::get_fade_ioFlag()
{
	return fade_ioFlag;
}

int Engine::get_score()
{
	return user.score;
}

char* Engine::get_user_name()
{
	return user.name;
}

bool Engine::get_gameover_flag()
{
	return gameover_flag;
}

bool Engine::get_gameclear_flag()
{
	return gameclear_flag;
}
