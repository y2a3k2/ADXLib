#include"BoxCollider.h"
#include<Sprite.h>
#include<ColliderManager/ColliderManager.h>

BoxCollider::BoxCollider()
	:Collider2D(nullptr, SHAPE::BOX) {

}

BoxCollider::BoxCollider(GameObject * body)
	: Collider2D(body, SHAPE::BOX) {

}

BoxCollider::~BoxCollider() {

}

void BoxCollider::Awake() {

	// Spriteがあったら
	auto spr = m_body->GetComponent<Image>();
	if (spr != nullptr) {
		auto size = spr->GetSize();
		m_size = VECTOR2((float)(size.x / 2), (float)(size.y / 2));
		return;
	}
	// TransSpriteがあったら
	spr = m_body->GetComponent<Sprite>();
	if (spr != nullptr) {
		auto size = spr->GetSize();
		m_size = VECTOR2((float)(size.x / 2), (float)(size.y / 2));
		return;
	}
}

void BoxCollider::Update() {

	ColliderManager::GetInstance()->Push2D(this);
}

BoxCollider::BOX_CORNER BoxCollider::GetCorner() {

	BOX_CORNER corner;
	VECTOR2 pos = GetCenter();

	// 右上
	corner.rightUp.x = pos.x + m_size.x;
	corner.rightUp.y = pos.y - m_size.y;

	// 右下
	corner.rightDown.x = pos.x + m_size.x;
	corner.rightDown.y = pos.y + m_size.y;

	// 左上
	corner.leftUp.x = pos.x - m_size.x;
	corner.leftUp.y = pos.y - m_size.y;

	// 左下
	corner.leftDown.x = pos.x - m_size.x;
	corner.leftDown.y = pos.y + m_size.y;

	return corner;
}

BoxCollider::BOX_SIDE BoxCollider::GetSide() {

	BOX_SIDE size;
	VECTOR2 pos = GetCenter();

	size.left = pos.x - m_size.x;	// 左
	size.right = pos.x + m_size.x;	// 右
	size.up = pos.y - m_size.y;		// 上
	size.down = pos.y + m_size.y;	// 下
	return size;
}
