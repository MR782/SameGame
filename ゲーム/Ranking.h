#pragma once
#include"RankingData.h"

class Ranking {
	std::vector<RankingData::Status> rank_data;
public:
	RankingData data;
	void initialize();
	void finalize();
	void draw();
};