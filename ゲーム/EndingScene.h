#pragma once
#include"Purpose.h"
#include"Ranking.h"

//�Q�[���{�ҏI����̃V�[��

class EndingScene {
	Ranking ranking;
public:
	void initialize();
	void finalize();
	void update();
	void draw();
};