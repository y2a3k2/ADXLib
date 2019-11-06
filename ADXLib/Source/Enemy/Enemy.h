#include"GameObject.h"

class Enemy : public GameObject{

public:
	Enemy();
	virtual ~Enemy();

	void Initialize()override;
	void Update()override;

	void OnCollisionEnter(GameObject *collider)override;

private:

};
