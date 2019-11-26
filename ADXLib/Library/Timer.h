#pragma once

///<summary>
///	時間を計測するクラス
///	その関数の処理時間などを計測する場合に使える
///</summary>
class Timer {

public:
	Timer();
	virtual~Timer();
	
	// 初期時間をリセットする
	void Reset();

	// Startからの経過時間(秒)を返す
	float GetSecond();

private:
	int m_startTime;	// 測定開始時の時間


};
