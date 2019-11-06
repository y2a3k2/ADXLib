#pragma once
#include<SceneID.h>
#include<SingletonObject.h>

class GameObject;
class SceneManager : public SingletonObject {

public:
	static SceneManager *GetInstance();

	void Initialize()override;
	void Update()override;

	void Change(SCENE_ID scene);

	SCENE_ID GetNextScene();

private:
	SceneManager();
	~SceneManager();

	void StartScene();
	void SceneChangeProcess();

	GameObject *m_scene;
	SCENE_ID m_nowScene;
	SCENE_ID m_nextScene;
};
