#include"ColliderManager.h"

#include<Collider.h>
#include<BoxCollider.h>
#include<CircleCollider.h>

ColliderManager * ColliderManager::GetInstance() {

	static ColliderManager *instance = nullptr;

	if (instance == nullptr) {
		instance = new ColliderManager();
	}
	return instance;
}

void ColliderManager::Initialize() {

}

void ColliderManager::FirstUpdate() {

	m_colliders2d.clear();
	m_colliders3d.clear();
}

void ColliderManager::LastUpdate() {

	// “o˜^‚³‚ê‚Ä‚¢‚é”»’è‚ª2ŒÂˆÈ‰º‚È‚ç
	if ((int)m_colliders2d.size() < 2) {
		return;
	}

	// ”»’è‚ğ‚·‚×‚Ä‚Ì‘g‚İ‡‚í‚¹‚ÅÕ“Ë‚³‚¹‚é
	for (auto it1 = m_colliders2d.begin(); it1 != (m_colliders2d.end() - 1); it1++) {
		for (auto it2 = (it1 + 1); it2 != m_colliders2d.end(); it2++) {
			// “–‚½‚Á‚Ä‚¢‚½‚ç
			if (Collision((*it1), (*it2))) {
				(*it1)->OnCollisionEnter((*it2)->GetBody());
				(*it2)->OnCollisionEnter((*it1)->GetBody());
			}
		}
	}
}

void ColliderManager::Push2D(Collider2D *col) {

	m_colliders2d.push_back(col);
}

void ColliderManager::Push3D(Collider3D *col) {

	m_colliders3d.push_back(col);
}

ColliderManager::ColliderManager()
	:SingletonObject(this) {
}

ColliderManager::~ColliderManager() {

}

bool ColliderManager::Collision(Collider2D * col1, Collider2D * col2) {

	auto shape1 = col1->GetShape();
	auto shape2 = col2->GetShape();

	if (shape1 == Collider2D::SHAPE::BOX) {
		if (shape2 == Collider2D::SHAPE::BOX) {
			return IsBox_BoxCol((BoxCollider*)col1, (BoxCollider*)col2);
		}
		if (shape2 == Collider2D::SHAPE::CIRCLE) {
			return IsBox_CircleCol((BoxCollider*)col1, (CircleCollider*)col2);
		}
	}
	else if (shape1 == Collider2D::SHAPE::CIRCLE) {
		if (shape2 == Collider2D::SHAPE::BOX) {
			return IsBox_CircleCol((BoxCollider*)col2, (CircleCollider*)col1);
		}
		if (shape2 == Collider2D::SHAPE::CIRCLE) {
			return IsCircle_CircleCol((CircleCollider*)col1, (CircleCollider*)col2);
		}
	}
	return false;
}

bool ColliderManager::IsBox_BoxCol(BoxCollider * col1, BoxCollider * col2) {

	auto IsCollision = [](BoxCollider* a, BoxCollider* b) {

		VECTOR2 pos = a->GetCenter();
		auto cor = a->GetCorner();

		// ˆê‚Â‚Å‚à“à‘¤‚È‚çtrue
		if (IsPoint_BoxCol(pos, b)) {
			return true;
		}
		if (IsPoint_BoxCol(cor.rightUp, b)) {
			return true;
		}
		if (IsPoint_BoxCol(cor.rightDown, b)) {
			return true;
		}
		if (IsPoint_BoxCol(cor.leftUp, b)) {
			return true;
		}
		if (IsPoint_BoxCol(cor.leftDown, b)) {
			return true;
		}
		return false;
	};

	bool isTouch1 = IsCollision(col1, col2);
	bool isTouch2 = IsCollision(col2, col1);

	// ‚Ç‚¿‚ç‚©‚ªtrue‚È‚çtrue
	return (isTouch1 || isTouch2);
}

bool ColliderManager::IsBox_CircleCol(BoxCollider * col1, CircleCollider * col2) {

	auto col1Cor = col1->GetCorner();
	auto col2Pos = col2->GetCenter();
	auto col2Rad = col2->GetRadius();

	// ‰~‚Ì’†S‚ª” ‚Ì“à‘¤‚É“ü‚Á‚Ä‚¢‚é‚È‚ç
	if (IsPoint_BoxCol(col2Pos, col1)) {
		return true;
	}

	// ” ‚ÌŠp‚ª‰~‚Ì“à‘¤‚É“ü‚Á‚Ä‚¢‚é‚È‚ç
	if (IsPoint_CircleCol(col1Cor.leftUp, col2)) {
		return true;
	}
	if (IsPoint_CircleCol(col1Cor.leftDown, col2)) {
		return true;
	}
	if (IsPoint_CircleCol(col1Cor.rightUp, col2)) {
		return true;
	}
	if (IsPoint_CircleCol(col1Cor.rightDown, col2)) {
		return true;
	}

	// ” ‚Ìü‚Æ‰~‚Ì‹——£‚ª”¼Œa‚æ‚è‹ß‚¢‚È‚ç
	if (Segment_Point_MinLength(col1Cor.leftUp, col1Cor.leftDown, col2Pos) <= col2Rad) {
		return true;
	}
	if (Segment_Point_MinLength(col1Cor.leftUp, col1Cor.rightUp, col2Pos) <= col2Rad) {
		return true;
	}
	if (Segment_Point_MinLength(col1Cor.rightUp, col1Cor.rightDown, col2Pos) <= col2Rad) {
		return true;
	}
	if (Segment_Point_MinLength(col1Cor.leftDown, col1Cor.rightDown, col2Pos) <= col2Rad) {
		return true;
	}
	return false;
}

bool ColliderManager::IsCircle_CircleCol(CircleCollider * col1, CircleCollider * col2) {

	float d = DxMath::GetDistance(col1->GetCenter(), col2->GetCenter());
	float r = (col1->GetRadius() + col2->GetRadius()) * (col1->GetRadius() + col2->GetRadius());

	// “ñ“_‚Ì‹——£‚ª”¼Œa‚Ì‡Z‚æ‚è¬‚³‚¢‚È‚ç
	if (d <= r) {
		return true;
	}
	return false;
}

bool ColliderManager::IsPoint_BoxCol(VECTOR2 pos, BoxCollider * col) {

	BoxCollider::BOX_SIDE size = col->GetSide();

	// ˆê‚©Š‚Å‚àŠO‘¤‚È‚çfalse
	if (size.left > pos.x) {
		return false;
	}
	if (size.right < pos.x) {
		return false;
	}
	if (size.up > pos.y) {
		return false;
	}
	if (size.down < pos.y) {
		return false;
	}
	return true;
}

bool ColliderManager::IsPoint_CircleCol(VECTOR2 pos, CircleCollider * col) {

	VECTOR2 p = col->GetCenter();

	float d = DxMath::GetDistance(pos, p);
	float r = col->GetRadius();

	// ‹——£‚ª”¼Œa‚æ‚è¬‚³‚¢‚È‚ç“à‘¤
	if (d <= (r * r)) {
		return true;
	}

	return false;
}
