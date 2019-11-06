#include "SingletonObject.h"
#include <SystemManager.h>

SingletonObject::SingletonObject()
	:m_initialized(0) {
}

SingletonObject::SingletonObject(SingletonObject * singleton)
	: m_initialized(0) {
	SystemManager::GetInstance()->Push(singleton);
}

SingletonObject::~SingletonObject() {

}
