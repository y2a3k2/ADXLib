#pragma once
#include"SingletonObject.h"
#include"GameObject.h"

class GameObjectManager : public SingletonObject{

public:
	static GameObjectManager *GetInstance();

	void Update()override;

	// オブジェクトをリストに登録する
	void PushUpdate(GameObject* obj);

private:
	GameObjectManager();
	~GameObjectManager();

private:
	std::list<GameObject*> m_objectList;

};
