//===================================================================================================================================
//�yFinaleEffect.cpp�z
// [�쐬��] HAL����GP12A332 11 ���� ��
// [�쐬��] 2019/12/23
// [�X�V��] 2019/12/23
//===================================================================================================================================

//===================================================================================================================================
//�y�C���N���[�h�z
//===================================================================================================================================
#include "FinaleEffect.h"

//===================================================================================================================================
//�yusing�錾�z
//===================================================================================================================================
using namespace FinaleEffectNS;

//===================================================================================================================================
//�y�R���X�g���N�^�z
//===================================================================================================================================
FinaleEffect::FinaleEffect()
{
	//�t�����[�G�t�F�N�g
	flowerObj = new Object();
	flowerObj->initialize(&D3DXVECTOR3(0, 0, 0));
	distanceFlower  = 15.0f;
	//�H�G�t�F�N�g
	featherObj = new Object();
	featherObj->initialize(&D3DXVECTOR3(0, 0, 0));
	distanceFeather = 15.0f;
}


//===================================================================================================================================
//�y�f�X�g���N�^�z
//===================================================================================================================================
FinaleEffect::~FinaleEffect()
{
	SAFE_DELETE(flowerObj);
	SAFE_DELETE(featherObj);
}

//===================================================================================================================================
//�y�X�V�z
//===================================================================================================================================
void FinaleEffect::update(Camera* camera)
{
	//�t�����[�G�t�F�N�g
	flowerObj->position =  camera->position + camera->getDirectionZ()*distanceFlower;
	flowerObj->postureControl(flowerObj->getAxisX()->direction, -camera->getDirectionZ(),0.1f);
	flowerObj->update();
	//�H�G�t�F�N�g
	featherObj->position =  camera->position + camera->getDirectionZ()*distanceFeather;
	featherObj->postureControl(featherObj->getAxisX()->direction, -camera->getDirectionZ(),0.01f);
	featherObj->update();
}

//===================================================================================================================================
//�y�Đ��z
//===================================================================================================================================
void FinaleEffect::play()
{
	//�Ԃт�G�t�F�N�g�̍Đ�
	flowerShower = new FlowerShower(&flowerObj->matrixWorld);
	effekseerNS::play(0, flowerShower);
	//�H�G�t�F�N�g�̍Đ�
	feather = new Feather(&featherObj->matrixWorld);
	effekseerNS::play(0, feather);
}

#ifdef _DEBUG

//===================================================================================================================================
//�y�Đ��z
//===================================================================================================================================
void FinaleEffect::play(int i)
{
	switch (i)
	{
	case 0:
		//�Ԃт�G�t�F�N�g�̍Đ�
		flowerShower = new FlowerShower(&flowerObj->matrixWorld);
		break;
	case 1:
		//�H�G�t�F�N�g�̍Đ�
		feather = new Feather(&featherObj->matrixWorld);
		break;
	case 2:
		flowerShower = new DigitMode(&flowerObj->matrixWorld);
		break;
	case 3:
		flowerShower = new DigitMode(&flowerObj->matrixWorld);
		break;
	case 4:
		flowerShower = new DigitalShiftEffect(&flowerObj->matrixWorld);
		break;
	case 5:
		flowerShower = new SkyJumpEffect(&flowerObj->matrixWorld);
		break;
	case 6:
		flowerShower = new SkyVisionEffect(&flowerObj->matrixWorld);
		break;
	case 7:
		flowerShower = new ShiftTerminateEffect(&flowerObj->matrixWorld);
		break;
	case 8:
		flowerShower = new DigitaTreeNearEffect(&flowerObj->matrixWorld);
		break;

	}
	effekseerNS::play(0, flowerShower);

}
#endif // _DEBUG

