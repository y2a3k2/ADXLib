#pragma once
#include<string>

class GameObject;
class Component {

public:
	Component() { m_enable = true; };
	Component(GameObject *body) { m_enable = true, m_body = body; }
	virtual ~Component() {};

	virtual void Awake() {};
	virtual void Update() {};
	virtual void Draw() {};

	// 有効ならtrue
	bool IsEnable() { return m_enable; }

	// 有効にする
	bool SetEnable() { m_enable = true; }

	// 無効にする
	bool SetDisable() { m_enable = false; }

	// 本体のレイヤーを返す
	int GetLayer();

	// レイヤー(描写順)を変える
	void SetLayer(int layer);

protected:
	GameObject* m_body;	// アタッチしている本体

private:
	bool m_enable;		// そのコンポーネントが有効かどうか

};
