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

	// 中身があるなら消す
	if (m_handle != -1) {
		Unload();
	}

	m_handle = LoadSoundMem(fileName);
	assert(m_handle != -1);
	SetVolume(0.5f);
}

void Sound::Play() {

	// 中身がないのに鳴らそうとしたら
	assert(m_handle != -1);

	// 再生中なら無視
	if (CheckSoundMem(m_handle)) {
		return;
	}

	PlaySoundMem(m_handle, DX_PLAYTYPE_BACK, false);
}

void Sound::Replay() {

	// 中身がないのに鳴らそうとしたら
	assert(m_handle != -1);

	PlaySoundMem(m_handle, DX_PLAYTYPE_BACK, true);
}

void Sound::LoopPlay() {

	// 中身がないのに鳴らそうとしたら
	assert(m_handle != -1);

	// 再生中なら無視
	if (CheckSoundMem(m_handle)) {
		return;
	}

	PlaySoundMem(m_handle, DX_PLAYTYPE_LOOP, true);
}

void Sound::Stop() {

	// 中身がないのに止めようとしたら
	assert(m_handle != -1);

	// 再生していないなら無視
	if (!CheckSoundMem(m_handle)) {
		return;
	}
	StopSoundMem(m_handle);
}

void Sound::SetVolume(float volume) {

	ChangeVolumeSoundMem(DxMath::Lerp(0, 255, volume * ALL_VOLUME), m_handle);
}

void Sound::Unload() {

	// 中身がないなら無視
	if (m_handle == -1) {
		return;
	}
	// 再生中なら止める
	if (CheckSoundMem(m_handle)) {
		StopSoundMem(m_handle);
	}
	DeleteSoundMem(m_handle);
	m_handle = -1;
}
