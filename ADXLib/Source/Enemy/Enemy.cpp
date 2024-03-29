#include "Enemy.h"
#include<Library.h>

Enemy::Enemy()
	:GameObject("Enemy") {

	/* 画像 */
	auto spr = AddComponent<Sprite>();
	spr->Load("data\\texture\\enemy.png");
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

	GetDebug()->SetLog("当たった");
}
