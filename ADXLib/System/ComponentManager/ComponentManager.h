#pragma once
#include<SingletonObject.h>
#include<list>
#include<Component.h>
#include<Layer.h>

class ComponentManager : public SingletonObject {

public:
	static ComponentManager *GetInstance();

	void Update()override;
	void Draw()override;

	void PushUpdate(Component* comp);
	void PushDraw(Component* comp);

	void EraseUpdate(Component* comp);
	void EraseDraw(Component* comp);

	void ChangeLayer(Component* comp ,LAYER layer);

private:
	ComponentManager();
	~ComponentManager();

private:
	std::list<Component*> m_updateList;
	std::list<Component*> m_drawList[(int)LAYER::MAX];

};
