#pragma once
#include"Animation.h"
#include<memory>
#include"TitleUIText.h"

//ƒ^ƒCƒgƒ‹‰æ–Ê

class TitleScene {
	TitleUI title_ui;
	int back_graph;
public:
	void initialize();
	void finalize();
	void update();
	void draw();
};