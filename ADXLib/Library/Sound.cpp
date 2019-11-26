#include "Sound.h"
#include <DxMath.h>
#include <assert.h>
#include <GameObject.h>
#include<ComponentManager/ComponentManager.h>
#include<ResourceManager/ResourceManager.h>

Sound::Sound()
	:Component() {
	m_state = STATE::NONE;
	m_handle = -1;
	m_initVolume = 0.5f;
}

Sound::Sound(GameObject * body)
	: Component(body) {
	m_state = STATE::NONE;
	m_handle = -1;
	m_initVolume = 0.5f;
	ComponentManager::GetInstance()->PushUpdate(this);
}

Sound::~Sound() {

	Unload();
	ComponentManager::GetInstance()->EraseUpdate(this);
}

void Sound::Update() {

	// �܂��n���h�����Ȃ��Ȃ�
	if (m_handle == -1) {
		int handle = ResourceManager::GetInstance()->GetSoundHandle(m_fileName.c_str());
		// �n���h�����󂯎�ꂽ��
		if (handle != -1) {
			m_handle = handle;
			ChangeVolumeSoundMem(DxMath::Lerp(0, 255, m_initVolume * ALL_VOLUME), m_handle);
			switch (m_state) {
			case Sound::PLAY:	Play();			break;
			case Sound::REPLAY:	Replay();		break;
			case Sound::LOOP:	LoopPlay();		break;
			}
			m_state = STATE::NONE;
		}
	}
}

void Sound::Load(const char* fileName, bool quickly) {

	// ���g������Ȃ����
	if (m_handle != -1) {
		Unload();
	}

	// ����
	if (quickly) {
		m_fileName = fileName;
		int handle = ResourceManager::GetInstance()->LoadSound(fileName);

		// �n���h������ꂽ��
		if (handle != -1) {
			m_handle = handle;
			ChangeVolumeSoundMem(DxMath::Lerp(0, 255, m_initVolume * ALL_VOLUME), m_handle);
			switch (m_state) {
			case Sound::PLAY:	Play();			break;
			case Sound::REPLAY:	Replay();		break;
			case Sound::LOOP:	LoopPlay();		break;
			}
			m_state = STATE::NONE;
		}
	}
	else {
		m_fileName = fileName;
		ResourceManager::GetInstance()->PushLoadSound(fileName);
	}
}

void Sound::Play() {

	// �܂��n���h�����Ȃ��Ȃ�
	if (m_handle == -1) {
		m_state = STATE::PLAY;
		return;
	}

	// �Đ����Ȃ疳��
	if (CheckSoundMem(m_handle)) {
		return;
	}
	PlaySoundMem(m_handle, DX_PLAYTYPE_BACK, false);
}

void Sound::Replay() {

	// �܂��n���h�����Ȃ��Ȃ�
	if (m_handle == -1) {
		m_state = STATE::REPLAY;
		return;
	}
	PlaySoundMem(m_handle, DX_PLAYTYPE_BACK, true);
}

void Sound::LoopPlay() {

	// �܂��n���h�����Ȃ��Ȃ�
	if (m_handle == -1) {
		m_state = STATE::LOOP;
		return;
	}
	// �Đ����Ȃ疳��
	if (CheckSoundMem(m_handle)) {
		return;
	}
	PlaySoundMem(m_handle, DX_PLAYTYPE_LOOP, true);
}

void Sound::Stop() {

	// �܂��n���h�����Ȃ��Ȃ�
	if (m_handle == -1) {
		return;
	}
	// �Đ����Ă��Ȃ��Ȃ疳��
	if (!CheckSoundMem(m_handle)) {
		return;
	}
	StopSoundMem(m_handle);
}

void Sound::SetVolume(float volume) {

	if (m_handle == -1) {
		m_initVolume = volume;
		return;
	}
	ChangeVolumeSoundMem(DxMath::Lerp(0, 255, volume * ALL_VOLUME), m_handle);
}

void Sound::Unload() {

	// ���g���Ȃ��Ȃ疳��
	if (m_handle == -1) {
		return;
	}
	// �Đ����Ȃ�~�߂�
	if (CheckSoundMem(m_handle)) {
		StopSoundMem(m_handle);
	}
	DeleteSoundMem(m_handle);
	ResourceManager::GetInstance()->DeleteSoundHandle(m_fileName.c_str());
	m_handle = -1;
}
