#pragma once
#include<memory>
#include"Animation.h"

//プレイヤー名の入力を行う

class InputNameScene {
	struct GraphData {
		GraphData();
		Animation anime;
		Point position;//描画座標
		int drawing_order;//描画する順番
		std::string name;
		//ソート用条件式----------------------------------------
		bool operator < (const GraphData& right)const {
			return this->drawing_order < right.drawing_order;
		}
		bool operator > (const GraphData& right)const {
			return this->drawing_order > right.drawing_order;
		}
	};
	//背景画像とテキストボックスの画像表示
	std::vector<GraphData> anime;
public:
	void initialize();
	void finalize();
	void update();
	void draw();
};