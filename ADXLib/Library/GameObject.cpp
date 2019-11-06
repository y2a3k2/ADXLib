#include "GameObject.h"

#include<Layer.h>
#include<Tag.h>
#include<GameObjectManager/GameObjectManager.h>

namespace {
	GameObject *root = nullptr;
	InputManager *input = nullptr;
	TimeManager *time = nullptr;
	DebugManager *debug = nullptr;
}

GameObject::GameObject() {

	m_state.enable = 1;
	m_transform = Transform(this);
	GameObjectManager::GetInstance()->PushUpdate(this);
}

GameObject::GameObject(std::string name) {

	m_state.enable = 1;
	m_objectName = name.c_str();
	m_transform = Transform(this);
	GameObjectManager::GetInstance()->PushUpdate(this);
}

GameObject::~GameObject() {

	// 親がいるなら親のリストから自分を破棄する
	if (m_parent != nullptr) {
		auto &pList = GetParent()->m_childList;
		for (auto it = pList.begin(); it != pList.end(); it++) {
			if (this == (*it)) {
				pList.erase(it);
				break;
			}
		}
	}

	// 子をすべて破棄
	for (auto it = m_childList.begin(); it != m_childList.end(); it++) {
		(*it)->m_parent = nullptr;
		(*it)->Destroy();
	}

	// コンポ―メントをすべて破棄
	for (auto it = m_componentList.begin(); it != m_componentList.end(); it++) {
		delete (*it);
	}
}

void GameObject::SetLayer(int layer) {

	int la = layer;

	if (layer < 0)
		la = 0;

	if (layer >= (int)LAYER::MAX)
		la = (int)LAYER::MAX - 1;

	m_state.layer = la;

	for each (auto comp in m_componentList) {
		comp->SetLayer(la);
	}
}

GameObject *GameObject::GetRoot() {

	if (root == nullptr) {
		root = new GameObject("Root");
		root->m_parent = nullptr;
		input = InputManager::GetInstance();
		time = TimeManager::GetInstance();
		debug = DebugManager::GetInstance();
	}
	return root;
}

InputManager * GameObject::GetInput() {

	return input;
}

DebugManager * GameObject::GetDebug() {

	return debug;
}

TimeManager * GameObject::GetTime() {

	return time;
}

void GameObject::Destroy(Component * comp) {

	for (auto it = m_componentList.begin(); it != m_componentList.end(); it++) {
		if ((*it) == comp) {
			delete (*it);
			m_componentList.erase(it);
			return;
		}
	}
}
