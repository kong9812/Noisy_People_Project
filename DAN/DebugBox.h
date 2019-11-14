//===================================================================================================================================
//【DebugBox.h】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/11/14
// [更新日]2019/11/14
//===================================================================================================================================
#pragma once

//===================================================================================================================================
//【インクルード】
//===================================================================================================================================
#include "Base.h"

class DebugBox :public Base
{
public:
	LPD3DXMESH	mesh;		//メッシュ
public:
	DebugBox(D3DXVECTOR3 size);
	~DebugBox();
	void render(D3DXMATRIX worldMatrix);
};

