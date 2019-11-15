//-----------------------------------------------------------------------------
// メタAIイベント生成クラス [GameMaker.h]
// Author : HAL東京昼間部 2年制ゲーム学科 GP12A332 32 中込和輝
// 作成開始日 : 2019/10/12
//-----------------------------------------------------------------------------
#pragma once
#include "OperationGenerator.h"

//=============================================================================
// 名前空間
//=============================================================================
namespace aiNS
{
	// 前方宣言
	struct AnalyticalData;

	// エネミー動的作成イベントの作成（SPAWN_ENEMY_AROUND_PLAYER)
	const float FUZZY_VALUE_SHOULD_SPAWN = 0.8f;
}


//=============================================================================
//クラス定義
//=============================================================================
class EventMaker
{
private:
	aiNS::AnalyticalData* data;

	OperationGenerator* opeGenerator;

	GameMaster* gameMaster;				// ゲーム管理オブジェクト
	Player* player;						// プレイヤー
	EnemyManager* enemyManager;			// エネミー管理オブジェクト
	TreeManager* treeManager;			// ツリー管理オブジェクト
	ItemManager* itemManager;			// アイテム管理オブジェクト
	TelopManager* telopManager;			// テロップ管理オブジェクト

public:
	void initialize(aiNS::AnalyticalData* data, OperationGenerator* _opeGenerator,
		GameMaster* _gameMaster, Player* _player, EnemyManager* _enemyManager,
		TreeManager* _treeManager, ItemManager* _itemManager, TelopManager* _telopManager);

	void uninitialize();
	void update();
	void makeEventSpawningEnemyAroundPlayer();
};
