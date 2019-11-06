#pragma once
#include<Component.h>

///<summary>
///	�����\���p�N���X
///</summary>
class Text : public Component {

public:
	Text();
	Text(GameObject *body);
	virtual	~Text();

	virtual	void Draw()override;

	// �\������������������
	void SetText(const char* text);
	void SetText(const std::string &text);

	// �����̐F��ς���
	void SetColor(int red,  int green, int blue);

	/*
	�t�H���g�����(thick��0�`9�܂ŁA���ꂼ�������-1������ƃf�t�H���g�ݒ�ɂȂ�)
	DX_FONTTYPE_NORMAL�@�@�@�@�@�@�@�@�@: �m�[�}���t�H���g
	DX_FONTTYPE_EDGE�@�@�@�@�@�@�@�@�@�@: �G�b�W���t�H���g
	DX_FONTTYPE_ANTIALIASING�@�@�@�@�@�@: �A���`�G�C���A�X�t�H���g
	DX_FONTTYPE_ANTIALIASING_4X4�@�@�@�@: �A���`�G�C���A�X�t�H���g(4x4�T���v�����O)
	DX_FONTTYPE_ANTIALIASING_8X8�@�@�@�@: �A���`�G�C���A�X�t�H���g(8x8�T���v�����O)
	DX_FONTTYPE_ANTIALIASING_EDGE_4X4�@ : �A���`�G�C���A�X���G�b�W�t���t�H���g(4x4�T���v�����O)
	DX_FONTTYPE_ANTIALIASING_EDGE_8X8�@ : �A���`�G�C���A�X���G�b�W�t���t�H���g(8x8�T���v�����O) )
	*/
	void CreateFontHandle(int size = -1, int thick = -1, int fontType = -1);

	// �쐬�����t�H���g��ǂݍ��ݎg�p����(�t�@�C�����A���̑���)
	void LoadFontHandle(const char* fileName, int edgeSize);

private:
	int m_fontHandle;		// �e�L�X�g�̃n���h��
	int m_colorHandle;		// �F�̃n���h��
	std::string m_text;		// �\������e�L�X�g

};
