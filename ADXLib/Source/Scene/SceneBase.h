#pragma once
#include"../../Library/GameObject.h"

class SceneBase : public GameObject {

public:
	SceneBase(std::string name) :GameObject(name) {};
	virtual ~SceneBase() {};
	virtual void Initialize() override { GetTime()->Reset(); };
};
