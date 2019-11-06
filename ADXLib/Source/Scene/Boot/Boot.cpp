#include "Boot.h"
#include"../../../System/SceneManager/SceneManager.h"

Boot::Boot()
	: SceneBase("Boot") {
}

Boot::~Boot() {

}

void Boot::Initialize() {

	SceneManager::GetInstance()->Change(SCENE_ID::TITLE);
}

void Boot::Update() {

}
