#pragma once
#include"Collider.h"
#include<DxMath.h>

///<summary>
///2D	円形の当たり判定
///</summary>
class CircleCollider : public Collider2D {

public:
	CircleCollider();
	CircleCollider(GameObject *body);
	~CircleCollider();

	void Awake()override;
	void Update()override;

	// 判定の大きさ
	void SetRadius(float radius) { m_radius = radius; }

	// 判定を中心からズラす(x,y)
	void SetOffset(VECTOR2 offset) { m_offset = offset; }
	void SetOffset(float x, float y) { m_offset = VECTOR2(x, y); }

	// 半径を返す
	float GetRadius() { return m_radius; }

	// 中心座標を返す
	VECTOR2 GetCenter() { return DxMath::VGetTranslate(m_body->GetTransform().GetWorldMatrix()) + m_offset; }

private:
	float m_radius;
	VECTOR2 m_offset;

};
