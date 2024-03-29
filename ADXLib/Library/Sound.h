#pragma once
#include<Component.h>

// すべての音量を平等に下げる
const float ALL_VOLUME = 1.0f;

class Sound : public Component {

public:
	Sound();
	Sound(GameObject *body);
	virtual	~Sound();
	virtual void Load(const char* fileName);

	// 音を再生する(停止中なら途中から)
	virtual void Play();
	// 音を最初から再生する
	virtual void Replay();
	// 音をループさせる
	virtual void LoopPlay();
	// 音の再生を止める
	virtual void Stop();

	// 音量を変える(0〜1)
	void SetVolume(float volume);

protected:
	void Unload();

protected:
	int m_handle;

};
