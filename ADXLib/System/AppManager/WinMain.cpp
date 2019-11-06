#include <DxLib.h>
#include"AppManager/AppManager.h"
#include"TimeManager/TimeManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	auto &app = *AppManager::GetInstance();
	app.Initalize();

	// DXライブラリ初期化
	if (DxLib_Init() == -1) {
		return -1;
	}

	auto time = TimeManager::GetInstance();

	// ウィンドウが閉じられたorESCを押したらループを抜ける
	while ((ProcessMessage() == 0) && (!CheckHitKey(KEY_INPUT_ESCAPE))) {
		time->Start();
		app.Update();
		app.Draw();
		time->Wait();
	}

	// DXライブラリ使用の終了
	DxLib_End();

	return 0;
}
