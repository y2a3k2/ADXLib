#pragma once
#include<DxLib.h>

class GameObject;

class Transform {

public:
	Transform();
	Transform(GameObject* body);
	virtual ~Transform() {}

	VECTOR GetPosition() { return m_position; }
	VECTOR GetRotation() { return m_rotation; }
	VECTOR GetScale() { return m_scale; }
	MATRIX GetLocalMatrix() { return m_matrix; }
	MATRIX GetWorldMatrix();

	void SetPosition(VECTOR pos);
	void SetRotation(VECTOR rot);
	void SetScale(VECTOR sca);

	void AddPosition(VECTOR pos);
	void AddRotation(VECTOR rot);
	void AddScale(VECTOR sca);

	// ローカル行列を代入する SetやAddをするまではこの値になる
	void SetMatrix(MATRIX mat) { m_matrix = mat; };

private:
	VECTOR m_position;
	VECTOR m_rotation;
	VECTOR m_scale;
	MATRIX m_matrix;
	GameObject* m_body;

	void CreateMatrix();
};
