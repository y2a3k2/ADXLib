#include"Image.h"
#include<assert.h>
#include<DxMath.h>
#include<GameObject.h>
#include<ComponentManager/ComponentManager.h>
#include<ResourceManager/ResourceManager.h>

Image::Image()
	:Component() {
	m_handle = -1;
	m_trans = true;
	m_isCenterInit = false;
	m_transform = nullptr;
	m_color = COLOR(255, 255, 255);
}

Image::Image(GameObject *body)
	: Component(body) {
	m_handle = -1;
	m_trans = true;
	m_isCenterInit = false;
	m_transform = nullptr;
	m_color = COLOR(255, 255, 255);
	ComponentManager::GetInstance()->PushDraw(this);
}

Image::~Image() {

	if (m_transform != nullptr) {
		delete m_transform;
	}
	ComponentManager::GetInstance()->EraseDraw(this);
	Unload();
}

void Image::Draw() {

	// まだハンドルがないとき
	if (m_handle == -1) {
		int handle = ResourceManager::GetInstance()->GetGraphHandle(m_fileName.c_str());
		// ロード出来ていないなら
		if (handle == -1) {
			return;
		}
		/* 初期化 */
		m_handle = handle;
		GetGraphSize(m_handle, &m_size.x, &m_size.y);
		// 予め指定していなければ
		if (!m_isCenterInit) {
			m_center = VGet(m_size.x / 2, m_size.y / 2);
		}
	}
	SetDrawBright((int)m_color.red, (int)m_color.green, (int)m_color.blue);
	SetDrawBlendMode(m_blendMode, (int)m_blendPal);
	VECTOR pos = GetWorldPosition();
	DrawGraph((int)pos.x - m_center.x, (int)pos.y - m_center.y, m_handle, m_trans);
}

void Image::Load(const char * fileName, bool quickly) {

	// 中身があるなら無視
	if (m_handle != -1) {
		return;
	}

	// 即時なら
	if (quickly) {
		m_fileName = fileName;
		int handle = ResourceManager::GetInstance()->LoadGraph(fileName);

		// ハンドルが取れたら
		if (handle != -1) {
			m_handle = handle;
			GetGraphSize(m_handle, &m_size.x, &m_size.y);
			// 予め指定していなければ
			if (!m_isCenterInit) {
				m_center = VGet(m_size.x / 2, m_size.y / 2);
			}
		}
	}
	else {
		m_fileName = fileName;
		ResourceManager::GetInstance()->PushLoadGraph(fileName);
	}
}

void Image::SetCenter(int cx, int cy) {

	m_isCenterInit = true;
	m_center.x = cx;
	m_center.y = cy;
}

void Image::SetColor(unsigned char red, unsigned char green, unsigned char blue) {

	m_color.red = red;
	m_color.green = green;
	m_color.blue = blue;
}

void Image::SetTrans(bool flag) {

	m_trans = flag;
}

void Image::SetBlendDefault() {

	m_blendMode = DX_BLENDMODE_NOBLEND;
	m_blendPal = 0;
}

void Image::SetBlendAlpha(unsigned char pal) {

	m_blendMode = DX_BLENDMODE_ALPHA;
	m_blendPal = pal;
}

void Image::SetBlendAdd(unsigned char pal) {

	m_blendMode = DX_BLENDMODE_ADD;
	m_blendPal = pal;

}

void Image::SetBlendSub(unsigned char pal) {

	m_blendMode = DX_BLENDMODE_SUB;
	m_blendPal = pal;
}

void Image::SetBlendMula(unsigned char pal) {

	m_blendMode = DX_BLENDMODE_MULA;
	m_blendPal = pal;
}

void Image::SetBlendInvsrc(unsigned char pal) {

	m_blendMode = DX_BLENDMODE_INVSRC;
	m_blendPal = pal;
}

void Image::SetBlendPmaAlpha(unsigned char pal) {

	m_blendMode = DX_BLENDMODE_PMA_ALPHA;
	m_blendPal = pal;
}

void Image::SetBlendPmaAdd(unsigned char pal) {

	m_blendMode = DX_BLENDMODE_PMA_ADD;
	m_blendPal = pal;
}

void Image::SetBlendPmaSub(unsigned char pal) {

	m_blendMode = DX_BLENDMODE_PMA_SUB;
	m_blendPal = pal;
}

void Image::SetBlendPmaInvsrc(unsigned char pal) {

	m_blendMode = DX_BLENDMODE_PMA_INVSRC;
	m_blendPal = pal;
}

const INT_VECTOR2 &Image::GetSize() {

	return m_size;
}

VECTOR Image::GetWorldPosition() {

	// 決め打ちされているなら
	if (m_transform != nullptr) {
		return m_transform->GetPosition();
	}
	// 本体がいるなら
	else if (m_body != nullptr) {
		return DxMath::VGetTranslate(m_body->GetTransform().GetWorldMatrix());
	}
	return VGet(0, 0, 0);
}

void Image::SetPosition(VECTOR pos) {

	if (m_transform == nullptr) {
		m_transform = new Transform();
	}
	m_transform->SetPosition(pos);
}

void Image::SetRotation(VECTOR rot) {

	if (m_transform == nullptr) {
		m_transform = new Transform();
	}
	m_transform->SetRotation(rot);
}

void Image::SetScale(VECTOR sca) {

	if (m_transform == nullptr) {
		m_transform = new Transform();
	}
	m_transform->SetScale(sca);
}

void Image::Unload() {

	if (m_handle == 1) {
		return;
	}
	ResourceManager::GetInstance()->DeleteGraphHandle(m_fileName.c_str());
	m_handle = -1;
}
