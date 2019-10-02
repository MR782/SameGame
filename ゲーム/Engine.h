#pragma once
#include<iostream>
#include<Windows.h>
#include<vector>

//ゲームを通して必要なものの定義

struct User {
	char name[6];//名前は6文字まで
	int score;//スコア
};

class Engine {
private:
	static bool gameover_flag;//ゲームオーバー判定
	static bool gameclear_flag;//ゲームクリア判定
	//false : フェードイン　true : フェードアウト
	static bool fade_ioFlag;
	//プレイヤーの名前
	static User user;
	static int buf_num;//ユーザーを入力する際に使用
public:
	static void initialize();
	//フラグや値をセットする
	//false : フェードイン　true : フェードアウト
	static void set_fade_ioFlag(bool);
	//スコアをセット
	static void set_score(int);
	//名前を入力
	static void input_name();
	static void set_default_name();
	//ゲームオーバーフラグをセット
	static void set_gameover_flag(bool flag);
	static void set_gameclear_flag(bool flag);

	//値を受け取る
	static bool get_fade_ioFlag();
	static int get_score();
	static char* get_user_name();
	static bool get_gameover_flag();
	static bool get_gameclear_flag();
};