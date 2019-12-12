//-----------------------------------------------------------------------------
// パーツアニメーション基底クラス [PartsAnimation.cpp]
// Author : HAL東京昼間部 2年制ゲーム学科 GP12A332 32 中込和輝
// 作成開始日 : 2019/12/12
//-----------------------------------------------------------------------------
#include "PartsAnimation.h"

//=============================================================================
// コンストラクタ
//=============================================================================
PartsAnimation::PartsAnimation()
{
	initialize();
}


//=============================================================================
// デストラクタ
//=============================================================================
PartsAnimation::~PartsAnimation()
{

}


//=============================================================================
// 初期化
//=============================================================================
void PartsAnimation::initialize()
{
	animationTime = 0.0f;
	keyFrame = 0;
}


//=============================================================================
// 更新処理
//=============================================================================
void PartsAnimation::update(float t)
{
	animationTime += t;
	keyFrame = (int)animationTime;	// キーフレームに変換

	if (keyFrame + 1 == numKeyFrame)
	{
		initialize();
	}
}
