#include "Sprite.h"
#include <DxMath.h>
#include<ResourceManager/ResourceManager.h>

Sprite::Sprite()
	:Image() {
	m_scale = 1.0f;
	m_angle = 0;
	m_isRectInit = false;
}

Sprite::Sprite(GameObject * body)
	:Image(body) {
	m_scale = 1.0f;
	m_angle = 0;
	m_isRectInit = false;
}

Sprite::~Sprite() {

}

void Sprite::Draw() {

	// まだハンドルがないとき
	if (m_handle == -1) {
		int handle = ResourceManager::GetInstance()->GetGraphHandle(m_fileName.c_str());
		// ロード出来ていないなら
		if (handle == -1) {
			return;
		}
		/* 初期化 */
		m_handle = handle;

		// 予め指定していなければ
		if (!m_isRectInit) {
			GetGraphSize(m_handle, &m_size.x, &m_size.y);
			SetRect(0, 0, m_size.x, m_size.y);
		}

		// 予め指定していなければ
		if (!m_isCenterInit) {
			m_center = INT_VECTOR2(0, 0);
		}
	}
	this;
	auto sub = GetWorldPosition();
	auto pos = INT_VECTOR2((int)sub.x - m_center.x, (int)sub.y - m_center.y);
	DrawRectRotaGraph(pos.x, pos.y, m_rect.lx, m_rect.ly, m_rect.rx - m_rect.lx, m_rect.ry - m_rect.ly, (double)m_scale, (double)m_angle, m_handle, m_trans);
}

void Sprite::Load(const char * fileName, bool quickly) {

	Image::Load(fileName, quickly);

	// ハンドルが来たら
	if (m_handle != -1) {
		// 予め指定していなければ
		if (!m_isRectInit) {
			GetGraphSize(m_handle, &m_size.x, &m_size.y);
			SetRect(0, 0, m_size.x, m_size.y);
		}
		// 予め指定していなければ
		if (!m_isCenterInit) {
			m_center = INT_VECTOR2(0, 0);
		}
	}
}

void Sprite::SetRect(int lx, int ly, int rx, int ry) {

	m_isRectInit = true;
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
