#pragma once
#include<string>

class GameObject;
class Component {

public:
	Component() { m_enable = true; };
	Component(GameObject *body) { m_enable = true, m_body = body; }
	virtual ~Component() {};

	virtual void Awake() {};
	virtual void Update() {};
	virtual void Draw() {};

	// �L���Ȃ�true
	bool IsEnable() { return m_enable; }

	// �L���ɂ���
	bool SetEnable() { m_enable = true; }

	// �����ɂ���
	bool SetDisable() { m_enable = false; }

	// �{�̂̃��C���[��Ԃ�
	int GetLayer();

	// ���C���[(�`�ʏ�)��ς���
	void SetLayer(int layer);

protected:
	GameObject* m_body;	// �A�^�b�`���Ă���{��

private:
	bool m_enable;		// ���̃R���|�[�l���g���L�����ǂ���

};
