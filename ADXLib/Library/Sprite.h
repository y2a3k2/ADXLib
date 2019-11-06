#pragma once
#include"Image.h"

///<summary>
///	回転、拡縮、切り取りを可能にした2D描画クラス
///	Imageと比べて処理は重い
///	自キャラや敵キャラなどに用いる
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
