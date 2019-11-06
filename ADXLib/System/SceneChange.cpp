#include <assert.h>
#include<GameObject.h>
#include<SceneManager/SceneManager.h>

/* それぞれのシーンをincludeする */
#include"../Source/Scene/Boot/Boot.h"
#include"../Source/Scene/Title/Title.h"
#include"../Source/Scene/Play/Play.h"
#include"../Source/Scene/Result/Result.h"
#include"../Source/Scene/Test/Test.h"

// どのシーンから開始するかをここで変更できる
void SceneManager::StartScene() {

	m_nextScene = SCENE_ID::TEST;
}

// シーン切り替え処理
void SceneManager::SceneChangeProcess() {

	// 中身があるなら
	if (m_scene != nullptr) {
		m_scene->Destroy();
	}

	auto next = SceneManager::GetInstance()->GetNextScene();

	switch (next) {

		/* シーンを増やすたびに追加する */
	case SCENE_ID::TITLE:	m_scene = GameObject::GetRoot()->CreateObject<Title>();		break;
	case SCENE_ID::PLAY:	m_scene = GameObject::GetRoot()->CreateObject<Play>();		break;
	case SCENE_ID::RESULT:	m_scene = GameObject::GetRoot()->CreateObject<Result>();	break;
	case SCENE_ID::TEST:	m_scene = GameObject::GetRoot()->CreateObject<Test>();		break;

		// 何も呼ばれなかった場合は止める
	default:				assert(false);							break;

	}
	m_nowScene = next;
	m_nextScene = SCENE_ID::NONE;
}
