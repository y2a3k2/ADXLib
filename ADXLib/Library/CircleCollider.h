#pragma once
#include"Collider.h"
#include<DxMath.h>

///<summary>
///2D	�~�`�̓����蔻��
///</summary>
class CircleCollider : public Collider2D {

public:
	CircleCollider();
	CircleCollider(GameObject *body);
	~CircleCollider();

	void Awake()override;
	void Update()override;

	// ����̑傫��
	void SetRadius(float radius) { m_radius = radius; }

	// ����𒆐S����Y����(x,y)
	void SetOffset(VECTOR2 offset) { m_offset = offset; }
	void SetOffset(float x, float y) { m_offset = VECTOR2(x, y); }

	// ���a��Ԃ�
	float GetRadius() { return m_radius; }

	// ���S���W��Ԃ�
	VECTOR2 GetCenter() { return DxMath::VGetTranslate(m_body->GetTransform().GetWorldMatrix()) + m_offset; }

private:
	float m_radius;
	VECTOR2 m_offset;

};
