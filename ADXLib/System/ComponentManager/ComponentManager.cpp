#include "ComponentManager.h"

ComponentManager * ComponentManager::GetInstance() {

	static ComponentManager* inst = nullptr;

	if (inst == nullptr) {
		inst = new ComponentManager();
	}

	return inst;
}

void ComponentManager::Update() {

	for each (auto comp in m_updateList) {
		// 無効なら飛ばす
		if (!comp->IsEnable())
			continue;
		comp->Update();
	}
}

void ComponentManager::Draw() {

	for (int i = 0; i < (int)LAYER::MAX; i++) {
		for each (auto comp in m_drawList[i]) {
			// 無効なら飛ばす
			if (!comp->IsEnable())
				continue;
			comp->Draw();
		}
	}
}

void ComponentManager::PushUpdate(Component * comp) {

	m_updateList.push_back(comp);
}

void ComponentManager::PushDraw(Component * comp) {

	int layer = comp->GetLayer();
	m_drawList[layer].push_back(comp);
}

void ComponentManager::EraseUpdate(Component * comp) {

	for (auto it = m_updateList.begin(); it != m_updateList.end(); it++) {
		if ((*it) == comp) {
			m_updateList.erase(it);
			return;
		}
	}
}

void ComponentManager::EraseDraw(Component * comp) {

	for (int i = 0; i < (int)LAYER::MAX; i++) {
		for (auto it = m_drawList[i].begin(); it != m_drawList[i].end(); it++) {
			// そのコンポ―メントを見つけたら
			if ((*it) == comp) {
				m_drawList[i].erase(it);
				return;
			}
		}
	}
}

void ComponentManager::ChangeLayer(Component * comp, LAYER layer) {

	for (int i = 0; i < (int)LAYER::MAX; i++) {
		for (auto it = m_drawList[i].begin(); it != m_drawList[i].end(); it++) {
			// そのコンポ―メントを見つけたら
			if ((*it) == comp) {
				// 今のリストから省いて、そのレイヤーのリストに再登録
				m_drawList[i].erase(it);
				m_drawList[(int)layer].push_back(comp);
				return;
			}
		}
	}
}

ComponentManager::ComponentManager()
	:SingletonObject(this) {

}

ComponentManager::~ComponentManager() {

}
