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

	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);	// 画面サイズと色の変更
	SetDrawArea(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); // 描写範囲

	// フルスク
	if (SCREEN_TYPE == 2) {
		ChangeWindowMode(FALSE);
	}
	// それ以外
	else {
		int x = (SCREEN_TYPE == 0) ? WINDOW_WIDTH : GetSystemMetrics(SM_CXSCREEN);
		int y = (SCREEN_TYPE == 0) ? WINDOW_HEIGHT : GetSystemMetrics(SM_CYSCREEN);
		float xSize = ((float)x / (float)WINDOW_WIDTH);
		float ySize = ((float)y / (float)WINDOW_HEIGHT);
		SetWindowSizeExtendRate(min(xSize, ySize));
		ChangeWindowMode(TRUE);
	}

	SetWindowInitPosition(0, 0);					// ウインドウの初期座標を指定する
	SetWindowSizeChangeEnableFlag(TRUE);			// 画面サイズの変更を可能に
	SetAlwaysRunFlag(TRUE);							// ウインドウが非アクティブでも起動を止めない。
	SetUseZBuffer3D(TRUE);							// Ｚバッファを有効にする
	SetWriteZBuffer3D(TRUE);						// Ｚバッファへの書き込みを有効にする
	SetDrawScreen(DX_SCREEN_BACK);					// 描写先を裏画面にする

	srand(NULL);

	// システムの管理人を生成、初期化する
	SystemInstance->Initialize();
}

void AppManager::Update() {

	SystemInstance->FirstUpdate();	// 先行して行うUpdate
	SystemInstance->Update();		// 通常のUpdate
	SystemInstance->LastUpdate();	// 最後に行うUpdate
}

void AppManager::Draw() {

	clsDx();						// 前フレームの簡易文字列を消す。
	ClearDrawScreen();				// 前フレームの描写を消す。
	SystemInstance->Draw();			// 描画処理
	ScreenFlip();					// 裏画面を表画面に反映
}
