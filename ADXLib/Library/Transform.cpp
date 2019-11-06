#include "Transform.h"
#include <DxMath.h>
#include <GameObject.h>

Transform::Transform() {

	m_position = VGet(0, 0, 0);
	m_rotation = VGet(0, 0, 0);
	m_scale = VGet(1.0f, 1.0f, 1.0f);
	CreateMatrix();
}

Transform::Transform(GameObject * body) {

	m_body = body;
	m_position = VGet(0, 0, 0);
	m_rotation = VGet(0, 0, 0);
	m_scale = VGet(1.0f, 1.0f, 1.0f);
	CreateMatrix();
}

MATRIX Transform::GetWorldMatrix() {

	if (m_body == nullptr) {
		return MGetIdent();
	}
	auto p = m_body->GetParent();
	if (p == nullptr)
		return GetLocalMatrix();
	return MMult(GetLocalMatrix(), p->GetTransform().GetWorldMatrix());
}

void Transform::SetPosition(VECTOR pos) {

	m_position = pos;
	CreateMatrix();
}

void Transform::SetRotation(VECTOR rot) {

	m_rotation = rot;
	CreateMatrix();
}

void Transform::SetScale(VECTOR sca) {

	m_scale = sca;
	CreateMatrix();
}

void Transform::AddPosition(VECTOR pos) {

	m_position += pos;
	CreateMatrix();
}

void Transform::AddRotation(VECTOR rot) {

	m_rotation += rot;
	CreateMatrix();
}

void Transform::AddScale(VECTOR sca) {

	m_scale = sca;
	CreateMatrix();
}

void Transform::CreateMatrix() {

	MATRIX tra = MGetTranslate(m_position);
	MATRIX rot = MMult(MMult(MGetRotX(m_rotation.x), MGetRotY(m_rotation.y)), MGetRotZ(m_rotation.z));
	MATRIX sca = MGetScale(m_scale);
	m_matrix = MMult(sca, MMult(rot, tra));	// à⁄ìÆÅAâÒì]ÅAägèkÇÃèáÇ…çsÇ§
}
