#include"Image.h"
#include<assert.h>
#include<DxMath.h>
#include<GameObject.h>
#include<ComponentManager/ComponentManager.h>

Image::Image()
	:Component() {
	m_handle = -1;
}

Image::Image(GameObject *body)
	: Component(body) {
	m_handle = -1;
	ComponentManager::GetInstance()->PushDraw(this);
}

Image::~Image() {

	ComponentManager::GetInstance()->EraseDraw(this);
	Unload();
}

void Image::Draw() {

	if (m_handle == -1) {
		return;
	}

	SetDrawBright((int)m_color.red, (int)m_color.green, (int)m_color.blue);
	SetDrawBlendMode(m_blendMode, (int)m_blendPal);
	VECTOR pos = GetWorldPosition();
	DrawGraph((int)pos.x - m_center.x, (int)pos.y - m_center.y, m_handle, m_trans);
}

void Image::Load(const char * fileName) {

	// ’†g‚ª‚ ‚é‚È‚ç–³Ž‹
	if (m_handle != -1) {
		return;
	}
	m_handle = LoadGraph(fileName);
	assert(m_handle != -1);

	GetGraphSize(m_handle, &m_size.x, &m_size.y);
	m_center = VGet(m_size.x / 2, m_size.y / 2);
	m_color = COLOR(255, 255, 255);
	m_trans = true;
}

void Image::SetCenter(int cx, int cy) {

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

	return DxMath::VGetTranslate(m_body->GetTransform().GetWorldMatrix());
}

void Image::Unload() {

	if (m_handle == 1) {
		return;
	}
	int error = DeleteGraph(m_handle);
	m_handle = -1;
}
