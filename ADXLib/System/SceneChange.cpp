#include <assert.h>
#include<GameObject.h>
#include<SceneManager/SceneManager.h>

/* ���ꂼ��̃V�[����include���� */
#include"../Source/Scene/Boot/Boot.h"
#include"../Source/Scene/Title/Title.h"
#include"../Source/Scene/Play/Play.h"
#include"../Source/Scene/Result/Result.h"
#include"../Source/Scene/Test/Test.h"

// �ǂ̃V�[������J�n���邩�������ŕύX�ł���
void SceneManager::StartScene() {

	m_nextScene = SCENE_ID::TEST;
}

// �V�[���؂�ւ�����
void SceneManager::SceneChangeProcess() {

	// ���g������Ȃ�
	if (m_scene != nullptr) {
		m_scene->Destroy();
	}

	auto next = SceneManager::GetInstance()->GetNextScene();

	switch (next) {

		/* �V�[���𑝂₷���тɒǉ����� */
	case SCENE_ID::TITLE:	m_scene = GameObject::GetRoot()->CreateObject<Title>();		break;
	case SCENE_ID::PLAY:	m_scene = GameObject::GetRoot()->CreateObject<Play>();		break;
	case SCENE_ID::RESULT:	m_scene = GameObject::GetRoot()->CreateObject<Result>();	break;
	case SCENE_ID::TEST:	m_scene = GameObject::GetRoot()->CreateObject<Test>();		break;

		// �����Ă΂�Ȃ������ꍇ�͎~�߂�
	default:				assert(false);							break;

	}
	m_nowScene = next;
	m_nextScene = SCENE_ID::NONE;
}
