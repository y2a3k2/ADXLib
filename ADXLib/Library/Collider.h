#pragma once
#include<Component.h>
#include<GameObject.h>
#include<ComponentManager/ComponentManager.h>

class Collider : public Component {

public:
	// 当たり判定の型
	enum class TYPE {
		DYNAMIC,	// 衝突すると移動する
		KINEMATIC,	// 衝突してもすり抜ける
		STATIC,		// 衝突しても移動しない
	};

public:
	Collider() :Component() { ComponentManager::GetInstance()->PushUpdate(this); }
	Collider(GameObject *body) :Component(body) { ComponentManager::GetInstance()->PushUpdate(this); }
	virtual	~Collider() { ComponentManager::GetInstance()->EraseUpdate(this); }

	/* 判定の型を変更する */
	virtual void ChangeDynamic() { m_type = TYPE::DYNAMIC; }
	virtual void ChangeKinematic() { m_type = TYPE::KINEMATIC; }
	virtual void ChangeStatic() { m_type = TYPE::STATIC; }

	// 自分の本体
	GameObject *GetBody() { return m_body; }
	// 今の型を返す
	TYPE GetType() { return m_type; }
	// 衝突時に呼ばれる
	void OnCollisionEnter(GameObject *target) { m_body->OnCollisionEnter(target); }

private:
	TYPE m_type;

};

class Collider2D : public Collider {

public:
	// 形状
	enum class SHAPE {
		NONE,
		BOX,		// 四角形
		CIRCLE,		// 円形
	};

public:
	Collider2D(GameObject*body, SHAPE shape) :Collider(body) { m_shape = shape; };
	virtual	~Collider2D() {};

	SHAPE GetShape() { return m_shape; }

private:
	SHAPE m_shape;
};

class Collider3D : public Collider {

public:
	// 形状
	enum class SHAPE {
		NONE,
		CUBE,		// 立方体
		SPHERE,		// 球体
		CAPSULE,	// カプセル
	};

public:
	Collider3D(GameObject*body, SHAPE shape) :Collider(body) { m_shape = shape; }
	virtual	~Collider3D() {};

	SHAPE GetShape() { return m_shape; }

private:
	SHAPE m_shape;

};
