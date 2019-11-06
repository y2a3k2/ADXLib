#include "Text.h"
#include<ComponentManager/ComponentManager.h>
#include<GameObject.h>
#include<DxMath.h>
#include<assert.h>

Text::Text() {

	m_fontHandle = -1;
	m_colorHandle = GetColor(255, 255, 255);
}

Text::Text(GameObject * body)
	: Component(body) {
	m_fontHandle = -1;
	m_colorHandle = GetColor(255, 255, 255);
	ComponentManager::GetInstance()->PushDraw(this);
}

Text::~Text() {

	ComponentManager::GetInstance()->EraseDraw(this);
}

void Text::Draw() {

	VECTOR pos = DxMath::VGetTranslate(m_body->GetTransform().GetWorldMatrix());

	// ハンドルがなければ
	if (m_fontHandle == -1) {
		DrawString((int)pos.x, (int)pos.y, m_text.c_str(), m_colorHandle);
	}

	// ハンドルがあれば
	else {
		DrawStringToHandle((int)pos.x, (int)pos.y, m_text.c_str(), m_colorHandle, m_fontHandle);
	}
}

void Text::SetText(const char * text) {

	m_text = text;
}

void Text::SetText(const std::string & text) {

	m_text = text;
}

void Text::SetColor(int red, int green, int blue) {

	m_fontHandle = GetColor(red, green, blue);
}

void Text::CreateFontHandle(int size, int thick, int fontType) {

	m_fontHandle = CreateFontToHandle(NULL, size, thick, fontType);
	assert(m_fontHandle != -1);
}

void Text::LoadFontHandle(const char * fileName, int edgeSize) {

	m_fontHandle = LoadFontDataToHandle(fileName, edgeSize);
	assert(m_fontHandle != -1);
}
