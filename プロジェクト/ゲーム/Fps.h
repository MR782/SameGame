#pragma once

//FPSを固定する

class Fps {
	float fps;//FreamPerSecond
	int start_time;//測定開始時刻
	int count;//カウンタ
public:
	Fps();
	bool update();
	void wait();
};