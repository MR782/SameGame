#pragma once
#include"Purpose.h"
#include"Ranking.h"

//ゲーム本編終了後のシーン

class EndingScene {
	Ranking ranking;
public:
	void initialize();
	void finalize();
	void update();
	void draw();
};