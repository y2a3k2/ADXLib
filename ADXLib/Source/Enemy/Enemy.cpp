#include "Enemy.h"
#include<Library.h>

Enemy::Enemy()
	:GameObject("Enemy") {

	/* ‰æ‘œ */
	auto spr = AddComponent<Sprite>();
	spr->Load("data\\texture\\enemy.png", true);	// ‘¦Žž“Ç‚Ýž‚Ý
	spr->SetRect(0, 0, 32, 32);

	auto col = AddComponent<BoxCollider>();
}

Enemy::~Enemy() {

}

void Enemy::Initialize() {

	GetTransform().SetPosition(VGet(400, 100, 0));
}

void Enemy::Update() {

}

void Enemy::OnCollisionEnter(GameObject * collider) {

	GetDebug()->SetLog("“–‚½‚Á‚½");
}
