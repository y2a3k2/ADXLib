#pragma once
#include<Component.h>

// ‚·‚×‚Ä‚Ì‰¹—Ê‚ğ•½“™‚É‰º‚°‚é
const float ALL_VOLUME = 1.0f;

class Sound : public Component {

public:
	Sound();
	Sound(GameObject *body);
	virtual ~Sound();

	virtual void Update()override;
	virtual void Load(const char* fileName, bool quickly = false);

	// ‰¹‚ğÄ¶‚·‚é(’â~’†‚È‚ç“r’†‚©‚ç)
	virtual void Play();
	// ‰¹‚ğÅ‰‚©‚çÄ¶‚·‚é
	virtual void Replay();
	// ‰¹‚ğƒ‹[ƒv‚³‚¹‚é
	virtual void LoopPlay();
	// ‰¹‚ÌÄ¶‚ğ~‚ß‚é
	virtual void Stop();

	// ‰¹—Ê‚ğ•Ï‚¦‚é(0`1)
	void SetVolume(float volume);

protected:
	void Unload();

	enum STATE {
		NONE,
		PLAY,
		REPLAY,
		LOOP,
	};

protected:
	float m_initVolume;
	int m_handle;
	std::string m_fileName;
	STATE m_state;
};
