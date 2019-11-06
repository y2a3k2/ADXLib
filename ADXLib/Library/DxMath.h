#pragma once
#include<DxLib.h>

namespace DxMath {
	struct INT_VECTOR2 {
		INT_VECTOR2() { ZeroMemory(this, sizeof(this)); }
		INT_VECTOR2(int rx, int ry) { x = rx; y = ry; }
		int x, y;
	};

	struct VECTOR2 {
		VECTOR2() { ZeroMemory(this, sizeof(this)); }
		VECTOR2(float rx, float ry) { x = rx; y = ry; }
		VECTOR2(VECTOR2& v) { x = v.x; y = v.y; }
		VECTOR2(VECTOR& v) { x = v.x; y = v.y; }

		/* VECTOR�Ƃ̃I�y���[�^�[ */
		VECTOR2 operator + (const VECTOR &a) { return VECTOR2(x + a.x, y + a.y); }
		VECTOR2 operator - (const VECTOR &a) { return VECTOR2(x - a.x, y - a.y); }
		VECTOR2 operator * (const VECTOR &a) { return VECTOR2(x * a.x, y * a.y); }
		VECTOR2 operator * (const float &a) { return VECTOR2(x * a, y * a); }
		VECTOR2 operator / (const VECTOR &a) { return VECTOR2(x / a.x, y / a.y); }
		VECTOR2 operator / (const float &a) { return VECTOR2(x / a, y / a); }

		VECTOR2 operator += (const VECTOR &a) { return VECTOR2(x += a.x, y += a.y); }
		VECTOR2 operator -= (const VECTOR &a) { return VECTOR2(x -= a.x, y -= a.y); }
		VECTOR2 operator *= (const VECTOR &a) { return VECTOR2(x *= a.x, y *= a.y); }
		VECTOR2 operator *= (const float &a) { return VECTOR2(x *= a, y *= a); }
		VECTOR2 operator /= (const VECTOR &a) { return VECTOR2(x /= a.x, y /= a.y); }
		VECTOR2 operator /= (const float &a) { return VECTOR2(x /= a, y /= a); }

		/* VECTOR2�Ƃ̃I�y���[�^�[ */
		VECTOR2 operator + (const VECTOR2 &a) { return VECTOR2(x + a.x, y + a.y); }
		VECTOR2 operator - (const VECTOR2 &a) { return VECTOR2(x - a.x, y - a.y); }
		VECTOR2 operator * (const VECTOR2 &a) { return VECTOR2(x * a.x, y * a.y); }
		VECTOR2 operator / (const VECTOR2 &a) { return VECTOR2(x / a.x, y / a.y); }

		VECTOR2 operator += (const VECTOR2 &a) { return VECTOR2(x += a.x, y += a.y); }
		VECTOR2 operator -= (const VECTOR2 &a) { return VECTOR2(x -= a.x, y -= a.y); }
		VECTOR2 operator *= (const VECTOR2 &a) { return VECTOR2(x *= a.x, y *= a.y); }
		VECTOR2 operator /= (const VECTOR2 &a) { return VECTOR2(x /= a.x, y /= a.y); }

		void operator = (const VECTOR &v) { x = v.x; y = v.y; }

		float x, y;
	};

	struct COLOR {
		COLOR() { ZeroMemory(this, sizeof(this)); }
		COLOR(unsigned char red, unsigned char green, unsigned char blue) {
			this->red = red; this->green = green; this->blue = blue;
		}
		unsigned char red, green, blue;
	};

	/* VGet�̃o���G�[�V���� */
	VECTOR2 VGet(VECTOR v);
	VECTOR VGet(VECTOR2 v);
	VECTOR2 VGet(float x, float y);
	INT_VECTOR2 VGet(int x, int y);

	float Segment_Point_MinLength(VECTOR2 Pos1, VECTOR2 Pos2, VECTOR2 PointPos);

	/* �֐��ꗗ */
	VECTOR VGetTranslate(const MATRIX &mat);

	// ��ԏ���
	int Lerp(int a, int b, float t);
	float Lerp(float a, float b, float t);
	VECTOR Lerp(VECTOR a, VECTOR b, float t);
	VECTOR2 Lerp(VECTOR2 a, VECTOR2 b, float t);

	// �t��ԏ���
	float InverseLerp(float a, float b, float t);

	// Degree�ɕϊ�
	int GetDegree(float rad);

	// Radian�ɕϊ�
	float GetRadian(int deg);

	// �����̓���Ԃ�
	float GetDistance(VECTOR pos1, VECTOR pos2);
	float GetDistance(VECTOR2 pos1, VECTOR2 pos2);
	float GetDistance(float p1, float p2);

	// ���������̂܂ܕԂ�(pos1����pos2�̋���,�񐄏�)
	float GetDistanceSqrt(VECTOR pos1, VECTOR pos2);
	float GetDistanceSqrt(VECTOR2 pos1, VECTOR2 pos2);
	float GetDistanceSqrt(float p1, float p2);

	/* VECTOR���m�̃I�y���[�^�[ */
	VECTOR operator + (const VECTOR &a, const VECTOR &b);
	VECTOR operator - (const VECTOR &a, const VECTOR &b);
	VECTOR operator * (const VECTOR &a, const VECTOR &b);
	VECTOR operator / (const VECTOR &a, const VECTOR &b);
	VECTOR operator += (VECTOR &a, const VECTOR &b);
	VECTOR operator -= (VECTOR &a, const VECTOR &b);
	VECTOR operator *= (VECTOR &a, const VECTOR &b);
	VECTOR operator /= (VECTOR &a, const VECTOR &b);

	/* VECTOR��float�̃I�y���[�^�[ */
	VECTOR operator * (const VECTOR &a, const float b);
	VECTOR operator / (const VECTOR &a, const float b);
	VECTOR operator *= (VECTOR &a, const float b);
	VECTOR operator /= (VECTOR &a, const float b);

	/* VECTOR��VECTOR2�̃I�y���[�^�[ */
	VECTOR operator + (const VECTOR &a, const VECTOR2 &b);
	VECTOR operator - (const VECTOR &a, const VECTOR2 &b);
	VECTOR operator * (const VECTOR &a, const VECTOR2 &b);
	VECTOR operator / (const VECTOR &a, const VECTOR2 &b);
	VECTOR operator += (VECTOR &a, const VECTOR2 &b);
	VECTOR operator -= (VECTOR &a, const VECTOR2 &b);
	VECTOR operator *= (VECTOR &a, const VECTOR2 &b);
	VECTOR operator /= (VECTOR &a, const VECTOR2 &b);
};

using namespace DxMath;
