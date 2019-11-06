#pragma once
#include"../SceneBase.h"

class Boot : public SceneBase {

public:
	Boot();
	~Boot();
	void Initialize()override;
	void Update()override;
};
