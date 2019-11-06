#include "SceneManager.h"
#include<Config.h>

SceneManager * SceneManager::GetInstance() {

	static SceneManager *inst = nullptr;

	if (inst == nullptr) {
		inst = new SceneManager();
	}
	return inst;
}

void SceneManager::Initialize() {

}

void SceneManager::Update() {

	if (m_nextScene != SCENE_ID::NONE) {
		SceneChangeProcess();
	}
}

void SceneManager::Change(SCENE_ID scene) {

	// Boot‚©None‚ÉˆÚ‚ë‚¤‚Æ‚µ‚Ä‚¢‚½‚ç‚±‚±‚Å‹‘”Û‚·‚é
	if (scene == SCENE_ID::BOOT || scene == SCENE_ID::NONE)
		return;
	m_nextScene = scene;
}

SCENE_ID SceneManager::GetNextScene() {

	return m_nextScene;
}

SceneManager::SceneManager()
	:SingletonObject(this) {

	m_scene = nullptr;
	m_nowScene = SCENE_ID::NONE;
	m_nextScene = SCENE_ID::NONE;
	StartScene();
}

SceneManager::~SceneManager() {

}
