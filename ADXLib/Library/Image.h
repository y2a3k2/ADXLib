#pragma once
#include<DxMath.h>
#include<Component.h>

///<summary>
///	2D�摜�̕\���p�N���X
///	�P���ȕ\�������ł����A�ό`�����邱�Ƃ͕s�\
///	UI��ꖇ�G��\�����鎞�ɏ������y���\���ł���
///</summary>

class Transform;
class Image : public Component {

public:
	Image();
	Image(GameObject *body);
	virtual	~Image();
	virtual	void Draw()override;

	// �t�@�C�������[�h����(��������true�𑗂�Ƒ����Ƀ��[�h����)
	virtual	void Load(const char *fileName, bool quickly = false);
	// �摜�̒��S�_��ύX����
	void SetCenter(int cx, int cy);
	// �摜�̐F�̒l�����炷
	void SetColor(unsigned char red, unsigned char green, unsigned char blue);
	// �摜�̓����x��K�����邩�ǂ���(�����l��true)
	void SetTrans(bool flag);

	// �m�[�u�����h�i�f�t�H���g�j
	void SetBlendDefault();
	// ���u�����h
	void SetBlendAlpha(unsigned char pal);
	// ���Z�u�����h
	void SetBlendAdd(unsigned char pal);
	// ���Z�u�����h
	void SetBlendSub(unsigned char pal);
	// ��Z�u�����h
	void SetBlendMula(unsigned char pal);
	// ���]�u�����h
	void SetBlendInvsrc(unsigned char pal);
	// ��Z�ς݃��p�̃��u�����h
	void SetBlendPmaAlpha(unsigned char pal);
	// ��Z�ς݃��p�̉��Z�u�����h
	void SetBlendPmaAdd(unsigned char pal);
	// ��Z�ς݃��p�̌��Z�u�����h
	void SetBlendPmaSub(unsigned char pal);
	// ��Z�ς݃��p�̔��]�u�����h
	void SetBlendPmaInvsrc(unsigned char pal);

	// �摜�̃T�C�Y
	const INT_VECTOR2 &GetSize();
	// �摜��World���W
	VECTOR GetWorldPosition();

	// �摜�̃��[�J�����W����
	void SetPosition(VECTOR pos);
	// �摜�̃��[�J����]����
	void SetRotation(VECTOR rot);
	// �摜�̃��[�J���g�k����
	void SetScale(VECTOR sca);

protected:
	// �摜������
	inline void Unload();

protected:
	int m_handle;				// �O���t�B�b�N�n���h��
	INT_VECTOR2 m_center;		// �摜�̒��S
	INT_VECTOR2 m_size;			// �摜�̃T�C�Y
	COLOR m_color;				// �摜�̐F(�f�t�H���g��255,255,255)
	bool m_trans;				// �摜�̓��ߐF�𔽉f���邩
	int m_blendMode;			// �u�����h���[�h
	unsigned char m_blendPal;	// �u�����h�̋���
	std::string m_fileName;		// �t�@�C����
	Transform *m_transform;		// �����␳���������ꍇ�Ɏg�����ߑł��p

	bool m_isCenterInit;	// ���S�_�����炩���ߏ��������Ă������ǂ���

};
