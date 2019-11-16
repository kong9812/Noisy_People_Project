//-----------------------------------------------------------------------------
// メタAIイベント生成クラス [EventMaker.cpp]
// Author : HAL東京昼間部 2年制ゲーム学科 GP12A332 32 中込和輝
// 作成開始日 : 2019/10/12
//-----------------------------------------------------------------------------
#include "AIDirector.h"
#include "EventMaker.h"
using namespace aiNS;


//=============================================================================
// 初期化
//=============================================================================
void EventMaker::initialize(aiNS::AnalyticalData* _data,
	OperationGenerator* _opeGenerator, GameMaster* _gameMaster, Player* _player, EnemyManager* _enemyManager,
	TreeManager* _treeManager, ItemManager* _itemManager, TelopManager* _telopManager)
{
	data = _data;
	opeGenerator = _opeGenerator;
	gameMaster = _gameMaster;
	player = _player;
	enemyManager = _enemyManager;
	treeManager = _treeManager;
	itemManager = _itemManager;
	telopManager = _telopManager;
}


//=============================================================================
// 終了処理
//=============================================================================
void EventMaker::uninitialize()
{
}


//=============================================================================
// 更新処理
//=============================================================================
void EventMaker::update()
{
	//// エネミー動的作成イベントの作成
	//if (enemyAD->shouldSpawnFuzzily > FUZZY_VALUE_SHOULD_SPAWN)
	//{
	//	makeEventSpawningEnemyAroundPlayer();
	//}
}


//=============================================================================
// エネミー動的作成イベントの作成（SPAWN_ENEMY_AROUND_PLAYER)
//=============================================================================
void EventMaker::makeEventSpawningEnemyAroundPlayer()
{
	enemyNS::ENEMYSET enemySet;
	enemySet.enemyID = enemyManager->issueNewEnemyID();
	enemySet.type = enemyNS::WOLF;
	enemySet.defaultPosition = *player[0].getPosition() + D3DXVECTOR3((float)(rand() % 5), 0.0f,(float)(rand() % 5));
	enemySet.defaultDirection = *player[0].getPosition() - enemySet.defaultPosition;
	enemySet.defaultState = stateMachineNS::PATROL;
	opeGenerator->spawnEnemyAroundPlayer(enemySet);
}