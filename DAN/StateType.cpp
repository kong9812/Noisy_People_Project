//-----------------------------------------------------------------------------
// ステート種類 [StateType.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/11/3
//-----------------------------------------------------------------------------
#include "StateMachine.h"
#include "StateType.h"
using namespace stateMachineNS;

//=============================================================================
// 追跡状態からの遷移
//=============================================================================
State* ChaseState::transition(stateMachineNS::TransitionTimeChecker* checker, int enemyType)
{
	if (checker[PATROL].executable)
	{ 
		return PatrolState::getInstance();
	}

	return this;
}


//=============================================================================
// 警戒状態からの遷移
//=============================================================================
State* PatrolState::transition(stateMachineNS::TransitionTimeChecker* checker, int enemyType)
{
	if (checker[CHASE].executable)
	{
		return ChaseState::getInstance();
	}

	return this;
}


//=============================================================================
// 休憩状態からの遷移
//=============================================================================
State* RestState::transition(stateMachineNS::TransitionTimeChecker* checker, int enemyType)
{
	return this;
}


//=============================================================================
// 死亡状態からの遷移
//=============================================================================
State* DieState::transition(stateMachineNS::TransitionTimeChecker* checker, int enemyType)
{
	return this;
}
