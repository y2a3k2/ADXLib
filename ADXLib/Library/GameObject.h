#pragma once
#include<DxLib.h>
#include<list>

#include<Transform.h>
#include<Component.h>

#include<DebugManager/DebugManager.h>
#include<InputManager/InputManager.h>
#include<TimeManager/TimeManager.h>

class GameObject {

public:
	GameObject();
	GameObject(std::string name);
	virtual ~GameObject();

	// 初期化(非推奨)	コンストラクタの後に呼ばれる　CreateObject<T>()→GameObject()→Awake()の順
	virtual void Awake() {}
	// 初期化	初回Updateで呼ばれる
	virtual void Initialize() {}
	// 更新		表示前に毎フレーム呼ばれる
	virtual void Update() {}

	// 衝突時に呼ばれる関数	引数には衝突したオブジェクトが入る(当たり判定そのものではない)
	virtual void OnCollisionEnter(GameObject *object) {}

	// Initializeが呼ばれているならtrue
	virtual bool IsInitialized() { return m_state.initialized; }
	// Initializeが呼ばれた
	virtual void UsedInitialize() { m_state.initialized = true; }
	// Updateを許可するか
	virtual bool IsEnable() { return m_state.enable; }
	// Updateを有効にする
	virtual void SetEnable() { m_state.enable = true; }
	// Updateを無効にする
	virtual void SetDisable() { m_state.enable = false; }
	// 消すならtrue
	bool IsDead() { return m_state.dead; }

	// オブジェクトの名前を返す
	std::string GetName() { return m_objectName; };
	// 親のポインタを返す
	GameObject *GetParent() { return m_parent; };
	// 子オブジェクトのリストを返す
	std::list<GameObject*> &GetChildList() { return m_childList; };
	// オブジェクトのタグを返す
	int GetTag() { return m_state.tag; }
	// 自分の位置、回転、拡縮のパラメーターを返す
	Transform &GetTransform() { return m_transform; }
	// レイヤーを返す
	int GetLayer() { return m_state.layer; };

	// オブジェクトの名前を変更する
	void SetName(const char *name) { m_objectName = name; }
	// オブジェクトのタグを入れる
	void SetTag(int tag) { m_state.tag = tag; }
	// レイヤーを変更する
	void SetLayer(int layer);

	// 自身の子に新しいオブジェクトを生成する
	template <typename T> T *CreateObject() {
		auto t = new T();
		((GameObject*)t)->m_parent = this;
		m_childList.push_back(t);
		t->Awake();
		return t;
	}

	// 新しいコンポーネントを追加する
	template <typename T> T *AddComponent() {
		auto t = new T(this);
		m_componentList.push_back(t);
		t->Awake();
		return t;
	}
	// コンポーネントを削除する
	template <typename T> void SubComponent() {
		for (auto it = m_componentList.begin(); it != m_componentList.end(); it++) {
			// 指定されたものと同じ型なら返す
			auto p = dynamic_cast<T*>((*it));
			if (p != nullptr) {
				return p;
			}
		}
	}
	// コンポ―メントを検索する
	template <typename T> T* GetComponent() {
		for (auto it = m_componentList.begin(); it != m_componentList.end(); it++) {
			// 指定されたものと同じ型なら返す
			auto p = dynamic_cast<T*>((*it));
			if (p != nullptr) {
				return p;
			}
		}
		// なければnullを返す
		return nullptr;
	}

	// 子オブジェクトを検索
	GameObject* Search(std::string name) {
		for (auto it = m_childList.begin(); it != m_childList.end(); it++) {
			if ((*it)->m_objectName == name) {
				return (*it);
			}
			auto p = (*it)->Search(name);
			if (p != nullptr) {
				return p;
			}
		}
		return nullptr;
	};

	// 名前で指定した子オブジェクトを消す
	void ChildDestroy(std::string name) {
		auto obj = Search(name);
		if (obj != nullptr)
			delete obj;
	}

	// 親を別オブジェクトに変える
	void SetParent(GameObject *parent) {
		auto par = GetParent();
		// 親がいるなら先に親の子リストから外れる
		if (par != nullptr) {
			auto list = par->GetChildList();
			for (auto it = list.begin(); it != list.end(); it++) {
				// 自分を撤去
				if ((*it) == this) {
					list.erase(it);
					break;
				}
			}
		}
		// 親無し(一番上)になるならrootの子にする
		if (parent == nullptr) {
			m_parent = GetRoot();
			GetRoot()->GetChildList().push_back(this);
		}

		else {
			m_parent = parent;
			parent->GetChildList().push_back(this);
		}
	}

	// 一番上の階層
	static GameObject *GetRoot();
	// 入力関係
	static InputManager *GetInput();
	// デバック関係
	static DebugManager *GetDebug();
	// 時間関係
	static TimeManager *GetTime();

	// オブジェクトやコンポーネントを消去する
	void Destroy() { m_state.dead = true; };
	void Destroy(Component* comp);

protected:
	struct STATE {
		STATE() { ZeroMemory(this, sizeof(this)); }
		unsigned initialized : 1;	// trueなら初期化済み
		unsigned dead : 1;			// trueなら消す
		unsigned enable : 1;		// trueじゃなければ動かさない
		int layer;					// 描写順(数値の低いものから描写)
		int tag;					// オブジェクトのタグ
	};

private:
	GameObject* m_parent;
	STATE m_state;
	Transform m_transform;
	std::string m_objectName;
	std::list<GameObject*> m_childList;
	std::list<Component*> m_componentList;

};
