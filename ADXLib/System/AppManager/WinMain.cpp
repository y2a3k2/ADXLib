#include <DxLib.h>
#include"AppManager/AppManager.h"
#include"TimeManager/TimeManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	auto &app = *AppManager::GetInstance();
	app.Initalize();

	// DX���C�u����������
	if (DxLib_Init() == -1) {
		return -1;
	}

	auto time = TimeManager::GetInstance();

	// �E�B���h�E������ꂽorESC���������烋�[�v�𔲂���
	while ((ProcessMessage() == 0) && (!CheckHitKey(KEY_INPUT_ESCAPE))) {
		time->Start();
		app.Update();
		app.Draw();
		time->Wait();
	}

	// DX���C�u�����g�p�̏I��
	DxLib_End();

	return 0;
}
