#pragma once
#include <memory>
#include "Resource.h"
#include"Purpose.h"

//アニメーションを行う

class Animation {
private:
	//friend class CoreScene;
	std::shared_ptr<GraphicObject> object;
	int current_anime;//何枚目にいるか
	int current_rate;

	void switch_anime();
public:
	Animation();
	~Animation();
	void draw_anime(Point);
	void set(std::string);
};