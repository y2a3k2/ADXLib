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

	switch (SCREEN_TYPE) {

	case 0:
		SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);	// ��ʃT�C�Y�ƐF�̕ύX
		SetDrawArea(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); // �`�ʔ͈�
		ChangeWindowMode(TRUE);							// �X�N���[���ݒ�B
		break;

	case 1:
		SetGraphMode(x, y, 32);							// ��ʃT�C�Y�ƐF�̕ύX
		SetDrawArea(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); // �`�ʔ͈�
		ChangeWindowMode(TRUE);							// �X�N���[���ݒ�B
		break;

	case 2:
		SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);	// ��ʃT�C�Y�ƐF�̕ύX
		SetDrawArea(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); // �`�ʔ͈�
		ChangeWindowMode(FALSE);						// �X�N���[���ݒ�B
		break;
	}

	SetWindowInitPosition(0, 0);					// �E�C���h�E�̏������W���w�肷��
	SetWindowSizeChangeEnableFlag(TRUE);			// ��ʃT�C�Y�̕ύX���\��
	SetAlwaysRunFlag(TRUE);							// �E�C���h�E����A�N�e�B�u�ł��N�����~�߂Ȃ��B
	SetUseZBuffer3D(TRUE);							// �y�o�b�t�@��L���ɂ���
	SetWriteZBuffer3D(TRUE);						// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetDrawScreen(DX_SCREEN_BACK);					// �`�ʐ�𗠉�ʂɂ���

	srand(NULL);

	// �V�X�e���̊Ǘ��l�𐶐�����
	SystemInstance->Initialize();
}

void AppManager::Update() {

	SystemInstance->FirstUpdate();
	SystemInstance->Update();
	SystemInstance->LastUpdate();
}

void AppManager::Draw() {

	clsDx();						// �O�t���[���̊ȈՕ�����������B
	ClearDrawScreen();				// �O�t���[���̕`�ʂ������B
	SystemInstance->Draw();
	ScreenFlip();					// ����ʂ�\��ʂɔ��f
}
