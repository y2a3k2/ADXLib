#include "Test.h"
#include"../../Player/Player.h"
#include"../../Enemy/Enemy.h"
#include<Library.h>
#include<SceneManager/SceneManager.h>

namespace {

	Player *player;
	Enemy *enemy;
}

Test::Test()
	:SceneBase("Test") {

	player = CreateObject<Player>();
	enemy = CreateObject<Enemy>();

	m_bgm = AddComponent<Sound>();
	m_bgm->Load("data\\sound\\battleBGM.mp3");
}

Test::~Test() {

}

void Test::Initialize() {

	SceneBase::Initialize();
}

void Test::Update() {

	if (GetInput()->GetKeyDown(KEY_INPUT_Q)) {
		m_bgm->SetVolume(0.5f);
		m_bgm->LoopPlay();
	}
}
