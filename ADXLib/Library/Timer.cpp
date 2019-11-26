#include "Timer.h"
#include<DxLib.h>

Timer::Timer() {

	m_startTime = GetNowCount();
}

Timer::~Timer() {

}

void Timer::Reset() {

	m_startTime = GetNowCount();
}

float Timer::GetSecond() {

	// 経過時間(ミリ秒)
	auto GetTook = [](int timer) {
		return GetNowCount() - timer;
	};
	float elapsed = max((float)GetTook(m_startTime), 1.0f);	// 上限値を設ける
	return elapsed / 1000.0f;								// ミリ秒を秒に変換
}

