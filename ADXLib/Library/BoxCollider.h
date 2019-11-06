#pragma once
#include"Collider.h"
#include<DxMath.h>

///<summary>
///2D	�l�p�`�̓����蔻��
///</summary>
class BoxCollider : public Collider2D {

public:
	// ����4�̓_
	struct	BOX_CORNER {
		VECTOR2 rightUp, rightDown, leftUp, leftDown;
	};

	// ����4�{�̕�
	struct BOX_SIDE {
		float right, left, up, down;
	};

public:
	BoxCollider();
	BoxCollider(GameObject *body);
	~BoxCollider();

	void Awake()override;
	void Update()override;

	// ����̑傫��(x,y)
	void SetSize(VECTOR2 size) { m_size = size; }
	void SetSize(float x, float y) { m_size = VECTOR2(x, y); }

	// ����𒆐S����Y����(x,y)
	void SetOffset(VECTOR2 offset) { m_offset = offset; }
	void SetOffset(float x, float y) { m_offset = VECTOR2(x, y); }

	// �E��A�E���A����A�����̓_��Ԃ�
	BOX_CORNER GetCorner();

	// �E�A���A��A���̕ӂ�Ԃ�
	BOX_SIDE GetSide();

	// ���S���W��Ԃ�
	VECTOR2 GetCenter() { return DxMath::VGetTranslate(m_body->GetTransform().GetWorldMatrix()) + m_offset; }

private:
	VECTOR2 m_size;
	VECTOR2 m_offset;

};
