//-----------------------------------------------------------------------------
// ベアークラス [Bear.cpp]
// Author : HAL東京昼間部 2年制ゲーム学科 GP12A332 32 中込和輝
// 作成開始日 : 2019/10/21
//-----------------------------------------------------------------------------
#include "Bear.h"
using namespace enemyNS;
using namespace stateMachineNS;


//=============================================================================
// コンストラクタ
//=============================================================================
Bear::Bear(StaticMesh* _staticMesh, EnemyData* _enemyData): Enemy(_staticMesh, _enemyData)
{
}


//=============================================================================
// デストラクタ
//=============================================================================
Bear::~Bear()
{

}


//=============================================================================
// 更新処理
//=============================================================================
void Bear::update(float frameTime)
{
	Enemy::preprocess(frameTime);
	switch (enemyData->state)
	{
	case CHASE:  chase();  break;
	case PATROL: patrol(); break;
	case REST:   rest();   break;
	case DIE:    die();    break;
	}
	Enemy::update(frameTime);
}


//=============================================================================
// 追跡ステート
//=============================================================================
void::Bear::chase()
{

}


//=============================================================================
// 警戒ステート
//=============================================================================
void::Bear::patrol()
{

}


//=============================================================================
// 休憩ステート
//=============================================================================
void::Bear::rest()
{

}


//=============================================================================
// 死亡ステート
//=============================================================================
void::Bear::die()
{

}


//=============================================================================
// Getter
//=============================================================================


//=============================================================================
// Setter
//=============================================================================
