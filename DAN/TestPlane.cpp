//===================================================================================================================================
//【TestPlane.cpp】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/10/29
// [更新日]2019/10/29
//===================================================================================================================================

//===================================================================================================================================
//【インクルード】
//===================================================================================================================================
#include "TestPlane.h"
#include "ShaderLoader.h"
#include "TextureLoader.h"

//===================================================================================================================================
//【using宣言】
//===================================================================================================================================
using namespace testPlaneNS;

//===================================================================================================================================
//【インスタンスクラス：コンストラクタ】
//===================================================================================================================================
TestPlaneInstance::TestPlaneInstance(D3DXVECTOR3 position) : InstancingBillboardNS::Instance()
{
	//初期値の設定
	this->position	= position;
	this->rotation	= D3DXVECTOR3(0, 0, D3DX_PI/4);
	this->scale		= D3DXVECTOR2(10.0f, 5.0f);
	this->speed		= D3DXVECTOR3(0, 0, 0);
	this->limitTime	= 1.0f;
	this->uv.x		= 0.125f*7;
	this->uv.y		= 0.125f*7;
}

//===================================================================================================================================
//【インスタンスクラス：更新】
//===================================================================================================================================
void TestPlaneInstance::update(float frameTime)
{
	//lifeTimer += frameTime;
	if (lifeTimer >= limitTime)return;
}

//===================================================================================================================================
//【コンストラクタ】
//===================================================================================================================================
TestPlane::TestPlane() :InstancingBillboard::InstancingBillboard()
{
	InstancingBillboard::initialize(*textureNS::reference(textureNS::COLOR_SCALE),7,7);

	generateInstance(new TestPlaneInstance(D3DXVECTOR3(0, 10, 30)));
	generateInstance(new TestPlaneInstance(D3DXVECTOR3(15, 10, 30)));
	generateInstance(new TestPlaneInstance(D3DXVECTOR3(-15, 10, 30)));

}

//===================================================================================================================================
//【デストラクタ】
//===================================================================================================================================
TestPlane::~TestPlane()
{
}

//===================================================================================================================================
//【更新】
//===================================================================================================================================
void TestPlane::update(float frameTime)
{
	InstancingBillboard::update(frameTime);
}
