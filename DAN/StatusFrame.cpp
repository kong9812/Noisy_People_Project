//=====================================
//�X�^�b�c�t���[������[StatusFrame.cpp]
//����W��
//=====================================

//=====================================
//�C���N���[�h
//=====================================
#include "StatusFrame.h"

//=====================================
// using�錾
//=====================================
using namespace statusFrameNS;

//=====================================
//�R���X�g���N�^
//=====================================
StatusFrame::StatusFrame()
{
	//�X�v���C�g�̍쐬
	statusFrame = new Sprite;
}

//=====================================
//�f�X�g���N�^
//=====================================
StatusFrame::~StatusFrame()
{
	delete statusFrame;
}

//=====================================
//������
//=====================================
void StatusFrame::initialize()
{
	//�����ʒu�̑��
	BasicUI::assingPosition(POSITION_STATUSFLAME01);

	//�����T�C�Y�̑��
	BasicUI::assingSize(WIDTH_STATUSFLAME, HEIGHT_STATUSFLAME);

	//�e�N�X�`���̎w��
	BasicUI::initialize(statusFrame, textureNS::reference(textureNS::UI_STATUSFRAME_P1));
}

//=====================================
//�`��
//=====================================
void StatusFrame::render()
{
	statusFrame->render();
}

//=====================================
//�X�V
//=====================================
void StatusFrame::update()
{

}