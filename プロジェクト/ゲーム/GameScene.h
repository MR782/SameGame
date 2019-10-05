#pragma once
#include "GameBoard.h"
#include"GameSceneUI.h"
//ゲーム本編

class GameScene {
	GameSceneUI game_ui;
public:
	//メソッド
	GameScene();
	void initialize();
	void finalize();
	void update();
	void draw();
};

namespace model {
	extern std::unique_ptr<GameBoard> board;
}
