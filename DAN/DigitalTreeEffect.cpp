//===================================================================================================================================
//�yDigitalTreeEffect.cpp�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/11/25
// [�X�V��]2019/11/25
//===================================================================================================================================

//===================================================================================================================================
//�y�C���N���[�h�z
//===================================================================================================================================
#include "DigitalTreeEffect.h"
#include "TextureLoader.h"

//===================================================================================================================================
//�yusing�錾�z
//===================================================================================================================================
using namespace DigitalTreeEffectNS;

//===================================================================================================================================
//�y�C���X�^���X�N���X�F�R���X�g���N�^�z
//===================================================================================================================================
EffectInstance::EffectInstance(D3DXVECTOR3 position) : InstancingBillboardNS::Instance()
{
	//�����l�̐ݒ�
	this->position	= position + D3DXVECTOR3((float)(rand() % 6 - 3), 0.0f, (float)(rand() % 6 - 3));
	
	//rotation = D3DXVECTOR3((float)(rand() % 20 - 10), (float)(rand() % 20 - 10), (float)(rand() % 20 - 10));
	rotation = D3DXVECTOR3(0, 0, 0);
	//instance.scale				= D3DXVECTOR2((float)(rand() % 20 + 1), (float)(rand() % 20 + 1));
	scale = D3DXVECTOR2(1.0f, 1.0f);
	speed = D3DXVECTOR3(0, 3.0f, 0.0f);
	color = D3DCOLOR_RGBA(64, rand() % 255, rand() % 255, 0);
	limitTime = (float)(rand() % 30);
	//uv.x = 0.25f*sinf(limitTime * 4);
	//uv.y = 0.25f*cosf(limitTime * 4);
}
//===================================================================================================================================
//�y�C���X�^���X�N���X�F�X�V�z
//===================================================================================================================================
void EffectInstance::update(float frameTime)
{
	lifeTimer += frameTime;
	if (lifeTimer >= limitTime)return;
	//�J���[
	//color.r = sinf(lifeTimer * 8);
	color.g = cosf(lifeTimer * 4);
	color.b = sinf(limitTime);
	color.a = 1.0f - (lifeTimer / limitTime);

	//UV
	float time = limitTime - lifeTimer;
	uv.x = 0.25f*sinf(time * 1.5);
	uv.y = 0.25f*cosf(time * 0.5);
	
	//�ʒu
	position += speed * frameTime;
}


//===================================================================================================================================
//�y�R���X�g���N�^�z
//===================================================================================================================================
DigitalTreeEffect::DigitalTreeEffect()
{
	billboard = new InstancingBillboard();
	billboard->initialize(*textureNS::reference(textureNS::LIGHT_001));

}

//===================================================================================================================================
//�y�f�X�g���N�^�z
//===================================================================================================================================
DigitalTreeEffect::~DigitalTreeEffect()
{
	SAFE_DELETE(billboard);
}

//===================================================================================================================================
//�y�X�V�z
//===================================================================================================================================
void DigitalTreeEffect::update(float frameTime)
{
	//�X�V
	billboard->update(frameTime);

}

//===================================================================================================================================
//�y�����z
//===================================================================================================================================
void DigitalTreeEffect::generateInstance(D3DXVECTOR3 position)
{
	billboard->generateInstance(new EffectInstance(position));//�C���X�^���X�̐���
}

//===================================================================================================================================
//�y�`��z
//===================================================================================================================================
void DigitalTreeEffect::render(D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	//�`��
	billboard->render(view,projection,cameraPosition);

}


