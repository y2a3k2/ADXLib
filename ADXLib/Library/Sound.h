#pragma once
#include<Component.h>

// ���ׂẲ��ʂ𕽓��ɉ�����
const float ALL_VOLUME = 1.0f;

class Sound : public Component {

public:
	Sound();
	Sound(GameObject *body);
	virtual	~Sound();
	virtual void Load(const char* fileName);

	// �����Đ�����(��~���Ȃ�r������)
	virtual void Play();
	// �����ŏ�����Đ�����
	virtual void Replay();
	// �������[�v������
	virtual void LoopPlay();
	// ���̍Đ����~�߂�
	virtual void Stop();

	// ���ʂ�ς���(0�`1)
	void SetVolume(float volume);

protected:
	void Unload();

protected:
	int m_handle;

};