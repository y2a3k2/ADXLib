#pragma once
#include"../SceneBase.h"

class Sound;
class Sprite;

class Test2d : public SceneBase {

public:
	Test2d();
	~Test2d();
	void Initialize()override;
	void Update()override;

private:
	float m_timer;

	Sound * m_bgm;
	Sprite* m_bg;
	Sprite* m_icon;
};
