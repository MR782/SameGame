#pragma once
#include"RankingData.h"

class Ranking {
	std::vector<RankingData::Status> rank_data;
	int* rank_no_graph;//1�ʁ`5�ʂ̕`��
public:
	RankingData data;
	void initialize();
	void finalize();
	void draw();
};