#pragma once
#include<DxLib.h>
#include<list>

#include<Transform.h>
#include<Component.h>

#include<DebugManager/DebugManager.h>
#include<InputManager/InputManager.h>
#include<TimeManager/TimeManager.h>

class GameObject {

public:
	GameObject();
	GameObject(std::string name);
	virtual ~GameObject();

	// ������(�񐄏�)	�R���X�g���N�^�̌�ɌĂ΂��@CreateObject<T>()��GameObject()��Awake()�̏�
	virtual void Awake() {}
	// ������	����Update�ŌĂ΂��
	virtual void Initialize() {}
	// �X�V		�\���O�ɖ��t���[���Ă΂��
	virtual void Update() {}

	// �Փˎ��ɌĂ΂��֐�	�����ɂ͏Փ˂����I�u�W�F�N�g������(�����蔻�肻�̂��̂ł͂Ȃ�)
	virtual void OnCollisionEnter(GameObject *object) {}

	// Initialize���Ă΂�Ă���Ȃ�true
	virtual bool IsInitialized() { return m_state.initialized; }
	// Initialize���Ă΂ꂽ
	virtual void UsedInitialize() { m_state.initialized = true; }
	// Update�������邩
	virtual bool IsEnable() { return m_state.enable; }
	// Update��L���ɂ���
	virtual void SetEnable() { m_state.enable = true; }
	// Update�𖳌��ɂ���
	virtual void SetDisable() { m_state.enable = false; }
	// �����Ȃ�true
	bool IsDead() { return m_state.dead; }

	// �I�u�W�F�N�g�̖��O��Ԃ�
	std::string GetName() { return m_objectName; };
	// �e�̃|�C���^��Ԃ�
	GameObject *GetParent() { return m_parent; };
	// �q�I�u�W�F�N�g�̃��X�g��Ԃ�
	std::list<GameObject*> &GetChildList() { return m_childList; };
	// �I�u�W�F�N�g�̃^�O��Ԃ�
	int GetTag() { return m_state.tag; }
	// �����̈ʒu�A��]�A�g�k�̃p�����[�^�[��Ԃ�
	Transform &GetTransform() { return m_transform; }
	// ���C���[��Ԃ�
	int GetLayer() { return m_state.layer; };

	// �I�u�W�F�N�g�̖��O��ύX����
	void SetName(const char *name) { m_objectName = name; }
	// �I�u�W�F�N�g�̃^�O������
	void SetTag(int tag) { m_state.tag = tag; }
	// ���C���[��ύX����
	void SetLayer(int layer);

	// ���g�̎q�ɐV�����I�u�W�F�N�g�𐶐�����
	template <typename T> T *CreateObject() {
		auto t = new T();
		((GameObject*)t)->m_parent = this;
		m_childList.push_back(t);
		t->Awake();
		return t;
	}

	// �V�����R���|�[�l���g��ǉ�����
	template <typename T> T *AddComponent() {
		auto t = new T(this);
		m_componentList.push_back(t);
		t->Awake();
		return t;
	}
	// �R���|�[�l���g���폜����
	template <typename T> void SubComponent() {
		for (auto it = m_componentList.begin(); it != m_componentList.end(); it++) {
			// �w�肳�ꂽ���̂Ɠ����^�Ȃ�Ԃ�
			auto p = dynamic_cast<T*>((*it));
			if (p != nullptr) {
				return p;
			}
		}
	}
	// �R���|�\�����g����������
	template <typename T> T* GetComponent() {
		for (auto it = m_componentList.begin(); it != m_componentList.end(); it++) {
			// �w�肳�ꂽ���̂Ɠ����^�Ȃ�Ԃ�
			auto p = dynamic_cast<T*>((*it));
			if (p != nullptr) {
				return p;
			}
		}
		// �Ȃ����null��Ԃ�
		return nullptr;
	}

	// �q�I�u�W�F�N�g������
	GameObject* Search(std::string name) {
		for (auto it = m_childList.begin(); it != m_childList.end(); it++) {
			if ((*it)->m_objectName == name) {
				return (*it);
			}
			auto p = (*it)->Search(name);
			if (p != nullptr) {
				return p;
			}
		}
		return nullptr;
	};

	// ���O�Ŏw�肵���q�I�u�W�F�N�g������
	void ChildDestroy(std::string name) {
		auto obj = Search(name);
		if (obj != nullptr)
			delete obj;
	}

	// �e��ʃI�u�W�F�N�g�ɕς���
	void SetParent(GameObject *parent) {
		auto par = GetParent();
		// �e������Ȃ��ɐe�̎q���X�g����O���
		if (par != nullptr) {
			auto list = par->GetChildList();
			for (auto it = list.begin(); it != list.end(); it++) {
				// ������P��
				if ((*it) == this) {
					list.erase(it);
					break;
				}
			}
		}
		// �e����(��ԏ�)�ɂȂ�Ȃ�root�̎q�ɂ���
		if (parent == nullptr) {
			m_parent = GetRoot();
			GetRoot()->GetChildList().push_back(this);
		}

		else {
			m_parent = parent;
			parent->GetChildList().push_back(this);
		}
	}

	// ��ԏ�̊K�w
	static GameObject *GetRoot();
	// ���͊֌W
	static InputManager *GetInput();
	// �f�o�b�N�֌W
	static DebugManager *GetDebug();
	// ���Ԋ֌W
	static TimeManager *GetTime();

	// �I�u�W�F�N�g��R���|�[�l���g����������
	void Destroy() { m_state.dead = true; };
	void Destroy(Component* comp);

protected:
	struct STATE {
		STATE() { ZeroMemory(this, sizeof(this)); }
		unsigned initialized : 1;	// true�Ȃ珉�����ς�
		unsigned dead : 1;			// true�Ȃ����
		unsigned enable : 1;		// true����Ȃ���Γ������Ȃ�
		int layer;					// �`�ʏ�(���l�̒Ⴂ���̂���`��)
		int tag;					// �I�u�W�F�N�g�̃^�O
	};

private:
	GameObject* m_parent;
	STATE m_state;
	Transform m_transform;
	std::string m_objectName;
	std::list<GameObject*> m_childList;
	std::list<Component*> m_componentList;

};
