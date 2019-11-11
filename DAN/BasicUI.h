//================================
// ��bUI�N���X�̒�`[BasicUI.h]
// ����@�W��
//================================
#pragma once

//================================
// �C���N���[�h
//================================
#include"TextureLoader.h"
#include "Sprite.h"

//================================
// ���O���
//================================
namespace basicUiNS
{
	//�ړ��̎��
	enum MOVE_TYPE
	{
		slideRight,
		slideLeft,
		slideUp,
		slideDown,
	};

	enum PLAYER_TYPE
	{
		P1,
		P2,
		PLAYER_TYPE_MAX,
	};

	const float SLIDE_SPEED = 20.0f;		//�X���C�h�C���̑��x
	const int	CHANGE_SIZE_SPEED = 20;		//�T�C�Y�ύX�̑��x
	const float   CHANGE_ALPHA_SPEED = 155.0f;		//���l�̕ύX���x
}

//================================
//�N���X��`
//================================
class BasicUI
{
public://�����o�[�ϐ�
	D3DXVECTOR3 position;	//�\���ʒu
	D3DXVECTOR3 rotation;	//��]
	D3DCOLOR	color;		//�F
	int widthSize;			//���̃T�C�Y
	int heightSize;			//�����T�C�Y
	float alphaValue;		//���l
	// uv���W�p�̕ϐ�
	D3DXVECTOR2 uvCoord01;
	D3DXVECTOR2 uvCoord02;
	D3DXVECTOR2 uvCoord03;
	D3DXVECTOR2 uvCoord04;

private:
public://�����o�[�֐�
	BasicUI();				//�R���X�g���N�^
	~BasicUI();				//�f�X�g���N�^
	void    initialize(Sprite *sprite, LPDIRECT3DTEXTURE9 *fileName);//������
	void	assingPosition(D3DXVECTOR3 pos);						//�\���ʒu�̑��
	void	assingRotation(D3DXVECTOR3 rot);						//��]�̑��
	void	assingColor(D3DCOLOR col);								//�F�̑��
	void	assingSize(int widh, int height);						//�T�C�Y�̑��
	void	changePostion(int movetype);//�ʒu�ύX	
	void	increaseAlpha(float alpha);//�����x����
	void	decreaseAlpha(float alpha);//�����x����
	void	expansionWidthSize(int speed);//���T�C�Y�̊g��
	void	expansionHeightSize(int speed);//�c�T�C�Y�̊g��
	void	reductionWidthSize(int speed);//���T�C�Y�̏k��
	void	reductionHeightSize(int speed);//�c�T�C�Y�̏k��

private:
};