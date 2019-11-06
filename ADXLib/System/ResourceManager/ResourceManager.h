#pragma once
#include<GameObject.h>
#include<Library.h>

/*������*/

///<summary>
///���[�h�����f�[�^���g���܂킷���߁A�ێ�����V���O���g��
///</summary>
class ResourceManager : public GameObject {

public:
	ResourceManager();
	~ResourceManager();

	static ResourceManager *GetInstance();

	// �摜�f�[�^�����[�h
	int LoadGraph(char *fileName);					

	// ���f���f�[�^�����[�h
	int LoadModel(char *fileName);

	// �T�E���h�f�[�^�����[�h
	int LoadSound(char *fileName);

private:
	struct RESOURCE_DATA {
		std::string name;	// �t�@�C����
		int originHandle;	// �I���W�i���̃n���h��
	};

	std::list<RESOURCE_DATA> m_graphList;
	std::list<RESOURCE_DATA> m_modelList;
	std::list<RESOURCE_DATA> m_soundList;

};
