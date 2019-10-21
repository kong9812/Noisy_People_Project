//-----------------------------------------------------------------------------
// ウルフクラス [Wolf.cpp]
// Author : HAL東京昼間部 2年制ゲーム学科 GP12A332 32 中込和輝
// 作成開始日 : 2019/10/21
//-----------------------------------------------------------------------------
#include "Wolf.h"
using namespace enemyNS;

//=============================================================================
// コンストラクタ
//=============================================================================
Wolf::Wolf(StaticMesh* _staticMesh, EnemyData* _enemyData): Enemy(_staticMesh, _enemyData)
{
}


//=============================================================================
// デストラクタ
//=============================================================================
Wolf::~Wolf()
{

}


//=============================================================================
// 更新処理
//=============================================================================
void Wolf::update(float frameTime)
{
	Enemy::update(frameTime);
}


//=============================================================================
// 追跡ステート
//=============================================================================
void::Wolf::chase()
{

}


//=============================================================================
// 警戒ステート
//=============================================================================
void::Wolf::patrol()
{

}


//=============================================================================
// 休憩ステート
//=============================================================================
void::Wolf::rest()
{

}


//=============================================================================
// 死亡ステート
//=============================================================================
void::Wolf::die()
{

}


//=============================================================================
// Getter
//=============================================================================


//=============================================================================
// Setter
//=============================================================================
