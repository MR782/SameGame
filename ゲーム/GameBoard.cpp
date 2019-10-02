#include "GameBoard.h"
#include<Windows.h>
#include"CoreScene.h"
#include"DxLib.h"
#include"Mouse.h"

void GameBoard::initialize()
{
	//データの初期化
	ZeroMemory(this->arr, sizeof(this->arr));
	this->previous_cellPos = Point(-1, -1);
	this->blinkCnt = 0;
	//チップに情報を入れる
	this->chip = GraphicResource::get_handle("board");
	//石をセット
	set(4);
}

void GameBoard::finalize()
{
}

void GameBoard::update()
{
	//マウス座標を取得
	Point mouse_pos = Mouse::get_mouse_pos();
	//画面の入力範囲内か確認
	if (mouse_pos.x >= 0 && mouse_pos.y >= 0
		&&
		mouse_pos.x < Stone_Width * GameBoard_Width && mouse_pos.y < Stone_Height * GameBoard_Height){
		//マス単位の座標に変換
		Point masu = Point(mouse_pos.x / Stone_Width, mouse_pos.y / Stone_Height);
		//マウスカーソル位置が以前のセルと異なるなら
		if (this->previous_cellPos.x != masu.x || this->previous_cellPos.y != masu.y) {
			this->previous_cellPos = masu;//更新
			//接続範囲抽出
			erase_check(masu);
		}
		//マウスの左ボタンが押されたら
		if (Mouse::left_mouse_down()) {
			int e_cnt = erase_cnt();//消せる石を数える
			if (e_cnt >= 2) {//消せる石が2個以上なら
				//スコア増加
				Engine::set_score(Engine::get_score() + (e_cnt * e_cnt));
				//連結している石を消す
				erase();
				//石を落とす
				fall();
				//右にずらす
				move_right();
				//全消し判定
				if (check_clear()) {
					Engine::set_score(Engine::get_score() + 1000);
					Engine::set_gameclear_flag(true);
				}
				else if (check_gameover()) {
					Engine::set_gameover_flag(true);
				}
				//マウスを動かなくても再チェックさせる
				this->previous_cellPos.x = -1;
				this->previous_cellPos.y = -1;
			}
		}
	}
	//強調表示用のカウンタを更新
	this->blinkCnt++;
	if (this->blinkCnt > INT_MAX)this->blinkCnt = 0;
}

void GameBoard::draw()
{
	//画面に表示する範囲だけ表示
	for (int y = 0; y < GameBoard_Height; y++) {
		for (int x = 0; x < GameBoard_Width; x++) {
			//石があるなら
			if (this->arr[y][x] != 0) {
				//消せる石を点滅させる
				if (this->blinkCnt % 20 < 10 && this->erase_log[y][x] == 1) {
					continue;
				}
				Point pos = Point(x * Stone_Width, y * Stone_Height);
				DrawGraph(pos.x, pos.y, this->chip[this->arr[y][x]], TRUE);
			}
		}
	}
}

void GameBoard::set(int value)
{
	//石を配置
	int cnt = 0;
	for (int y = 0; y < GameBoard_Height; y++) {
		for (int x = 0; x < GameBoard_Width; x++) {
			this->arr[y][x] = cnt + 1;
			//1以上のデータを用意(0は空のため)
			cnt = (cnt + 1) % value;
		}
	}
	//石をシャッフルする
	shuffle();
}

void GameBoard::shuffle()
{
	for (int y = 0; y < GameBoard_Height; y++) {
		for (int x = 0; x < GameBoard_Width; x++) {
			int rand_x = rand() % GameBoard_Width;
			int rand_y = rand() % GameBoard_Height;
			//配列データを入れ替え
			int temp = this->arr[y][x];// A <- B
			this->arr[y][x] = this->arr[rand_y][rand_x];// B <- C
			this->arr[rand_y][rand_y] = temp;// C <- A
		}
	}
}

void GameBoard::erase_check(Point pos)
{
	//範囲探索準備
	ZeroMemory(this->erase_log, sizeof(this->erase_log));
	int kind = this->arr[pos.y][pos.x];
	//指定座標が空白なら
	if (kind == 0) { return; }//終了
	//範囲探索開始
	this->erase_check_recursion(pos.x, pos.y, kind);
}

void GameBoard::erase_check_recursion(int x, int y, int kind)
{
	//現在地がすでに探索済みなら中断
	if (this->erase_log[y][x] != 0) { return; }
	//石の種類が違うなら中断
	if (this->arr[y][x] != kind) { return; }
	//現在地をマーキング
	this->erase_log[y][x] = 1;
	//隣接するマスをチェック(上下左右)
	if (x - 1 >= 0) { this->erase_check_recursion(x - 1, y, kind); }//左
	if (x + 1 < GameBoard_Width) { this->erase_check_recursion(x + 1, y, kind); }//右
	if (y - 1 >= 0) { this->erase_check_recursion(x, y - 1, kind); }//上
	if (y + 1 < GameBoard_Height) { this->erase_check_recursion(x, y + 1, kind); }//下
}

int GameBoard::erase_cnt()
{
	int cnt = 0;
	for (int y = 0; y < GameBoard_Height; y++) {
		for (int x = 0; x < GameBoard_Width; x++) {
			cnt += this->erase_log[y][x];//erase_logには0か1しかないためこの書き方ができる
			//if(this->erase_log[y][x] == 1){  cnt++;  }//他の書き方
		}
	}
	return cnt;
}

void GameBoard::erase()
{
	for (int y = 0; y < GameBoard_Height; y++) {
		for (int x = 0; x < GameBoard_Width; x++) {
			if (this->erase_log[y][x] != 0) {
				this->arr[y][x] = 0;
			}
		}
	}
	//erase_logを全て0にする
	ZeroMemory(this->erase_log, sizeof(this->erase_log));
}

void GameBoard::fall()
{
	//全てに0を入れる
	int board[GameBoard_Height][GameBoard_Width] = { {0} };
	for (int x = 0; x < GameBoard_Width; x++) {
		//下から上に向かって処理を行う
		int y2 = GameBoard_Height - 1;
		//詰めた結果をboardに書き込んでいく
		for (int y = GameBoard_Height - 1; y >= 0; y--) {
			//石が存在するなら
			if (this->arr[y][x] != 0) {
				//上書き
				board[y2][x] = this->arr[y][x];
				y2--;
			}
		}
	}
	//データを上書きする
	memcpy(this->arr, board, sizeof(board));
}

void GameBoard::move_right()
{
	int board[GameBoard_Height][GameBoard_Width] = { {0} };//初期化
	int x2 = GameBoard_Width - 1;
	//右から左に向かって処理を行う
	for (int x = GameBoard_Width - 1; x >= 0; x--) {
		//縦1ライン全て空白ならラインを移す
		if (this->arr[9][x] == 0) continue;
		//ラインを詰めてboardに書き込む
		for (int y = 0; y < GameBoard_Height; y++) {
			board[y][x2] = this->arr[y][x];
		}
		x2--;
	}
	//データを上書き
	memcpy(this->arr, board, sizeof(board));
}

bool GameBoard::check_clear()
{
	//右下のデータが空ならクリア
	return this->arr[GameBoard_Height - 1][GameBoard_Width - 1] == 0;
}

bool GameBoard::check_gameover()
{
	bool check = false;
	for (int y = 0; y < GameBoard_Height; y++) {
		for (int x = 0; x < GameBoard_Width; x++) {
			if (this->arr[y][x] != 0) {
				Point pos = Point(x, y);
				erase_check(pos);
				//消せる石をチェック
				int e_cnt = erase_cnt();
				//消せる石が2つ未満なら
				if (e_cnt < 2) {
					check = true;
				}
			}
		}
	}
	return check;
}
