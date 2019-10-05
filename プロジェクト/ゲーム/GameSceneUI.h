#pragma once
#include"BasicUI.h"

class GameSceneUI {
	Text game_ui;
public:
	GameSceneUI();
	void initialize();
	void finalize();
	void update();
	void draw();
};