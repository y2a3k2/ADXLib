#pragma once
#include"Collider.h"
#include<DxMath.h>

///<summary>
///2D	四角形の当たり判定
///</summary>
class BoxCollider : public Collider2D {

public:
	// 箱の4つの点
	struct	BOX_CORNER {
		VECTOR2 rightUp, rightDown, leftUp, leftDown;
	};

	// 箱の4本の辺
	struct BOX_SIDE {
		float right, left, up, down;
	};

public:
	BoxCollider();
	BoxCollider(GameObject *body);
	~BoxCollider();

	void Awake()override;
	void Update()override;

	// 判定の大きさ(x,y)
	void SetSize(VECTOR2 size) { m_size = size; }
	void SetSize(float x, float y) { m_size = VECTOR2(x, y); }

	// 判定を中心からズラす(x,y)
	void SetOffset(VECTOR2 offset) { m_offset = offset; }
	void SetOffset(float x, float y) { m_offset = VECTOR2(x, y); }

	// 右上、右下、左上、左下の点を返す
	BOX_CORNER GetCorner();

	// 右、左、上、下の辺を返す
	BOX_SIDE GetSide();

	// 中心座標を返す
	VECTOR2 GetCenter() { return DxMath::VGetTranslate(m_body->GetTransform().GetWorldMatrix()) + m_offset; }

private:
	VECTOR2 m_size;
	VECTOR2 m_offset;

};
