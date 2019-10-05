#include "Ranking.h"
#include <string>
#include <algorithm>
#include <functional>
#include<fstream>
#include"DxLib.h"

RankingData::RankingData()
{
}

void RankingData::input_ranking(int score_,std::string name_)
{
	Status state;
	state.name = name_;
	state.score = score_;
	//ランキングの配列に追加
	ranking.push_back(state);

	swap_ranking(Sort::DESC);
	//ランキングのデータが50個以上あるなら
	if (ranking.size() > 50) {
		//50個以降を削除する
		ranking.erase(ranking.begin() + 50, ranking.end());
	}
}

void RankingData::swap_ranking(Sort s)
{
	switch (s)
	{
	case RankingData::ASC:
		//昇順に並び替える
		std::sort(ranking.begin(), ranking.end());
		break;
	case RankingData::DESC:
		//降順に並び替える
		std::sort(ranking.begin(), ranking.end(), std::greater<Status>());
		break;
	}
}

void RankingData::reset_ranking()
{
	//データを削除する
	ranking.clear();
}

void RankingData::input_textfile_data(std::string filepath)
{
	reset_ranking();//データを削除
	std::ifstream fp(filepath);
	//見つからないなら例外を投げる
	if (fp.fail()) "text file is not found";
	Status state;
	while (!fp.eof()) {//末端ではないなら
		//データを入れる
		fp >> state.name >> state.score;
		//vectorに入れる
		ranking.push_back(state);
	}
	//降順に並び替える
	swap_ranking(Sort::DESC);
	fp.close();//ファイルを閉じる
}

void RankingData::output_textfile_data(std::string filepath)
{
	//ランキングの中身が空なら例外を投げる
	if (ranking.empty())throw "ranking data is empty";

	std::ofstream fp(filepath);
	//見つからないなら例外を投げる
	if (fp.fail()) "text file is not found";
	swap_ranking(Sort::DESC);//並び替え

	int size = 0;
	for (auto itr = ranking.begin(); itr != ranking.end(); itr++, size++) {
		if (size < 50) {
			//最後でないなら改行する
			if (itr == ranking.end() - 1) fp << itr->name << " " << itr->score;
			else fp << itr->name << " " << itr->score << "\n";
		}
	}
	fp.close();//データを入れたら閉じる
}

void RankingData::reset_textfile_data(std::string filepath)
{
	std::ofstream fp(filepath);
	//見つからないなら例外を投げる
	if (fp.fail()) "text file is not found";
	for (int i = 0; i < 50; ++i) {
		//    name      score
		if (i < 50 - 1) fp << "NULL" << 0 << "\n";
		else fp << "NULL" << 0;
	}
}

std::vector<RankingData::Status> RankingData::get_ranking()
{
	return this->ranking;
}

std::vector<RankingData::Status> RankingData::get_rank(int val)
{
	std::vector<Status> return_value;
	int cnt = 0;
	for (auto itr = ranking.begin(); itr != ranking.end(); itr++, cnt++) {
		if (cnt >= val) break;//指定数受け取ったらループを抜ける
		return_value.push_back(*itr);
	}
	return return_value;
}
