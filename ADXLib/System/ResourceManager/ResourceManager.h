#pragma once
#include<SingletonObject.h>
#include<string>
#include<list>

///<summary>
///	���[�h�����f�[�^�������I�Ɏg���񂷂��߂̃V�X�e��
///</summary>
class ResourceManager : public SingletonObject {

public:
	static ResourceManager *GetInstance();

	void Update()override;

	// �摜�f�[�^�����[�h(�R���[�`��)
	void PushLoadGraph(const char *fileName);
	// ���f���f�[�^�����[�h(�R���[�`��)
	void PushLoadModel(const char *fileName);
	// �T�E���h�f�[�^�����[�h(�R���[�`��)
	void PushLoadSound(const char *fileName);

	// �摜�f�[�^�����[�h
	int LoadGraph(const char *fileName);
	// ���f���f�[�^�����[�h
	int LoadModel(const char *fileName);
	// �T�E���h�f�[�^�����[�h
	int LoadSound(const char *fileName);

	// �摜�f�[�^�̃n���h�������炤
	int GetGraphHandle(const char *fileName);
	// ���f���f�[�^�̃n���h�������炤
	int GetModelHandle(const char *fileName);
	// �T�E���h�f�[�^�̃n���h�������炤
	int GetSoundHandle(const char *fileName);

	// �摜�f�[�^�̃n���h��������
	void DeleteGraphHandle(const char *fileName);
	// ���f���f�[�^�̃n���h��������
	void DeleteModelHandle(const char *fileName);
	// �T�E���h�f�[�^�̃n���h��������
	void DeleteSoundHandle(const char *fileName);

	// �R���[�`���Ń��[�h�����Ă��邩
	bool IsCoroutine();
	//���[�h��������Ԃ�
	float GetLoadPercent();

private:
	// ���\�[�X���
	struct RESOURCE_DATA {
		RESOURCE_DATA() { name = "", handle = -1, copyCount = 0; };
		RESOURCE_DATA(std::string n, int h) { name = n, handle = h, copyCount = 0; };
		std::string name;	// �t�@�C����
		int handle;			// �I���W�i���̃n���h��
		int copyCount;		// �R�s�[�̐�
	};

	// ���\�[�X�敪
	enum RESOURCE_TYPE {
		GRAPH, MODEL, SOUND, MAX,
	};

	struct LOAD_DATA {
		LOAD_DATA() {};
		LOAD_DATA(std::string n, RESOURCE_TYPE t) { name = n, type = t; }
		std::string name;		// �t�@�C����
		RESOURCE_TYPE type;		// �敪
	};

	ResourceManager();
	~ResourceManager();

	// ���[�h�ς݂Ȃ�true��Ԃ�
	bool IsLoaded(std::list<RESOURCE_DATA> &list, const char* name);
	// ���[�h���Ȃ�true��Ԃ�
	bool IsLoading(const char* name);

private:
	int m_loadCount;	// �������[�h����̂�
	std::list<LOAD_DATA> m_loadList;
	std::list<RESOURCE_DATA> m_resourceList[RESOURCE_TYPE::MAX];

};
