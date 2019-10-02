#pragma once
#include"Object.h"
#include"define.h"

class GameBoard {
	int arr[GameBoard_Height][GameBoard_Width];//石のデータ配列
	int erase_log[GameBoard_Height][GameBoard_Width];//消去するための配列
	int* chip;//ブロック情報
	int  blinkCnt;//消すことのできる意思を強調表示するためのカウンタ
	Point previous_cellPos;//直前の選択セル
	//メソッド
	void set(int value);//石をセットする
	void shuffle();//石をシャッフルする
	void erase_check(Point pos);//接続範囲を抽出
	void erase_check_recursion(int x,int y,int kind);//再帰によって範囲探索を行う
	int erase_cnt();//消せる石の数をカウント
	void erase();//対象の石を削除する
	void fall();//石を下に落とす処理
	void move_right();//右にずらす処理
	bool check_clear();//クリア判定
	bool check_gameover();//ゲームオーバー判定
public:
	void initialize();
	void finalize();
	void update();
	void draw();
};