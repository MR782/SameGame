#include "Ranking.h"
#include"ScreenSystem.h"
#include"DxLib.h"
#include"Engine.h"

void Ranking::initialize()
{
	//ラベルに入っているパスからデータを読み込む
	this->data.input_textfile_data("./data/txt/rank.txt");
	//ユーザー名とスコアを入れる
		//入力した名前とゲームのスコアをランキングに追加
	this->data.input_ranking(Engine::get_score(), Engine::get_user_name());
	//Top5のデータを持ってくる
	this->rank_data = this->data.get_rank(5);
}

void Ranking::finalize()
{
	this->rank_data.clear();
}

void Ranking::draw()
{
	int cnt = 0;
	for (auto itr = this->rank_data.begin(); itr != this->rank_data.end(); itr++,cnt++) {
		//上から下に描画
		int posY = 25 * cnt;//間隔
		int posX = ScreenSize::width / 2;
		unsigned int color = GetColor(255, 0, 0);
		//順位     プレイヤーの名前 スコアの順に描画する
		DrawString(posX, 75, "Rank   Name  SCORE",color);
		DrawFormatString(posX, posY + 100, color, "%d      %s : %d", cnt + 1 , (*itr).name.c_str(), (*itr).score);
	}
}
