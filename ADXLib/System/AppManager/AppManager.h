#pragma once

class AppManager {

public:
	static AppManager *GetInstance();

	void Initalize();
	void Update();
	void Draw();

private:
	AppManager();
	~AppManager();

};
