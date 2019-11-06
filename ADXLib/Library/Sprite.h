#pragma once
#include"Image.h"

///<summary>
///	��]�A�g�k�A�؂�����\�ɂ���2D�`��N���X
///	Image�Ɣ�ׂď����͏d��
///	���L������G�L�����Ȃǂɗp����
///</summary>
class Sprite : public Image {

public:
	Sprite();
	Sprite(GameObject *body);
	virtual	~Sprite();

	virtual	void Draw()override;

	virtual	void Load(const char *fileName);

	void SetRect(int lx, int ly, int rx, int ry);
	void SetScale(float scale);
	void SetAngle(int degree);
	void SetAngle(float radian);

private:
	struct Rect { int rx, ry, lx, ly; };
	Rect m_rect;
	float m_angle;
	float m_scale;

};
