//===================================================================================================================================
//【Sky.h】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/10/20
// [更新日]2019/10/20
//===================================================================================================================================
#pragma once

//===================================================================================================================================
//【インクルード】
//===================================================================================================================================
#include "Object.h"
#include "StaticMeshObject.h"

namespace skyNS
{
	const int NUM = 1;
}

//===================================================================================================================================
//【スカイクラス】
//===================================================================================================================================
class Sky :	public Base
{
private:
	StaticMeshObject* renderer;
	bool needUpdate;
public:
	Sky();
	~Sky();
	void initialize();
	void update();
	void render(D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);
	void generate(D3DXVECTOR3 position);
};

