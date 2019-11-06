#pragma once
#include<vector>
#include<DxMath.h>
#include<SingletonObject.h>

class Collider2D;
class BoxCollider;
class CircleCollider;

class Collider3D;

class ColliderManager : public SingletonObject {

public:
	static ColliderManager *GetInstance();

	void Initialize()override;
	void FirstUpdate();
	void LastUpdate();

	void Push2D(Collider2D *col);
	void Push3D(Collider3D *col);

private:
	ColliderManager();
	~ColliderManager();

	std::vector<Collider2D*> m_colliders2d;
	std::vector<Collider3D*> m_colliders3d;

	bool Collision(Collider2D *col1, Collider2D *col2);

	static bool IsBox_BoxCol(BoxCollider* col1, BoxCollider* col2);
	static bool IsBox_CircleCol(BoxCollider *col1, CircleCollider *col2);
	static bool IsCircle_CircleCol(CircleCollider *col1, CircleCollider *col2);

	static bool IsPoint_BoxCol(VECTOR2 pos, BoxCollider *col);
	static bool IsPoint_CircleCol(VECTOR2 pos, CircleCollider *col);
};
