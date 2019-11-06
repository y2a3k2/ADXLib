#pragma once
#include"../SceneBase.h"

class Play : public SceneBase {

public:
	Play();
	~Play();
	void Initialize()override;
	void Update()override;
};

