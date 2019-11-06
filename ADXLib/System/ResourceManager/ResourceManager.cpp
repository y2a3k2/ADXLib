#include "ResourceManager.h"

namespace {
	ResourceManager* instance = nullptr;

}

ResourceManager::ResourceManager()
	:GameObject("ResourceManager") {

	if (instance != nullptr) {
		Destroy();
		return;
	}
	instance = this;
}

ResourceManager::~ResourceManager() {

	for each (auto var in m_graphList) {
		DeleteGraph(var.originHandle);
	}
	for each (auto var in m_modelList) {
		MV1DeleteModel(var.originHandle);
	}
	for each (auto var in m_soundList) {
		DeleteSoundMem(var.originHandle);
	}
}

ResourceManager * ResourceManager::GetInstance() {

	return instance;
}

int ResourceManager::LoadGraph(char * fileName) {

	//for each (auto var in m_graphList) {
	//	if (var.name == fileName) {
	//	}
	//}

	return 0;
}

int ResourceManager::LoadModel(char * fileName) {

	for each (auto var in m_modelList) {
		if (var.name == fileName) {
			return MV1DuplicateModel(var.originHandle);
		}
	}
	return MV1LoadModel(fileName);
}

int ResourceManager::LoadSound(char * fileName) {

	for each (auto var in m_soundList) {
		if (var.name == fileName) {
			return DuplicateSoundMem(var.originHandle);
		}
	}
	return LoadSoundMem(fileName);
}
