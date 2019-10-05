#include "Fps.h"
#include"DxLib.h"

Fps::Fps()
{
	start_time = 0;
	count = 0;
	fps = 0;
}

bool Fps::update()
{
	const int N = 10;//平均とる数(10フレームに１回FPSを測る)
	//1フレーム目なら時刻を記憶
	if (count == 0) { 
		start_time = GetNowCount();
	}
	//特定のフレーム目なら平均を計算
	if (count == N) {
		int time = GetNowCount();//現在の時間を計測
		fps = 1000.0f / ((time - start_time) / (float)N);
		count = 0;//カウンター初期化
		start_time = time;//開始時間に代入次の測定に備える
	}
	count++;
	//FPS測定
	//DrawFormatString(0, 100, GetColor(0, 255, 255), "count : %d", count);
	//DrawFormatString(0, 0, GetColor(0, 255, 255), "FPS : %.5f", fps);
	return true;
}

void Fps::wait()
{
	const int FPS = 60;//設定したFPS
	int took_time = GetNowCount() - start_time;//掛かった時間
	int wait_time = count * 1000 / FPS - took_time;//待つべき時間
	if (wait_time > 0) {
		Sleep(wait_time);//待機
	}
}
