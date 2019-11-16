//-----------------------------------------------------------------------------
// タイガークラス [Tiger.cpp]
// Author : HAL東京昼間部 2年制ゲーム学科 GP12A332 32 中込和輝
// 作成開始日 : 2019/10/21
//-----------------------------------------------------------------------------
#include "Tiger.h"
using namespace enemyNS;
using namespace stateMachineNS;

//=============================================================================
// コンストラクタ
//=============================================================================
Tiger::Tiger(StaticMesh* _staticMesh, EnemyData* _enemyData): Enemy(_staticMesh, _enemyData)
{
	setSize(D3DXVECTOR3(1.0f, 2.9, 1.0f));
}


//=============================================================================
// デストラクタ
//=============================================================================
Tiger::~Tiger()
{

}


//=============================================================================
// 更新処理
//=============================================================================
void Tiger::update(float frameTime)
{
	Enemy::preprocess(frameTime);
	switch (enemyData->state)
	{
	case CHASE:  chase(frameTime);  break;
	case PATROL: patrol(frameTime); break;
	case REST:   rest(frameTime);   break;
	case DIE:    die(frameTime);    break;
	}
	Enemy::update(frameTime);
}


//=============================================================================
// 追跡ステート
//=============================================================================
void::Tiger::chase(float frameTime)
{
	Enemy::chase(frameTime);

	float distance = between2VectorLength(position, *movingTarget);

	if (distance < 7.0f && canAttack)
	{
		shouldAttack = true;
	}
}


//=============================================================================
// 警戒ステート
//=============================================================================
void::Tiger::patrol(float frameTime)
{
	Enemy::patrol(frameTime);

	if (onGround && isArraved || isDestinationLost)
	{
		setDebugDestination();		// デバッグ用目的地を設定
		isDestinationLost = false;	// 目的地はロストしていない
		shouldSearch = true;		// パスサーチ実行
	}
}


//=============================================================================
// 休憩ステート
//=============================================================================
void::Tiger::rest(float frameTime)
{

}


//=============================================================================
// ツリー攻撃ステート
//=============================================================================
void Tiger::attackTree(float frameTime)
{
	Enemy::attackTree(frameTime);
}


//=============================================================================
// 死亡ステート
//=============================================================================
void::Tiger::die(float frameTime)
{
	Enemy::die(frameTime);
}


//=============================================================================
// Getter
//=============================================================================


//=============================================================================
// Setter
//=============================================================================
