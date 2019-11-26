#pragma once

class Random {

	// ランダム抽選した結果、当たったらtrueを返す(母数の数,当たりの数)
	static	bool GetHit(int all, int win = 1);

	// そのくじの当たる確率を求める。戻り値は1～0(母数の数,当たりの数)
	static	float GetProb(int all, int win = 1);

};
