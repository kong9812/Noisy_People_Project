//===================================================================================================================================
//【Game.h】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/09/20
// [更新日]2019/10/05
//===================================================================================================================================
#pragma once

//===================================================================================================================================
//【インクルード】
//===================================================================================================================================
#include <vector>
#include "AbstractScene.h"
#include "Player.h"
#include "StaticMeshObject.h"
#include "InstancingBillboard.h"
#include "EnemyManager.h"
#include "AIDirector.h"
#include "NavigationMesh.h"
#include "TreeManager.h"
#include "ItemManager.h"
#include "Telop.h"


//#include "GameMaster.h"
//#include "PointSprite.h"

//#include "Object.h"
//#include "Text.h"

//===================================================================================================================================
//【名前空間】
//===================================================================================================================================
namespace gameNS
{

	//プレイヤー初期位置
	const D3DXVECTOR3 PLAYER_POSITION =	D3DXVECTOR3(0,100,0);

	//カメラ相対位置
	//const D3DXQUATERNION CAMERA_RELATIVE_QUATERNION = D3DXQUATERNION(0.0f,20.0f,-40.0f,0.0f);
	const D3DXQUATERNION CAMERA_RELATIVE_QUATERNION = D3DXQUATERNION(0.0f,3.0f,-5.0f,0.0f);

	//カメラ相対注視位置
	const D3DXVECTOR3 CAMERA_RELATIVE_GAZE = D3DXVECTOR3(0,0,0);

	//const int NUM_SAMPLE = 1000;

}

//===================================================================================================================================
//【ゲームシーンクラス】
//===================================================================================================================================
class Game : public AbstractScene
{
private:

	//Text text;					//Sample
	//Text text2;					//Sample
	//PointSprite pointSprite;		//Sample
	//InstancingBillboard plane;	//Sample
	//Object testObject;			//Sample
	//Object testCube;				//Sample

	//プレイヤー
	Player *player;

	//フィールド
	StaticMeshObject* testField;	

	//インスタンシングビルボードテスト
	InstancingBillboard instancingBillboardTest;

	// エネミー
	EnemyManager enemyManager;
	Enemy* enemy;

	// ツリー
	TreeManager* treeManager;

	// アイテム
	ItemManager* itemManager;

	// テロップ
	Telop* telop;

	// AI
	AIDirector* aiDirector;
	NavigationMesh* naviAI;

public:
	Game();
	~Game();
	virtual void initialize() override;
	virtual void update(float frameTime) override;
	virtual void render() override;
	virtual void collisions() override;
	virtual void AI() override;
	virtual void uninitialize() override;

	void render3D(Camera currentCamera);
	void renderUI();

#ifdef _DEBUG
	virtual void createGUI() override;
#endif
};


//===================================================================================================================================
//【ビルドスイッチ】
//===================================================================================================================================
#ifdef _DEBUG

#if 1	// ここを1でナビメッシュデバッグモード
#define DEBUG_NAVIMESH
#endif

#endif// _DEBUG