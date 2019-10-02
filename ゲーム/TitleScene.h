#pragma once
#include"Animation.h"
#include<memory>
#include"TitleUIText.h"

//タイトル画面

class TitleScene {
	std::unique_ptr<Animation> anime;
	TitleUI title_ui;
public:
	void initialize();
	void finalize();
	void update();
	void draw();
};