#pragma once
#include<SingletonObject.h>
#include<string>
#include<list>

///<summary>
///	ロードしたデータを効率的に使い回すためのシステム
///</summary>
class ResourceManager : public SingletonObject {

public:
	static ResourceManager *GetInstance();

	void Update()override;

	// 画像データをロード(コルーチン)
	void PushLoadGraph(const char *fileName);
	// モデルデータをロード(コルーチン)
	void PushLoadModel(const char *fileName);
	// サウンドデータをロード(コルーチン)
	void PushLoadSound(const char *fileName);

	// 画像データをロード
	int LoadGraph(const char *fileName);
	// モデルデータをロード
	int LoadModel(const char *fileName);
	// サウンドデータをロード
	int LoadSound(const char *fileName);

	// 画像データのハンドルをもらう
	int GetGraphHandle(const char *fileName);
	// モデルデータのハンドルをもらう
	int GetModelHandle(const char *fileName);
	// サウンドデータのハンドルをもらう
	int GetSoundHandle(const char *fileName);

	// 画像データのハンドルを消す
	void DeleteGraphHandle(const char *fileName);
	// モデルデータのハンドルを消す
	void DeleteModelHandle(const char *fileName);
	// サウンドデータのハンドルを消す
	void DeleteSoundHandle(const char *fileName);

	// コルーチンでロードをしているか
	bool IsCoroutine();
	//ロード完了率を返す
	float GetLoadPercent();

private:
	// リソース情報
	struct RESOURCE_DATA {
		RESOURCE_DATA() { name = "", handle = -1, copyCount = 0; };
		RESOURCE_DATA(std::string n, int h) { name = n, handle = h, copyCount = 0; };
		std::string name;	// ファイル名
		int handle;			// オリジナルのハンドル
		int copyCount;		// コピーの数
	};

	// リソース区分
	enum RESOURCE_TYPE {
		GRAPH, MODEL, SOUND, MAX,
	};

	struct LOAD_DATA {
		LOAD_DATA() {};
		LOAD_DATA(std::string n, RESOURCE_TYPE t) { name = n, type = t; }
		std::string name;		// ファイル名
		RESOURCE_TYPE type;		// 区分
	};

	ResourceManager();
	~ResourceManager();

	// ロード済みならtrueを返す
	bool IsLoaded(std::list<RESOURCE_DATA> &list, const char* name);
	// ロード中ならtrueを返す
	bool IsLoading(const char* name);

private:
	int m_loadCount;	// 何件ロードするのか
	std::list<LOAD_DATA> m_loadList;
	std::list<RESOURCE_DATA> m_resourceList[RESOURCE_TYPE::MAX];

};
