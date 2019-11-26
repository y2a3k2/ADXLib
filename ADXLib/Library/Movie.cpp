#include "Movie.h"
#include<assert.h>
#include<DxLib.h>
#include<ComponentManager/ComponentManager.h>
#include<ResourceManager/ResourceManager.h>

Movie::Movie()
	:Component() {
	m_handle = -1;
}

Movie::Movie(GameObject * body)
	: Component(body) {
	m_handle = -1;
	ComponentManager::GetInstance()->PushDraw(this);
}

Movie::~Movie() {

	Unload();
	ComponentManager::GetInstance()->EraseDraw(this);
}

void Movie::Draw() {

	// ���g���Ȃ����
	if (m_handle == -1) {
		int handle = ResourceManager::GetInstance()->GetGraphHandle(m_fileName.c_str());
		// ���[�h�o���Ă��Ȃ��Ȃ�
		if (handle == -1) {
			return;
		}
		m_handle = handle;
	}
	PlayMovieToGraph(m_handle);
}

void Movie::Load(const char * fileName) {

	// ���g������Ȃ��ɍ폜
	if (m_handle != -1) {
		Unload();
	}
	m_fileName = fileName;
	ResourceManager::GetInstance()->PushLoadGraph(fileName);
}

inline void Movie::Unload(){

	if (m_handle == -1) {
		return;
	}
	ResourceManager::GetInstance()->DeleteGraphHandle(m_fileName.c_str());
	m_handle = -1;
}
