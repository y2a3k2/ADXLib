#include "Sound.h"
#include <DxMath.h>
#include <assert.h>
#include <GameObject.h>

Sound::Sound()
	:Component() {
	m_handle = -1;
}

Sound::Sound(GameObject * body)
	: Component(body) {
	m_handle = -1;
}

Sound::~Sound() {

	Unload();
}

void Sound::Load(const char* fileName) {

	// ���g������Ȃ����
	if (m_handle != -1) {
		Unload();
	}

	m_handle = LoadSoundMem(fileName);
	assert(m_handle != -1);
	SetVolume(0.5f);
}

void Sound::Play() {

	// ���g���Ȃ��̂ɖ炻���Ƃ�����
	assert(m_handle != -1);

	// �Đ����Ȃ疳��
	if (CheckSoundMem(m_handle)) {
		return;
	}

	PlaySoundMem(m_handle, DX_PLAYTYPE_BACK, false);
}

void Sound::Replay() {

	// ���g���Ȃ��̂ɖ炻���Ƃ�����
	assert(m_handle != -1);

	PlaySoundMem(m_handle, DX_PLAYTYPE_BACK, true);
}

void Sound::LoopPlay() {

	// ���g���Ȃ��̂ɖ炻���Ƃ�����
	assert(m_handle != -1);

	// �Đ����Ȃ疳��
	if (CheckSoundMem(m_handle)) {
		return;
	}

	PlaySoundMem(m_handle, DX_PLAYTYPE_LOOP, true);
}

void Sound::Stop() {

	// ���g���Ȃ��̂Ɏ~�߂悤�Ƃ�����
	assert(m_handle != -1);

	// �Đ����Ă��Ȃ��Ȃ疳��
	if (!CheckSoundMem(m_handle)) {
		return;
	}
	StopSoundMem(m_handle);
}

void Sound::SetVolume(float volume) {

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
	m_handle = -1;
}
