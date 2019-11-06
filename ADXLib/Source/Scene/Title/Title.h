#pragma once
#include"../SceneBase.h"

class Title : public SceneBase {

public:
	Title();
	~Title();
	void Initialize()override;
	void Update()override;
};
