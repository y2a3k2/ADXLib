#include "TimeManager.h"
#include<Config.h>
#include"DebugManager/DebugManager.h"

TimeManager * TimeManager::GetInstance() {

	static TimeManager *inst = nullptr;

	if (inst == nullptr) {
		inst = new TimeManager();
	}
	return inst;
}

void TimeManager::Initialize() {

	m_fps = (float)FPS_RATE;
	m_timer = GetNowCount();
	m_delta = (1.0f / m_fps);
	m_count = 0;
	GetDateTime(&m_dateData);

	m_drawFps = m_fps;
	m_drawDelta = m_delta;
}

void TimeManager::Update() {

#if DEBUG
	m_drawFps += m_fps;
	m_drawDelta += m_delta;

	if (m_count >= DRAW_WAIT) {
		m_drawFps = m_drawFps / DRAW_WAIT;
		m_drawDelta = m_drawDelta / DRAW_WAIT;
		m_count = 0;
	}
	m_count++;

	DebugManager::GetInstance()->SetLog("FPS %0.3f,DELTA %0.3f", m_drawFps / m_count, m_drawDelta / m_count);
	DebugManager::GetInstance()->SetLog("%d %d/%d %d:%d:%d",GetYaer(), GetMon(), GetDay(),GetHour(),GetMin(),GetSec());

#endif
}

void TimeManager::Start() {

	m_timer = GetNowCount();
	GetDateTime(&m_dateData);
}

void TimeManager::Wait() {

	// 経過時間(ミリ秒)
	auto GetTook = [](int timer) {
		return GetNowCount() - timer;
	};

	int waitTime = (1000 / FPS_RATE) - GetTook(m_timer);	// 待機する時間(理想の経過時間 - 実際の経過時間)

	// 待つ必要があるなら
	if (waitTime > 0) {
		Sleep(waitTime);
	}

	float elapsed = max((float)GetTook(m_timer), 1.0f);	// 上限値を設ける
	m_fps = 1000.0f / elapsed;							// 今のFPSを算出
	m_delta = elapsed / 1000.0f;						// デルタタイムを算出
}

void TimeManager::Reset() {

	Initialize();
}

float TimeManager::Getfps() {

	return m_fps;
}

float TimeManager::GetDelta() {

	return m_delta;
}

TimeManager::TimeManager()
	:SingletonObject(this) {
}

TimeManager::~TimeManager() {

}
