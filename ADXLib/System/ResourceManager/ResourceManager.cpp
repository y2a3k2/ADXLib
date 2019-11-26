#include "ResourceManager.h"
#include<assert.h>
#include<Timer.h>
#include<Config.h>

ResourceManager * ResourceManager::GetInstance() {

	static ResourceManager *inst = nullptr;

	if (inst == nullptr) {
		inst = new ResourceManager();
	}
	return inst;
}

void ResourceManager::Update() {

	if ((int)m_loadList.size() == 0) {
		return;
	}

	Timer timer;
	int count = 0;

	auto &list = m_loadList;
	for (auto it = list.begin(); it != list.end(); it++) {
		// 時間が一定以上かかったなら中断
		if (timer.GetSecond() > RESOURCE_SECOND) {
			break;
		}
		auto type = (*it).type;
		int handle = -1;

		switch (type) {
		case ResourceManager::GRAPH:	handle = DxLib::LoadGraph((*it).name.c_str());		break;
		case ResourceManager::MODEL:	handle = MV1LoadModel((*it).name.c_str());			break;
		case ResourceManager::SOUND:	handle = LoadSoundMem((*it).name.c_str());			break;
		}
		assert(handle != -1);
		m_resourceList[type].push_back(RESOURCE_DATA((*it).name, handle));
		count++;
	}

	// ロード済みのものをlistから消す
	for (int i = 0; i < count; i++) {
		m_loadList.pop_front();
	}

	if ((int)m_loadList.size() == 0) {
		m_loadCount = 0;
	}
}

void ResourceManager::PushLoadGraph(const char * fileName) {

	// ロード済みなら無視
	if (IsLoaded(m_resourceList[RESOURCE_TYPE::GRAPH], fileName)) {
		return;
	}
	// ロード中なら無視
	if (IsLoading(fileName)) {
		return;
	}
	m_loadList.push_back(LOAD_DATA(fileName, RESOURCE_TYPE::GRAPH));
	m_loadCount++;
}

void ResourceManager::PushLoadModel(const char * fileName) {

	// ロード済みなら無視
	if (IsLoaded(m_resourceList[RESOURCE_TYPE::MODEL], fileName)) {
		return;
	}
	// ロード中なら無視
	if (IsLoading(fileName)) {
		return;
	}
	m_loadList.push_back(LOAD_DATA(fileName, RESOURCE_TYPE::MODEL));
	m_loadCount++;
}

void ResourceManager::PushLoadSound(const char * fileName) {

	// ロード済みなら無視
	if (IsLoaded(m_resourceList[RESOURCE_TYPE::SOUND], fileName)) {
		return;
	}
	// ロード中なら無視
	if (IsLoading(fileName)) {
		return;
	}
	m_loadList.push_back(LOAD_DATA(fileName, RESOURCE_TYPE::SOUND));
	m_loadCount++;
}

int ResourceManager::LoadGraph(const char * fileName) {

	auto &list = m_resourceList[RESOURCE_TYPE::GRAPH];

	for each (auto li in list) {
		// 既にロードしていたなら
		if (li.name == fileName) {
			li.copyCount++;
			return li.handle;
		}
	}
	int handle = DxLib::LoadGraph(fileName);
	assert(handle != -1);
	list.push_back(RESOURCE_DATA(fileName, handle));
	return handle;
}

int ResourceManager::LoadModel(const char * fileName) {

	auto &list = m_resourceList[RESOURCE_TYPE::MODEL];

	for each (auto li in list) {
		// 既にロードしていたなら
		if (li.name == fileName) {
			li.copyCount++;
			return MV1DuplicateModel(li.handle);
		}
	}
	int handle = MV1LoadModel(fileName);
	assert(handle != -1);
	list.push_back(RESOURCE_DATA(fileName, handle));
	return MV1DuplicateModel(handle);
}

int ResourceManager::LoadSound(const char * fileName) {

	auto &list = m_resourceList[RESOURCE_TYPE::SOUND];

	for each (auto li in list) {
		// 既にロードしていたなら
		if (li.name == fileName) {
			li.copyCount++;
			return DuplicateSoundMem(li.handle);
		}
	}
	int handle = LoadSoundMem(fileName);
	assert(handle != -1);
	list.push_back(RESOURCE_DATA(fileName, handle));
	return handle;
}

int ResourceManager::GetGraphHandle(const char * fileName) {

	for each (auto li in m_resourceList[RESOURCE_TYPE::GRAPH]) {
		if (li.name == fileName) {
			li.copyCount++;
			return li.handle;
		}
	}
	return -1;
}

int ResourceManager::GetModelHandle(const char * fileName) {

	for each (auto li in m_resourceList[RESOURCE_TYPE::MODEL]) {
		if (li.name == fileName) {
			li.copyCount++;
			return MV1DuplicateModel(li.handle);
		}
	}
	return -1;
}

int ResourceManager::GetSoundHandle(const char * fileName) {

	for each (auto li in m_resourceList[RESOURCE_TYPE::SOUND]) {
		if (li.name == fileName) {
			li.copyCount++;
			return DuplicateSoundMem(li.handle);
		}
	}
	return -1;
}

void ResourceManager::DeleteGraphHandle(const char * fileName) {

	auto &list = m_resourceList[RESOURCE_TYPE::GRAPH];

	for (auto it = list.begin(); it != list.end(); it++) {
		// 同名が見つかったら
		if ((*it).name == fileName) {
			// コピー数が0以下なら
			if ((*it).copyCount <= 0) {
				DeleteGraph((*it).handle);
				list.erase(it);
				return;
			}
			else {
				(*it).copyCount--;
				return;
			}
		}
	}
	assert(false);
}

void ResourceManager::DeleteModelHandle(const char * fileName) {

	auto &list = m_resourceList[RESOURCE_TYPE::MODEL];

	for (auto it = list.begin(); it != list.end(); it++) {
		// 同名が見つかったら
		if ((*it).name == fileName) {
			// コピー数が0以下なら
			if ((*it).copyCount <= 0) {
				MV1DeleteModel((*it).handle);
				list.erase(it);
				return;
			}
			else {
				(*it).copyCount--;
				return;
			}
		}
	}
	assert(false);
}

void ResourceManager::DeleteSoundHandle(const char * fileName) {

	auto &list = m_resourceList[RESOURCE_TYPE::SOUND];

	for (auto it = list.begin(); it != list.end(); it++) {
		// 同名が見つかったら
		if ((*it).name == fileName) {
			// コピー数が0以下なら
			if ((*it).copyCount <= 0) {
				DeleteSoundMem((*it).handle);
				list.erase(it);
				return;
			}
			else {
				(*it).copyCount--;
				return;
			}
		}
	}
	assert(false);
}

bool ResourceManager::IsCoroutine() {

	return ((int)m_loadList.size() != 0);
}

float ResourceManager::GetLoadPercent() {

	// 何もロードしないなら
	if ((int)m_loadCount == 0) {
		return 1.0f;
	}
	// ロードする必要はあるが、まだ何もロードできていないなら
	else if (m_loadCount == 0) {
		return 0.0f;
	}
	//	return  (float)m_loadCount / (float)m_loadList.size();
	return 1.0f - (float)m_loadList.size() / (float)m_loadCount;
}

ResourceManager::ResourceManager()
	:SingletonObject(this) {
	m_loadCount = 0;
}

ResourceManager::~ResourceManager() {

	for each (auto var in m_resourceList[RESOURCE_TYPE::GRAPH]) {
		DeleteGraph(var.handle);
	}
	for each (auto var in m_resourceList[RESOURCE_TYPE::MODEL]) {
		MV1DeleteModel(var.handle);
	}
	for each (auto var in m_resourceList[RESOURCE_TYPE::SOUND]) {
		DeleteSoundMem(var.handle);
	}
}

bool ResourceManager::IsLoaded(std::list<RESOURCE_DATA>& list, const char * name) {

	// ロード済みなら
	for each (auto li in list) {
		if (li.name == name) {
			return true;
		}
	}
	return false;
}

bool ResourceManager::IsLoading(const char * name) {

	// ロード中なら
	for each(auto li in m_loadList) {
		if (li.name == name) {
			return true;
		}
	}
	return false;
}
