#include "Sprite.h"
#include <DxMath.h>

Sprite::Sprite()
	:Image() {

	m_scale = 1.0f;
	m_angle = 0;
}

Sprite::Sprite(GameObject * body)
	:Image(body) {

	m_scale = 1.0f;
	m_angle = 0;
}

Sprite::~Sprite() {

}

void Sprite::Draw() {

	auto sub = GetWorldPosition();
	auto pos = INT_VECTOR2((int)sub.x - m_center.x, (int)sub.y - m_center.y);
	DrawRectRotaGraph(pos.x, pos.y, m_rect.lx, m_rect.ly, m_rect.rx - m_rect.lx, m_rect.ry - m_rect.ly, (double)m_scale, (double)m_angle, m_handle, m_trans);
}

void Sprite::Load(const char * fileName) {

	Image::Load(fileName);

	auto size = GetSize();
	SetRect(0, 0, size.x, size.y);
	m_center = INT_VECTOR2(0, 0);
}

void Sprite::SetRect(int lx, int ly, int rx, int ry) {

	m_rect.rx = rx;
	m_rect.ry = ry;
	m_rect.lx = lx;
	m_rect.ly = ly;

	m_size = INT_VECTOR2(rx - lx, ry - ly);
}

void Sprite::SetScale(float scale) {

	m_scale = scale;
}

void Sprite::SetAngle(int degree) {

	m_angle = DxMath::GetRadian(degree);
}

void Sprite::SetAngle(float radian) {

	m_angle = radian;
}
