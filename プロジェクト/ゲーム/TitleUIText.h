#pragma once
#include"Purpose.h"
#include"Animation.h"

class TitleUI {
	std::unique_ptr<Animation> anime;
public:
	void initialize();
	void finalize();
	void draw();
};