//===================================================================================================================================
//�yDebugBox.h�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/11/14
// [�X�V��]2019/11/14
//===================================================================================================================================
#pragma once

//===================================================================================================================================
//�y�C���N���[�h�z
//===================================================================================================================================
#include "Base.h"

class DebugBox :public Base
{
public:
	LPD3DXMESH	mesh;		//���b�V��
public:
	DebugBox(D3DXVECTOR3 size);
	~DebugBox();
	void render(D3DXMATRIX worldMatrix);
};
