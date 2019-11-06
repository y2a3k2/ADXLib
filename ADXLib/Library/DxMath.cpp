#include "DxMath.h"

DxMath::VECTOR2 DxMath::VGet(VECTOR v) { return VGet(v.x, v.y); }
VECTOR DxMath::VGet(VECTOR2 v) { return DxLib::VGet(v.x, v.y, 0.0f); }
DxMath::VECTOR2 DxMath::VGet(float x, float y) { return VECTOR2(x, y); }
DxMath::INT_VECTOR2 DxMath::VGet(int x, int y) { return INT_VECTOR2(x, y); }

float DxMath::Segment_Point_MinLength(VECTOR2 Pos1, VECTOR2 Pos2, VECTOR2 PointPos) {

	return Segment_Point_MinLength(VGet(Pos1), VGet(Pos2), VGet(PointPos));
}

VECTOR DxMath::VGetTranslate(const MATRIX & mat) { return DxLib::VGet(mat.m[3][0], mat.m[3][1], mat.m[3][2]); }

int DxMath::Lerp(int a, int b, float t) {

	if (t <= 0.0f)
		return a;
	else if (t >= 1.0f)
		return b;
	return (int)((float)a + t * ((float)b - (float)a));
}

float DxMath::Lerp(float a, float b, float t) {

	if (t <= 0.0f)
		return a;
	else if (t >= 1.0f)
		return b;
	return a + t * (b - a);
}

VECTOR DxMath::Lerp(VECTOR a, VECTOR b, float t) {

	float x = Lerp(a.x, b.x, t);
	float y = Lerp(a.y, b.y, t);
	float z = Lerp(a.z, b.z, t);
	return DxLib::VGet(x, y, z);
}

VECTOR2 DxMath::Lerp(VECTOR2 a, VECTOR2 b, float t) {

	float x = Lerp(a.x, b.x, t);
	float y = Lerp(a.y, b.y, t);
	return DxLib::VGet(x, y, 0);
}

float DxMath::InverseLerp(float a, float b, float t) {

	float ans = 0;
	if (a != b) {
		ans = (t - a) / (b - a);
	}
	ans = ans > 1 ? 1 : ans;
	ans = ans < 0 ? 0 : ans;
	return ans;
}

int DxMath::GetDegree(float rad) {

	return (int)(rad * 180.0f / DX_PI_F);
}

float DxMath::GetRadian(int deg) {

	return (float)deg * DX_PI_F / 180.0f;
}

float DxMath::GetDistance(VECTOR pos1, VECTOR pos2) {

	float x = pos2.x - pos1.x;
	float y = pos2.y - pos1.y;
	float z = pos2.z - pos1.z;

	return (x * x) + (y * y) + (z * z);
}

float DxMath::GetDistance(VECTOR2 pos1, VECTOR2 pos2) {

	float x = pos2.x - pos1.x;
	float y = pos2.y - pos1.y;

	return (x * x) + (y * y);
}

float DxMath::GetDistance(float p1, float p2) {

	float r = (p2 - p1);

	return r * r;
}

float DxMath::GetDistanceSqrt(VECTOR pos1, VECTOR pos2) {

	float x = pos2.x - pos1.x;
	float y = pos2.y - pos1.y;
	float z = pos2.z - pos1.z;

	return x + y + z;
}

float DxMath::GetDistanceSqrt(VECTOR2 pos1, VECTOR2 pos2) {

	float x = pos2.x - pos1.x;
	float y = pos2.y - pos1.y;

	return x + y;
}

float DxMath::GetDistanceSqrt(float p1, float p2) {

	return p2 - p1;
}

VECTOR DxMath::operator + (const VECTOR &a, const VECTOR &b) { return VAdd(a, b); }
VECTOR DxMath::operator - (const VECTOR &a, const VECTOR &b) { return VSub(a, b); }
VECTOR DxMath::operator * (const VECTOR &a, const VECTOR &b) { return DxLib::VGet(a.x * b.x, a.y * b.y, a.z * b.z); }
VECTOR DxMath::operator / (const VECTOR &a, const VECTOR &b) { return DxLib::VGet(a.x / b.x, a.y / b.y, a.z / b.z); }
VECTOR DxMath::operator += (VECTOR &a, const VECTOR &b) { return (a = VAdd(a, b)); }
VECTOR DxMath::operator -= (VECTOR &a, const VECTOR &b) { return (a = VSub(a, b)); }
VECTOR DxMath::operator *= (VECTOR &a, const VECTOR &b) { return a * b; }
VECTOR DxMath::operator /= (VECTOR &a, const VECTOR &b) { return a / b; }

VECTOR DxMath::operator * (const VECTOR &a, const float b) { return VScale(a, b); }
VECTOR DxMath::operator / (const VECTOR &a, const float b) { return VScale(a, (1.0f / b)); }
VECTOR DxMath::operator *= (VECTOR &a, const float b) { return (a = VScale(a, b)); }
VECTOR DxMath::operator /= (VECTOR &a, const float b) { return (a = VScale(a, (1.0f / b))); }

VECTOR DxMath::operator + (const VECTOR & a, const VECTOR2 & b) { return DxLib::VGet(a.x + b.x, a.y + b.y, a.z); }
VECTOR DxMath::operator - (const VECTOR & a, const VECTOR2 & b) { return DxLib::VGet(a.x - b.x, a.y - b.y, a.z); }
VECTOR DxMath::operator * (const VECTOR & a, const VECTOR2 & b) { return DxLib::VGet(a.x * b.x, a.y * b.y, a.z); }
VECTOR DxMath::operator / (const VECTOR & a, const VECTOR2 & b) { return DxLib::VGet(a.x / b.x, a.y / b.y, a.z); }
VECTOR DxMath::operator += (VECTOR & a, const VECTOR2 & b) { return DxLib::VGet(a.x += b.x, a.y += b.y, a.z); }
VECTOR DxMath::operator-=(VECTOR & a, const VECTOR2 & b) { return DxLib::VGet(a.x -= b.x, a.y -= b.y, a.z); }
VECTOR DxMath::operator*=(VECTOR & a, const VECTOR2 & b) { return DxLib::VGet(a.x *= b.x, a.y *= b.y, a.z); }
VECTOR DxMath::operator/=(VECTOR & a, const VECTOR2 & b) { return DxLib::VGet(a.x /= b.x, a.y /= b.y, a.z); }
