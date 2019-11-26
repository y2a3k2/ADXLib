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

	// Œo‰ßŠÔ(ƒ~ƒŠ•b)
	auto GetTook = [](int timer) {
		return GetNowCount() - timer;
	};
	float elapsed = max((float)GetTook(m_startTime), 1.0f);	// ãŒÀ’l‚ğİ‚¯‚é
	return elapsed / 1000.0f;								// ƒ~ƒŠ•b‚ğ•b‚É•ÏŠ·
}

