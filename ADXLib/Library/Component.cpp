#include "Component.h"

#include<GameObject.h>
#include<Layer.h>
#include<ComponentManager/ComponentManager.h>

int Component::GetLayer() {

	if (m_body == nullptr)
		return (int)LAYER::NONE;

	return m_body->GetLayer();
}

void Component::SetLayer(int layer) {

	ComponentManager::GetInstance()->ChangeLayer(this, (LAYER)layer);
}
