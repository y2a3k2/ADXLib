#include "Test2d.h"
#include"../../Player/Player.h"
#include"../../Enemy/Enemy.h"
#include<Library.h>
#include<SceneManager/SceneManager.h>
#include<ResourceManager/ResourceManager.h>

namespace {
	Player *player;
	Enemy *enemy;
}

Test2d::Test2d()
	:SceneBase("Test2d") {

	player = CreateObject<Player>();
	enemy = CreateObject<Enemy>();

	m_bgm = AddComponent<Sound>();
	m_bgm->Load("data\\sound\\battleBGM.mp3");

	m_bg = AddComponent<Sprite>();
	m_bg->Load("data\\texture\\bg.png", true);
	m_bg->SetPosition(VGet(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0));
	m_bg->SetScale(1.0f);

	m_icon = AddComponent <Sprite>();
	m_icon->Load("data\\texture\\loading.png", true);
	m_icon->SetPosition(VGet(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0));
	m_icon->SetScale(0.5f);

	m_timer = 0;
	SetLayer((int)LAYER::UI);
}

Test2d::~Test2d() {

}

void Test2d::Initialize() {

	SceneBase::Initialize();
}

void Test2d::Update() {

	m_timer += GetTime()->GetDelta();

	if (GetInput()->GetKeyDown(KEY_INPUT_Q)) {
		m_bgm->SetVolume(0.5f);
		m_bgm->LoopPlay();
	}

	if (ResourceManager::GetInstance()->IsCoroutine()) {
		float t = m_timer * (360.0f * 3);
		float s = cosf(GetRadian((int)t));
		float y = (WINDOW_HEIGHT / 2) + (s * 10.0f);
		m_icon->SetPosition(VGet(WINDOW_WIDTH / 2, y, 0));
	}
	// ”ñ•\Ž¦‚É‚·‚é
	else {
		m_bg->SetDisable();
		m_icon->SetDisable();
	}
}
