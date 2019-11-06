#pragma once
#include"../SceneBase.h"

class Sound;

class Test : public SceneBase {

public:
	Test();
	~Test();
	void Initialize()override;
	void Update()override;

private:
	Sound *m_bgm;

};
