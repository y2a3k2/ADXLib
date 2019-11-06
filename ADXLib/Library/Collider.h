#pragma once
#include<Component.h>
#include<GameObject.h>
#include<ComponentManager/ComponentManager.h>

class Collider : public Component {

public:
	// �����蔻��̌^
	enum class TYPE {
		DYNAMIC,	// �Փ˂���ƈړ�����
		KINEMATIC,	// �Փ˂��Ă����蔲����
		STATIC,		// �Փ˂��Ă��ړ����Ȃ�
	};

public:
	Collider() :Component() { ComponentManager::GetInstance()->PushUpdate(this); }
	Collider(GameObject *body) :Component(body) { ComponentManager::GetInstance()->PushUpdate(this); }
	virtual	~Collider() { ComponentManager::GetInstance()->EraseUpdate(this); }

	/* ����̌^��ύX���� */
	virtual void ChangeDynamic() { m_type = TYPE::DYNAMIC; }
	virtual void ChangeKinematic() { m_type = TYPE::KINEMATIC; }
	virtual void ChangeStatic() { m_type = TYPE::STATIC; }

	// �����̖{��
	GameObject *GetBody() { return m_body; }
	// ���̌^��Ԃ�
	TYPE GetType() { return m_type; }
	// �Փˎ��ɌĂ΂��
	void OnCollisionEnter(GameObject *target) { m_body->OnCollisionEnter(target); }

private:
	TYPE m_type;

};

class Collider2D : public Collider {

public:
	// �`��
	enum class SHAPE {
		NONE,
		BOX,		// �l�p�`
		CIRCLE,		// �~�`
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
	// �`��
	enum class SHAPE {
		NONE,
		CUBE,		// ������
		SPHERE,		// ����
		CAPSULE,	// �J�v�Z��
	};

public:
	Collider3D(GameObject*body, SHAPE shape) :Collider(body) { m_shape = shape; }
	virtual	~Collider3D() {};

	SHAPE GetShape() { return m_shape; }

private:
	SHAPE m_shape;

};
