#include"Player.h"
#include<Library.h>
#include<SceneManager/SceneManager.h>
#include<ResourceManager/ResourceManager.h>

namespace {
	GameObject *enemy;
}

struct DATA {
	DATA() { num = 0; strcpy_s(name, 256, ""); }
	DATA(int nu, const char *na) { num = nu, strcpy_s(name, 256, na); }
	int num;
	char name[256];
};

Player::Player()
	:GameObject("Player") {

	/* �摜 */
	auto spr = AddComponent<Sprite>();
	spr->Load("data\\texture\\solvalou.png");
	spr->SetRect(0, 0, 32, 32);

	/* �� */
	m_se = AddComponent<Sound>();
	m_se->Load("data\\sound\\fire1.mp3");
	m_se = AddComponent<Sound>();
	m_se->Load("data\\sound\\fire2.mp3");
	m_se = AddComponent<Sound>();
	m_se->Load("data\\sound\\fire3.mp3");
	m_se = AddComponent<Sound>();
	m_se->Load("data\\sound\\fire4.mp3");
	m_se = AddComponent<Sound>();
	m_se->Load("data\\sound\\fire5.mp3");
	m_se = AddComponent<Sound>();
	m_se->Load("data\\sound\\fire6.mp3");
	m_se = AddComponent<Sound>();
	m_se->Load("data\\sound\\fire7.mp3");
	m_se = AddComponent<Sound>();
	m_se->Load("data\\sound\\fire8.mp3");
	m_se = AddComponent<Sound>();
	m_se->Load("data\\sound\\fire9.mp3");
	m_se = AddComponent<Sound>();
	m_se->Load("data\\sound\\fire10.mp3");

	auto col = AddComponent<CircleCollider>();
}

Player::~Player() {

}

void Player::Initialize() {

	// �ʒu�̏�����(��ʂ̐^�񒆂�)
	GetTransform().SetPosition(VGet(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0));

	// �`�ʏ���ύX
	SetLayer((int)LAYER::PLAYER);

	// �\���̂��Z�[�u
	auto p = StructSave<DATA>("data\\save\\save.txt");
	auto data = p.Read();
	p.Write(DATA(data.num + 1, "abc"));

	// �����Ɠ����K�w���猟������
	enemy = GetParent()->Search("Enemy");
}

void Player::Update() {

	static Timer timer;

	const float SPEED = MOVE_SPEED * GetTime()->GetDelta(); // ���x�~�f���^�^�C��
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
		timer.Reset();
		m_se->Replay();
	}

	// �V�[���J�ڂ̃T���v��
	if (input->GetKeyDown(KEY_INPUT_RETURN)) {
		SceneManager::GetInstance()->Change(SCENE_ID::TEST2D);
	}

	GetDebug()->SetLog("Second %0.2f", timer.GetSecond());
	GetDebug()->SetLog("���[�h�� %0.2f", ResourceManager::GetInstance()->GetLoadPercent() * 100.0f);
}

void Player::OnCollisionEnter(GameObject *collider) {

	// �G�l�~�[�ɐG��Ă���Ƃ�
	if (collider->GetName() == "Enemy") {
		// 1����������
		if (GetInput()->GetKeyDown(KEY_INPUT_1)) {
			collider->Destroy();
		}
	}
}
