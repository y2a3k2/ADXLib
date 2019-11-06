#include "AppManager.h"

#include <DxLib.h>
#include <Config.h>
#include <SystemManager.h>
#include <SceneManager/SceneManager.h>

AppManager::AppManager() {

}

AppManager::~AppManager() {

}

AppManager * AppManager::GetInstance() {

	static AppManager *instance = nullptr;

	if (!instance) {
		instance = new AppManager();
	}

	return instance;
}

void AppManager::Initalize() {

	SetOutApplicationLogValidFlag(FALSE);			// ログの生成をしない

	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	switch (SCREEN_TYPE) {

	case 0:
		SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);	// 画面サイズと色の変更
		SetDrawArea(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); // 描写範囲
		ChangeWindowMode(TRUE);							// スクリーン設定。
		break;

	case 1:
		SetGraphMode(x, y, 32);							// 画面サイズと色の変更
		SetDrawArea(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); // 描写範囲
		ChangeWindowMode(TRUE);							// スクリーン設定。
		break;

	case 2:
		SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);	// 画面サイズと色の変更
		SetDrawArea(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); // 描写範囲
		ChangeWindowMode(FALSE);						// スクリーン設定。
		break;
	}

	SetWindowInitPosition(0, 0);					// ウインドウの初期座標を指定する
	SetWindowSizeChangeEnableFlag(TRUE);			// 画面サイズの変更を可能に
	SetAlwaysRunFlag(TRUE);							// ウインドウが非アクティブでも起動を止めない。
	SetUseZBuffer3D(TRUE);							// Ｚバッファを有効にする
	SetWriteZBuffer3D(TRUE);						// Ｚバッファへの書き込みを有効にする
	SetDrawScreen(DX_SCREEN_BACK);					// 描写先を裏画面にする

	srand(NULL);

	// システムの管理人を生成する
	SystemInstance->Initialize();
}

void AppManager::Update() {

	SystemInstance->FirstUpdate();
	SystemInstance->Update();
	SystemInstance->LastUpdate();
}

void AppManager::Draw() {

	clsDx();						// 前フレームの簡易文字列を消す。
	ClearDrawScreen();				// 前フレームの描写を消す。
	SystemInstance->Draw();
	ScreenFlip();					// 裏画面を表画面に反映
}
