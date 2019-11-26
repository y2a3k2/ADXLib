#pragma once
#include<stdio.h>
#include<string>

///	<summary>
///	�\���̂��Z�[�u����B���߂Ƀt�@�C���K�w�����Ȃ���Ύg���Ȃ�
///	</summary>
template<typename T> class StructSave {

public:
	StructSave(const char *fileName) { m_fileName = fileName; }
	virtual	~StructSave() {};

	// ��������
	void Write(const T &t) {
		FILE *pFile;
		T data = t;
		// �t�@�C�����J���Ȃ����
		if (fopen_s(&pFile, m_fileName.c_str(), "w") != 0) {
			// �t�@�C����V�K�쐬
			fopen_s(&pFile, m_fileName.c_str(), "w+");
		}
		fwrite(&t, sizeof(T), 1, pFile);		// SaveData�\���̂̒��g���������݁B
		fclose(pFile);							// �t�@�C�������
	}

	// �ǂݎ��
	T Read() {
		FILE *pFile;
		T data;
		// �t�@�C�����J���Ȃ����
		if (fopen_s(&pFile, m_fileName.c_str(), "r") != 0) {
			// �t�@�C����V�K�쐬
			fopen_s(&pFile, m_fileName.c_str(), "w+");
		}
		fread(&data, sizeof(T), 1, pFile);		// fread���Ə������݁B
		fclose(pFile);							// �t�@�C�������
		return data;
	}

private:
	std::string m_fileName;

};
