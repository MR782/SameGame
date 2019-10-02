#pragma once
#include "GameBoard.h"
//ゲーム本編

class GameScene {
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
