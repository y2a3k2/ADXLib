#include "CircleCollider.h"
#include<Sprite.h>
#include<ColliderManager/ColliderManager.h>

CircleCollider::CircleCollider()
	:Collider2D(nullptr, SHAPE::CIRCLE) {

}

CircleCollider::CircleCollider(GameObject * body)
	: Collider2D(body, SHAPE::CIRCLE) {

}

CircleCollider::~CircleCollider() {

}

void CircleCollider::Awake() {

	// Sprite‚ª‚ ‚Á‚½‚ç
	auto spr = m_body->GetComponent<Image>();
	if (spr != nullptr) {
		auto size = spr->GetSize();
		m_radius = (float)((size.x + size.y) / 4);
		return;
	}
	// TransSprite‚ª‚ ‚Á‚½‚ç
	spr = m_body->GetComponent<Sprite>();
	if (spr != nullptr) {
		auto size = spr->GetSize();
		m_radius = (float)((size.x + size.y) / 4);
		return;
	}
}

void CircleCollider::Update() {

	ColliderManager::GetInstance()->Push2D(this);
}
