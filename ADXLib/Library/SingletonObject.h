#pragma once
#include<DxLib.h>

class SingletonObject {

public:
	virtual void Initialize() {};
	virtual void FirstUpdate() {};
	virtual void Update() {};
	virtual void LastUpdate() {};
	virtual	void Draw() {};
	virtual	void Release() {};

	virtual bool IsInitialized() { return m_initialized; }
	virtual void UsedInitialize() { m_initialized = true; };

protected:
	SingletonObject();
	SingletonObject(SingletonObject *singleton);
	virtual ~SingletonObject();

private:
	unsigned m_initialized : 1;	// trueÇ»ÇÁèâä˙âªçœÇ›
};
