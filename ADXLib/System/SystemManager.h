#pragma once
#include<vector>
#include<SingletonObject.h>

#define SystemInstance SystemManager::GetInstance()

class GameObject;

class SystemManager :public SingletonObject {

public:
	static SystemManager *GetInstance();

	void Initialize();
	void FirstUpdate();
	void Update();
	void LastUpdate();
	void Draw();
	void Release();

	// �V���O���g���𐶐������ۂɌĂяo���A���̒��ɓ����
	void Push(SingletonObject *singleton);

private:
	SystemManager();
	~SystemManager();

private:
	std::vector<SingletonObject*> m_childList;


};
