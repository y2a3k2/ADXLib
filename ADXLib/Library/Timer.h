#pragma once

///<summary>
///	���Ԃ��v������N���X
///	���̊֐��̏������ԂȂǂ��v������ꍇ�Ɏg����
///</summary>
class Timer {

public:
	Timer();
	virtual~Timer();
	
	// �������Ԃ����Z�b�g����
	void Reset();

	// Start����̌o�ߎ���(�b)��Ԃ�
	float GetSecond();

private:
	int m_startTime;	// ����J�n���̎���


};
