#include "DebugManager.h"
#include "Config.h"

DebugManager * DebugManager::GetInstance() {

	static DebugManager *inst = nullptr;

	if (inst == nullptr) {
		inst = new DebugManager();
	}

	return inst;
}

void DebugManager::Update() {

}

void DebugManager::Draw() {

#if DEBUG
	const int COLOR = GetColor(255, 255, 255);
	const int SPACE = 16;

	int line = 0;
	for each (auto text in m_textList) {
		DrawFormatString(0, line * SPACE, COLOR, text.c_str());
		line++;
	}
	m_textList.clear();
#endif
}

void DebugManager::SetLog(const char * text, ...) {

	const int MAX = 1024;

	va_list ap;
	va_start(ap, text);
	char buffer[MAX];
	vsprintf_s<MAX>(buffer, text, ap);
	va_end(ap);

	std::string s;

	for (int i = 0; i < MAX; i++) {
		// ‹ó‚É‚È‚Á‚½‚çŽ~‚ß‚é
		if (buffer[i] == '\0')
			break;
		s.push_back(buffer[i]);
	}
	m_textList.push_back(s);
}

DebugManager::DebugManager()
	:SingletonObject(this) {
}

DebugManager::~DebugManager() {

}
