#pragma once
#include<SingletonObject.h>

const int DRAW_WAIT = 60;	// FPSの精度

class TimeManager : public SingletonObject {

public:
	static TimeManager* GetInstance();

	void Initialize()override;
	void Update()override;

	// フレーム間の時間測定開始
	void Start();

	// FPSを一定に保つために止めるコマンド(決して呼び出さないこと)
	void Wait();

	// これを呼ばれた時点で計算が開始する(ロードによるfps低下で最初のフレームの暴走防止)
	void Reset();

	// 今のFPSを返す
	float Getfps();

	// 今のデルタタイムを返す
	float GetDelta();

	// 西暦を返す
	int GetYaer() { return m_dateData.Year; }

	// 月を返す
	int GetMon() { return m_dateData.Mon; }

	// 日付を返す
	int GetDay() { return m_dateData.Day; }

	// 時刻を返す
	int GetHour() { return m_dateData.Hour; }

	// 分数を返す
	int GetMin() { return m_dateData.Min; }

	// 秒を返す
	int GetSec() { return m_dateData.Sec; }

private:
	TimeManager();
	~TimeManager();

	int m_timer;			// timer
	float m_fps;			// fps
	float m_delta;			// デルタタイム
	DATEDATA m_dateData;	// 現在時刻

	int m_count;		// 表示用カウンタ
	float m_drawFps;
	float m_drawDelta;
};
