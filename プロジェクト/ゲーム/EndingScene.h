#pragma once
#include"Purpose.h"
#include"Ranking.h"
#include"Animation.h"

//�Q�[���{�ҏI����̃V�[��

class EndingScene {
	int back_graph;
	Ranking ranking;
public:
	void initialize();
	void finalize();
	void update();
	void draw();
};