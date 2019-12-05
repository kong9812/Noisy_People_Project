//===================================================================================================================================
//【Result.h】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/09/20
// [更新日]2019/12/05
//===================================================================================================================================
#pragma once

//===================================================================================================================================
//【インクルード】
//===================================================================================================================================
#include "AbstractScene.h"
#include "ResultUI.h"
#include "StaticMeshRenderer.h"
//#include "Sprite.h"
//#include "UIResult.h"
//#include "SceneEffect.h"

//===================================================================================================================================
//【名前空間】
//===================================================================================================================================
namespace resultNS
{
	const D3DXQUATERNION CAMERA_RELATIVE_QUATERNION =	D3DXQUATERNION(0.0f, 300.0f, -300.0f, 0.0f);
	const float			 CAMERA_SPEED				= 30.0f;
}

//===================================================================================================================================
//【リザルトシーンクラス】
//===================================================================================================================================
class Result :public AbstractScene
{
private:
	ResultUI resultUI;

	//フィールド
	Object*							testField;			//フィールド
	StaticMeshRenderer*				testFieldRenderer;	//フィールドレンダラー


public:
	Result(void);
	~Result(void);
	virtual void initialize() override;
	virtual void uninitialize(void) override;
	virtual void update(float _frameTime) override;
	virtual void render() override;
	virtual void collisions(void) override;
	virtual void AI(void) override;

	void render3D(Camera currentCamera);
	void renderUI();

#ifdef _DEBUG
	virtual void createGUI() override;
#endif
};