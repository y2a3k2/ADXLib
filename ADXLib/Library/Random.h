#pragma once

class Random {

	// �����_�����I�������ʁA����������true��Ԃ�(�ꐔ�̐�,������̐�)
	static	bool GetHit(int all, int win = 1);

	// ���̂����̓�����m�������߂�B�߂�l��1�`0(�ꐔ�̐�,������̐�)
	static	float GetProb(int all, int win = 1);

};
