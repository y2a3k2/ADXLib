#include "Movie.h"
#include<assert.h>
#include<DxLib.h>
#include<ComponentManager/ComponentManager.h>

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

	// ’†g‚ª‚È‚¯‚ê‚Î
	if (m_handle == -1) {
		return;
	}

	PlayMovieToGraph(m_handle);
}

void Movie::Load(const char * fileName) {

	// ’†g‚ª‚ ‚é‚È‚çæ‚Éíœ
	if (m_handle != -1) {
		Unload();
	}
	m_handle = LoadGraph(fileName);
	assert(m_handle != -1);
}

inline void Movie::Unload(){

	if (m_handle == -1) {
		return;
	}
	DeleteGraph(m_handle);
	m_handle = -1;
}
