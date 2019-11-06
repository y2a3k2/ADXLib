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

	// SpriteÇ™Ç†Ç¡ÇΩÇÁ
	auto spr = m_body->GetComponent<Image>();
	if (spr != nullptr) {
		auto size = spr->GetSize();
		m_size = VECTOR2((float)(size.x / 2), (float)(size.y / 2));
		return;
	}
	// TransSpriteÇ™Ç†Ç¡ÇΩÇÁ
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

	// âEè„
	corner.rightUp.x = pos.x + m_size.x;
	corner.rightUp.y = pos.y - m_size.y;

	// âEâ∫
	corner.rightDown.x = pos.x + m_size.x;
	corner.rightDown.y = pos.y + m_size.y;

	// ç∂è„
	corner.leftUp.x = pos.x - m_size.x;
	corner.leftUp.y = pos.y - m_size.y;

	// ç∂â∫
	corner.leftDown.x = pos.x - m_size.x;
	corner.leftDown.y = pos.y + m_size.y;

	return corner;
}

BoxCollider::BOX_SIDE BoxCollider::GetSide() {

	BOX_SIDE size;
	VECTOR2 pos = GetCenter();

	size.left = pos.x - m_size.x;	// ç∂
	size.right = pos.x + m_size.x;	// âE
	size.up = pos.y - m_size.y;		// è„
	size.down = pos.y + m_size.y;	// â∫
	return size;
}
