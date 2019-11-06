#include "GameObjectManager.h"

GameObjectManager * GameObjectManager::GetInstance() {

	static GameObjectManager *inst = nullptr;

	if (inst == nullptr) {
		inst = new GameObjectManager();
	}
	return inst;
}

void GameObjectManager::Update() {

	for (auto it = m_objectList.begin(); it != m_objectList.end();) {

		// Initialize‚ð“Ç‚ñ‚Å‚¢‚È‚¢‚È‚ç
		if (!(*it)->IsInitialized()) {
			(*it)->Initialize();
			(*it)->UsedInitialize();
		}

		// íœ‚·‚é‚È‚ç
		if ((*it)->IsDead()) {
			delete (*it);
			it = m_objectList.erase(it);
			continue;
		}

		// Update‚ª–³Œø‚È‚ç
		if (!(*it)->IsEnable()) {
			continue;
		}

		(*it)->Update();
		it++;
	}
}

void GameObjectManager::PushUpdate(GameObject * obj) {

	m_objectList.push_back(obj);
}

GameObjectManager::GameObjectManager()
	:SingletonObject(this) {

}

GameObjectManager::~GameObjectManager() {

}
