#include "SystemManager.h"
#include<GameObject.h>

#include"InputManager\InputManager.h"
#include"TimeManager/TimeManager.h"
#include"ColliderManager/ColliderManager.h"
#include"ComponentManager/ComponentManager.h"
#include"SceneManager/SceneManager.h"
#include"ResourceManager/ResourceManager.h"
#include"DebugManager/DebugManager.h"
#include"GameObjectManager/GameObjectManager.h"

SystemManager * SystemManager::GetInstance() {

	static SystemManager *inst = nullptr;

	if (inst == nullptr) {
		inst = new SystemManager();
	}
	return inst;
}

void SystemManager::Initialize() {

	/* ‚±‚ÌŽž“_‚Å¶¬‚µ‚Ä‚¨‚­ */
	InputManager::GetInstance();
	TimeManager::GetInstance();
	ColliderManager::GetInstance();
	ComponentManager::GetInstance();
	SceneManager::GetInstance();
	ResourceManager::GetInstance();
	DebugManager::GetInstance();
	GameObjectManager::GetInstance();
	GameObject::GetRoot();
}

void SystemManager::FirstUpdate() {

	for each (const auto &cl in m_childList) {
		// ‰Šú‰»‚µ‚Ä‚¢‚È‚¯‚ê‚Î
		if (!cl->IsInitialized()) {
			cl->Initialize();
			cl->UsedInitialize();
		}
		cl->FirstUpdate();
	}
}

void SystemManager::Update() {

	for each (const auto &cl in m_childList) {
		// ‰Šú‰»‚µ‚Ä‚¢‚È‚¯‚ê‚Î
		if (!cl->IsInitialized()) {
			cl->Initialize();
			cl->UsedInitialize();
		}
		cl->Update();
	}
}

void SystemManager::LastUpdate() {

	for each (const auto &cl in m_childList) {
		// ‰Šú‰»‚µ‚Ä‚¢‚È‚¯‚ê‚Î
		if (!cl->IsInitialized()) {
			cl->Initialize();
			cl->UsedInitialize();
		}
		cl->LastUpdate();
	}
}

void SystemManager::Draw() {

	for each (const auto &cl in m_childList) {
		cl->Draw();
	}
}

void SystemManager::Release() {

}

void SystemManager::Push(SingletonObject * singleton) {

	m_childList.push_back(singleton);
}

SystemManager::SystemManager()
	:SingletonObject() {

}

SystemManager::~SystemManager() {

}
