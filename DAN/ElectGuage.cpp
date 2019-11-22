//===================================
//�d�̓Q�[�W����[ElectGuage.cpp]
//����W��
//===================================

//===================================
//�C���N���[�h
//===================================
#include "ElectGuage.h"

//===================================
// usuing�錾
//===================================
using namespace electGuageNS;

//===================================
//�R���X�g���N�^
//===================================
ElectGuage::ElectGuage()
{
	electGuage = new Sprite;
	width = WIDTH_EN_GUAGE;
}

//===================================
//�f�X�g���N�^
//===================================
ElectGuage::~ElectGuage()
{
	delete electGuage;
}

//===================================
//������
//===================================
void ElectGuage::initialize(int playerType)
{
	switch (playerType)
	{
	case basicUiNS::P1:
		BasicUI::assingSize(WIDTH_EN_GUAGE, HEIGHT_EN_GUAGE);
		BasicUI::assingPosition(POSITION_EN_GUAGE);
		BasicUI::changePivot(SpriteNS::TOP_LEFT);
		BasicUI::initialize(electGuage, textureNS::reference(textureNS::UI_EN_GUAGE_P1));
		break;
	case basicUiNS::P2:
		BasicUI::assingSize(WIDTH_EN_GUAGE, HEIGHT_EN_GUAGE);
		BasicUI::assingPosition(POSITION_EN_GUAGE_P2);
		BasicUI::changePivot(SpriteNS::TOP_RIGHT);
		BasicUI::initialize(electGuage, textureNS::reference(textureNS::UI_EN_GUAGE_P2));
		break;

	}
}

//===================================
//�`��
//===================================
void ElectGuage::render()
{
	electGuage->render();
}

//===================================
//�X�V
//�����F�d��
//===================================
void ElectGuage::update(int power)
{
	changeGuage(power);
}

//===================================
//�Q�[�W�̕ω�����
//�����F���݂̓d��
//===================================
void ElectGuage::changeGuage(int power)
{
	//�d�͂̉�2�������o��
	int  enPersent = power % 100;
	if (BasicUI::widthSize > WIDTH_EN_GUAGE*enPersent)
	{
		BasicUI::reductionWidthSize(electGuage, 1.0);
	}
	else if (enPersent == 0)//0�̎��̓Q�[�W��MAX
	{
		BasicUI::changeWhidthSize(electGuage, WIDTH_EN_GUAGE);
	}
}