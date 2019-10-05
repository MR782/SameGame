#pragma once
#include"Purpose.h"
#include"Ranking.h"
#include"Animation.h"

//ゲーム本編終了後のシーン

class EndingScene {
	int back_graph;
	Ranking ranking;
public:
	void initialize();
	void finalize();
	void update();
	void draw();
};