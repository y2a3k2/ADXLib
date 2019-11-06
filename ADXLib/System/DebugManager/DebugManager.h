#pragma once
#include<SingletonObject.h>
#include<string>
#include<list>

class DebugManager : public SingletonObject {

public:
	static DebugManager *GetInstance();

	void Update()override;
	void Draw()override;

	// 画面左上にテキストを表示する(半角1024文字,全角512文字まで)
	void SetLog(const char *text, ...);

private:
	DebugManager();
	~DebugManager();

private:
	std::list<std::string> m_textList;

};
