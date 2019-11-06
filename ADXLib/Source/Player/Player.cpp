#include"Player.h"
#include<Library.h>
#include<SceneManager/SceneManager.h>

Player::Player()
	:GameObject("Player") {

	/* 画像 */
	auto spr = AddComponent<Sprite>();
	spr->Load("data\\texture\\solvalou.png");
	spr->SetRect(0, 0, 32, 32);

	/* 音 */
	m_se = AddComponent<Sound>();
	m_se->Load("data\\sound\\fire1.mp3");

	auto col = AddComponent<CircleCollider>();
}

Player::~Player() {

}

void Player::Initialize() {

	auto parent = GetParent();
	m_bulletManager = parent->Search("BulletManager");

	// 位置の初期化(画面の真ん中へ)
	GetTransform().SetPosition(VGet(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0));

	SetLayer((int)LAYER::UI);
}

void Player::Update() {

	const float SPEED = MOVE_SPEED * GetTime()->GetDelta();
	VECTOR vec = VGet(0, 0, 0);
	auto input = GetInput();

	if (input->GetKey(KEY_INPUT_LEFT)) {
		vec.x = -SPEED;
	}
	if (input->GetKey(KEY_INPUT_RIGHT)) {
		vec.x = SPEED;
	}
	if (input->GetKey(KEY_INPUT_UP)) {
		vec.y = -SPEED;
	}
	if (input->GetKey(KEY_INPUT_DOWN)) {
		vec.y = SPEED;
	}

	GetTransform().AddPosition(vec);

	if (input->GetKeyDown(KEY_INPUT_SPACE)) {
		m_se->Replay();
	}

	// シーン遷移のサンプル
	if (input->GetKeyDown(KEY_INPUT_RETURN)) {
		SceneManager::GetInstance()->Change(SCENE_ID::TEST);
	}
}

void Player::OnCollisionEnter(GameObject *collider) {

	// エネミーに触れているとき
	if (collider->GetName() == "Enemy") {
		// 1を押したら
		if (GetInput()->GetKeyDown(KEY_INPUT_1)) {
			collider->Destroy();
		}
	}
}
