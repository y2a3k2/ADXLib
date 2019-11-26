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

	SetOutApplicationLogValidFlag(FALSE);			// ���O�̐��������Ȃ�

	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);	// ��ʃT�C�Y�ƐF�̕ύX
	SetDrawArea(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); // �`�ʔ͈�

	// �t���X�N
	if (SCREEN_TYPE == 2) {
		ChangeWindowMode(FALSE);
	}
	// ����ȊO
	else {
		int x = (SCREEN_TYPE == 0) ? WINDOW_WIDTH : GetSystemMetrics(SM_CXSCREEN);
		int y = (SCREEN_TYPE == 0) ? WINDOW_HEIGHT : GetSystemMetrics(SM_CYSCREEN);
		float xSize = ((float)x / (float)WINDOW_WIDTH);
		float ySize = ((float)y / (float)WINDOW_HEIGHT);
		SetWindowSizeExtendRate(min(xSize, ySize));
		ChangeWindowMode(TRUE);
	}

	SetWindowInitPosition(0, 0);					// �E�C���h�E�̏������W���w�肷��
	SetWindowSizeChangeEnableFlag(TRUE);			// ��ʃT�C�Y�̕ύX���\��
	SetAlwaysRunFlag(TRUE);							// �E�C���h�E����A�N�e�B�u�ł��N�����~�߂Ȃ��B
	SetUseZBuffer3D(TRUE);							// �y�o�b�t�@��L���ɂ���
	SetWriteZBuffer3D(TRUE);						// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetDrawScreen(DX_SCREEN_BACK);					// �`�ʐ�𗠉�ʂɂ���

	srand(NULL);

	// �V�X�e���̊Ǘ��l�𐶐��A����������
	SystemInstance->Initialize();
}

void AppManager::Update() {

	SystemInstance->FirstUpdate();	// ��s���čs��Update
	SystemInstance->Update();		// �ʏ��Update
	SystemInstance->LastUpdate();	// �Ō�ɍs��Update
}

void AppManager::Draw() {

	clsDx();						// �O�t���[���̊ȈՕ�����������B
	ClearDrawScreen();				// �O�t���[���̕`�ʂ������B
	SystemInstance->Draw();			// �`�揈��
	ScreenFlip();					// ����ʂ�\��ʂɔ��f
}
