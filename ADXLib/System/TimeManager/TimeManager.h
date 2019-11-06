#pragma once
#include<SingletonObject.h>

const int DRAW_WAIT = 60;	// FPS�̐��x

class TimeManager : public SingletonObject {

public:
	static TimeManager* GetInstance();

	void Initialize()override;
	void Update()override;

	// �t���[���Ԃ̎��ԑ���J�n
	void Start();

	// FPS�����ɕۂ��߂Ɏ~�߂�R�}���h(�����ČĂяo���Ȃ�����)
	void Wait();

	// ������Ă΂ꂽ���_�Ōv�Z���J�n����(���[�h�ɂ��fps�ቺ�ōŏ��̃t���[���̖\���h�~)
	void Reset();

	// ����FPS��Ԃ�
	float Getfps();

	// ���̃f���^�^�C����Ԃ�
	float GetDelta();

	// �����Ԃ�
	int GetYaer() { return m_dateData.Year; }

	// ����Ԃ�
	int GetMon() { return m_dateData.Mon; }

	// ���t��Ԃ�
	int GetDay() { return m_dateData.Day; }

	// ������Ԃ�
	int GetHour() { return m_dateData.Hour; }

	// ������Ԃ�
	int GetMin() { return m_dateData.Min; }

	// �b��Ԃ�
	int GetSec() { return m_dateData.Sec; }

private:
	TimeManager();
	~TimeManager();

	int m_timer;			// timer
	float m_fps;			// fps
	float m_delta;			// �f���^�^�C��
	DATEDATA m_dateData;	// ���ݎ���

	int m_count;		// �\���p�J�E���^
	float m_drawFps;
	float m_drawDelta;
};
