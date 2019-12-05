//===================================================================================================================================
//【GameMaster.cpp】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/09/20
// [更新日]2019/10/25
//===================================================================================================================================
#include "GameMaster.h"
#include "ImguiManager.h"
#include "Input.h"

//===================================================================================================================================
//【名前空間】
//===================================================================================================================================
namespace gameMasterNS
{
	Input* input = NULL;
}

//===================================================================================================================================
//【using宣言】
//===================================================================================================================================
using namespace gameMasterNS;

//===================================================================================================================================
//【コンストラクタ】
//===================================================================================================================================
GameMaster::GameMaster()
{
	gameTimer			= 0.0f;								//ゲーム時間
	countDownTimer		= 0.0f;								//カウントダウン時間
	for (int i = 0; i < gameMasterNS::PLAYER_NUM; i++)
	{
		ZeroMemory(&playerInformation[i], sizeof(PlayerTable));
	}
	treeNum				= 0;
	//conversionOrder		= NULL;
	input				= getInput();
	gameTimerStop		= false;
#ifdef _DEBUG
	showGUI = true;
#endif // _DEBUG
}

//===================================================================================================================================
//【デストラクタ】
//===================================================================================================================================
GameMaster::~GameMaster()
{
	//SAFE_DELETE_ARRAY(conversionOrder);
}

//===================================================================================================================================
//【初期化】
//===================================================================================================================================
void GameMaster::initialize()
{

}

//===================================================================================================================================
//【更新】
//===================================================================================================================================
void GameMaster::update(float frameTime)
{
	//ゲーム中ならば、ポーズ切り替え受付
	if (gameTimer > 0)
	{
		//スタートボタン/Ｐキーを入力された場合ポーズにする。
		if (input->wasKeyPressed('P') || 
			input->getController()[0]->wasButton(virtualControllerNS::SPECIAL_MAIN)||
			input->getController()[1]->wasButton(virtualControllerNS::SPECIAL_MAIN))
		{
			pause = !pause;
		}
#ifdef _DEBUG
		//タッチパッド(SUB)ボタン/Qキーを入力された場合ゲームタイマーを停止。
		if (input->wasKeyPressed('Q') ||
			input->getController()[0]->wasButton(virtualControllerNS::SPECIAL_SUB) ||
			input->getController()[1]->wasButton(virtualControllerNS::SPECIAL_SUB))
		{
			gameTimerStop = !gameTimerStop;
		}

#endif // _DEBUG


	}
}

//===================================================================================================================================
//【ポーズ処理】
//===================================================================================================================================
bool GameMaster::paused()
{
	return pause;
}

//===================================================================================================================================
//【ゲーム開始時処理】
//===================================================================================================================================
void GameMaster::startGame()
{
	gameTimer		= GAME_TIME;
	gameTimerStop	= false;
	pause = false;
	progress = 0x00000000;
	discardConversionOrder();
}

//===================================================================================================================================
//【ゲーム時間の更新】
//===================================================================================================================================
void GameMaster::updateGameTime(float frameTime)
{
	if (gameTimerStop)return;

	gameTimer -= frameTime;
}

//===================================================================================================================================
//【残り時間1分の更新】
//===================================================================================================================================
bool GameMaster::playActionRamaining1Min()
{
	if (gameTimer > 60)return false;
	if (whetherAchieved(PASSING_REMAINING_ONE_MINUTE))return false;

	setProgress(PASSING_REMAINING_ONE_MINUTE);

	return true;
}


#pragma region conversionOrderFunction
//===================================================================================================================================
//【緑化した木の本数を記録】
//===================================================================================================================================
void GameMaster::recordTreeTable(TreeTable treeTable)
{
	TreeTable data = treeTable;
	data.eventTime = GAME_TIME - gameTimer;
	treeTableList.insertFront(data);
	treeTableList.listUpdate();
}

//===================================================================================================================================
//【変換順番変数を準備する】
//===================================================================================================================================
void GameMaster::readyTreeTable() 
{

}

//===================================================================================================================================
//【変換順番変数を破棄する】
//===================================================================================================================================
void GameMaster::discardConversionOrder() {
	this->treeNum = 0;
	treeTableList.allClear();
}
#pragma endregion

//===================================================================================================================================
//【setter】
//===================================================================================================================================
void GameMaster::setConversionOrder(int* newValue) {} // conversionOrder = newValue; };
void GameMaster::setProgress(int achievement) { progress |= achievement; }

//===================================================================================================================================
//【getter】
//===================================================================================================================================
PlayerTable* GameMaster::getPlayerInfomation(){	return playerInformation;}	//プレイヤー情報の取得
float GameMaster::getGameTime() {return gameTimer;}							//ゲーム制限時間の取得
int GameMaster::getProgress() { return progress; }
bool GameMaster::whetherAchieved(int ahievement) { return progress & ahievement; }

//===================================================================================================================================
//【GUI】
//===================================================================================================================================
#ifdef _DEBUG
void GameMaster::createGUI()
{
	ImGui::Text("gameTime = %f",		gameTimer);
	ImGui::Text("countDownTimer = %f",	countDownTimer);
	ImGui::Text("TreeNum = %d",	treeNum);
	if (ImGui::CollapsingHeader("TreeTableList"))
	{
		ImGui::Text("listNum: %d ", treeTableList.nodeNum);
		
		for (int i = 0; i < treeTableList.nodeNum; i++)
		{
			if (ImGui::CollapsingHeader("TreeTable"))
			{
				TreeTable table = *treeTableList.getValue(i);
				ImGui::Text("No:[%d]",i);				
				ImGui::Text("TreeId = %d",table.id);
				ImGui::Text("PlayerNo:%d",table.player+1);
				ImGui::Text("EventTime = %.02f",table.eventTime);
				ImGui::Text("model = %d",table.modelType);
				ImGui::Text("position(%.02f,%.02f,%.02f)",table.position.x,table.position.y,table.position.z);
				ImGui::Text("rotation(%.02f,%.02f,%.02f,%.02f)",table.rotation.x,table.rotation.y,table.rotation.z,table.rotation.w);
				ImGui::Text("scale(%.02f,%.02f,%.02f)",table.scale.x,table.scale.y,table.scale.z);
				switch (table.eventType)
				{
				case EVENT_TYPE::TO_DEAD:				ImGui::Text("EVENT:TO_DEAD");					break;
				case EVENT_TYPE::TO_GREEN_WITH_ANALOG:	ImGui::Text("EVENT:TO_GREEN_WITH_ANALOG");		break;
				case EVENT_TYPE::TO_GREEN_WITH_DIGITAL:	ImGui::Text("EVENT:TO_GREEN_WITH_DIGITAL");		break;
				}
			}
		}
	}
}
#endif