//-----------------------------------------------------------------------------
// エネミー管理クラス [Enemy.cpp]
// Author : HAL東京昼間部 2年制ゲーム学科 GP12A332 32 中込和輝
// 作成開始日 : 2019/10/4
//-----------------------------------------------------------------------------
#include "EnemyManager.h"
#include "ImguiManager.h"
using namespace enemyNS;


//=============================================================================
// 初期化
//=============================================================================
void EnemyManager::initialize()
{
	// ファイルからエネミー初期ステータスを読み込む
	FILE	*fp = NULL;
	fopen("enemy.enemy", "rb");

	ENEMY_FILE tmpEnemyFile;
	memset(&tmpEnemyFile, 0, sizeof(ENEMY_FILE));

	//ENMYの読み込み
	fread(&tmpEnemyFile.enmy, sizeof(ENEMY_ENMY), 1, fp);

	//メモリ確保
	tmpEnemyFile.efmt = new ENEMY_EFMT[tmpEnemyFile.enmy.enemyMax];

	//EFMTの読み込み
	fread(&tmpEnemyFile.efmt, sizeof(ENEMY_EFMT), tmpEnemyFile.enmy.enemyMax, fp);

	fclose(fp);

	// エネミーデータリストの追加
	EnemyData enemyData;
	enemyDataList.reserve(tmpEnemyFile.enmy.enemyMax);
	for (int i = 0; i < tmpEnemyFile.enmy.enemyMax; i++)
	{
		enemyData.clear();

		//enemyData.id = tmpEnemyFile.efmt->chunkId;

		enemyDataList.push_back(enemyData);
	}
	
	// エネミーオブジェクトの作成
	enemyList.reserve(INITIAL_RESERVE);
	for (size_t i = 0; enemyDataList.size(); i++)
	{
		if (/* プレイヤーの初期位置と近ければ */1)
		{
			createEnemy(&enemyDataList[i]);
		}
	}

	SAFE_DELETE_ARRAY(tmpEnemyFile.efmt);
}


//=============================================================================
// 終了処理
//=============================================================================
void EnemyManager::uninitialize()
{
	for (size_t i = 0; i < enemyList.size(); i++)
	{
		SAFE_DELETE(enemyList[i]);
	}

	std::vector<Enemy*> temp;
	enemyList.swap(temp);
}


//=============================================================================
// 更新処理
//=============================================================================
void EnemyManager::update(float frameTime)
{
	for (size_t i = 0; i < enemyList.size(); i++)
	{
		enemyList[i]->update(frameTime);

		// 撃退したエネミーオブジェクトを破棄する
		if (enemyList[i]->getEnemyData()->isAlive == false)
		{
			destroyEnemy(enemyList[i]->getEnemyData()->id);
		}
	}
}


//=============================================================================
// 描画処理
//=============================================================================
void EnemyManager::render(D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	//for (size_t i = 0; i < enemyList.size(); i++)
	//{
	//	enemyList[i]->render(view, projection, cameraPosition);
	//}
}


//=============================================================================
// エネミーオブジェクトの作成
//=============================================================================
void EnemyManager::createEnemy(EnemyData* enemyData)
{
	switch (enemyData->type)
	{
	case WOLF:
		break;
	case TIGER:
		break;
	case BEAR:
		break;

	default:
		//enemyList.emplace_back(new Enemy);
		break;
	}

	enemyList.back()->setDataToEnemy(enemyData);
}


//=============================================================================
// エネミーオブジェクトの破棄
//=============================================================================
void EnemyManager::destroyEnemy(int _id)
{
	for (size_t i = 0; i < enemyList.size(); i++)
	{
		if (enemyList[i]->getEnemyData()->id == _id)
		{
			delete enemyList[i];
			enemyList.erase(enemyList.begin() + i);
		}
	}
}


//=============================================================================
// ImGuiに出力
//=============================================================================
void EnemyManager::outputGUI()
{
#ifdef _DEBUG

	if (ImGui::CollapsingHeader("EnemyInformation"))
	{
		ImGuiIO& io = ImGui::GetIO();
		//float limitTop = 1000;
		//float limitBottom = -1000;

		ImGui::Text("numOfEnemy:%d", Enemy::getNumOfEnemy());

		//ImGui::SliderFloat3("position", position, limitBottom, limitTop);				//位置
		//ImGui::SliderFloat4("quaternion", quaternion, limitBottom, limitTop);			//回転
		//ImGui::SliderFloat3("scale", scale, limitBottom, limitTop);					//スケール
		//ImGui::SliderFloat("radius", &radius, 0, limitTop);							//半径
		//ImGui::SliderFloat("alpha", &alpha, 0, 255);									//透過値
		//ImGui::SliderFloat3("speed", speed, limitBottom, limitTop);					//速度
		//ImGui::SliderFloat3("acceleration", acceleration, limitBottom, limitTop);		//加速度
		//ImGui::SliderFloat3("gravity", gravity, limitBottom, limitTop);				//重力

		//ImGui::Checkbox("onGravity", &onGravity);										//重力有効化フラグ
		//ImGui::Checkbox("onActive", &onActive);										//アクティブ化フラグ
		//ImGui::Checkbox("onRender", &onRender);										//描画有効化フラグ
		//ImGui::Checkbox("onLighting", &onLighting);									//光源処理フラグ
		//ImGui::Checkbox("onTransparent", &onTransparent);								//透過フラグ
		//ImGui::Checkbox("operationAlpha", &operationAlpha);							//透過値の操作有効フラグ

		//ImGui::SliderInt("renderNum", &renderNum, 1, (int)limitTop);					//透過値の操作有効フラグ
	}

#endif
}