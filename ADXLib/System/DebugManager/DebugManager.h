#pragma once
#include<SingletonObject.h>
#include<string>
#include<list>

class DebugManager : public SingletonObject {

public:
	static DebugManager *GetInstance();

	void Update()override;
	void Draw()override;

	// ��ʍ���Ƀe�L�X�g��\������(���p1024����,�S�p512�����܂�)
	void SetLog(const char *text, ...);

private:
	DebugManager();
	~DebugManager();

private:
	std::list<std::string> m_textList;

};
