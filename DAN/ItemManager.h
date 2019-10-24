//-----------------------------------------------------------------------------
// アイテム管理クラス [Item.h]
// Author : HAL東京昼間部 2年制ゲーム学科 GP12A332 32 中込和輝
// 作成開始日 : 2019/10/4
//-----------------------------------------------------------------------------
#pragma once
#include <vector>
#include "Item.h"
#include "Battery.h"


//=============================================================================
// 名前空間
//=============================================================================
namespace itemNS
{	
	const int NUM_SURPLUS_DATA = 10;			// 初期アイテムデータ数に加えて確保する余剰分のベクター要素数
}


//=============================================================================
//クラス定義
//=============================================================================
class ItemManager
{
private:
	std::vector<Item*> itemList;				// アイテムポインタリスト
	StaticMeshRenderer* batteryRenderer;		// 描画オブジェクト
	int nextID;									// 次回ツリー発行ID

public:
	void initialize();
	void uninitialize();
	void update(float frameTime);
	void render(D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);
	void createItem(itemNS::ItemData itemData);
	void destroyItem(int _itemID);
	void destroyAllItem();
	int issueNewItemID();
	void outputGUI();

	// Getter
	std::vector<Item*>& getList();
};