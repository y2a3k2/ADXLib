#pragma once
#include<GameObject.h>

class Sound;

class Player : public GameObject {

public:
	Player();
	~Player();

	void Initialize()override;
	void Update()override;

	void OnCollisionEnter(GameObject *collider)override;

private:
	const float MOVE_SPEED = 100.0f;

	GameObject *m_bulletManager;
	Sound *m_se;

};
