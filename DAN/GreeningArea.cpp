//===================================================================================================================================
//�yGreeningArea.cpp�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/11/17
// [�X�V��]2019/11/17
//===================================================================================================================================

//===================================================================================================================================
//�y�C���N���[�h�z
//===================================================================================================================================
#include "GreeningArea.h"

//===================================================================================================================================
//�y�R���X�g���N�^�z
//===================================================================================================================================
GreeningArea::GreeningArea()
{
	{//�I�u�W�F�N�g�^�C�v�ƏՓˑΏۂ̎w��
		using namespace ObjectType;
		treeCell.type = GREENING_AREA;
		treeCell.target = TREE;
	}


}

//===================================================================================================================================
//�y�f�X�g���N�^�z
//===================================================================================================================================
GreeningArea::~GreeningArea()
{
}

//===================================================================================================================================
//�y�X�V�z
//===================================================================================================================================
void GreeningArea::update(float frameTime)
{

}

//===================================================================================================================================
//�y�`��z
//===================================================================================================================================
void GreeningArea::render()
{
	sphere->render();
}
