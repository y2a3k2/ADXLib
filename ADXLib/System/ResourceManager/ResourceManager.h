#pragma once
#include<GameObject.h>
#include<Library.h>

/*未完成*/

///<summary>
///ロードしたデータを使いまわすため、保持するシングルトン
///</summary>
class ResourceManager : public GameObject {

public:
	ResourceManager();
	~ResourceManager();

	static ResourceManager *GetInstance();

	// 画像データをロード
	int LoadGraph(char *fileName);					

	// モデルデータをロード
	int LoadModel(char *fileName);

	// サウンドデータをロード
	int LoadSound(char *fileName);

private:
	struct RESOURCE_DATA {
		std::string name;	// ファイル名
		int originHandle;	// オリジナルのハンドル
	};

	std::list<RESOURCE_DATA> m_graphList;
	std::list<RESOURCE_DATA> m_modelList;
	std::list<RESOURCE_DATA> m_soundList;

};
