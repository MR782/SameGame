#pragma once
#include"Animation.h"
#include"Purpose.h"

//ゲーム内オブジェクトの初期化処理

class Object {
protected:
	Rect hitBox;//当たり判定矩形
	Point position;//座標
	std::unique_ptr<Animation> anime;
public:
	Object();
	virtual void initialize() = 0;//初期化処理
	virtual void update() = 0;//更新処理
	virtual void draw();//描画処理

	Rect get_hitBox();//自身の当たり判定矩形を返す
};