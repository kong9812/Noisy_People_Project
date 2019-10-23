//-----------------------------------------------------------------------------
// ツリー基底クラス [Tree.cpp]
// Author : HAL東京昼間部 2年制ゲーム学科 GP12A332 32 中込和輝
// 作成開始日 : 2019/10/13
//-----------------------------------------------------------------------------
#include "Tree.h"
#include "ImguiManager.h"
using namespace treeNS;


int Tree::numOfTree = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
Tree::Tree(treeNS::TreeData _treeData)
{
	treeData = _treeData;
	trunk->position = treeData.initialPosition;
	leaf->position = treeData.initialPosition;

	// treeData.initialDirectionを基にした向き転換

	// treeData.sizeを基にした拡大縮小

	numOfTree++;
}


//=============================================================================
// デストラクタ
//=============================================================================
Tree::~Tree()
{
	numOfTree--;
}


//=============================================================================
// 更新処理
//=============================================================================
void Tree::update(float frameTime)
{
}


//=============================================================================
// Getter
//=============================================================================
Object* Tree::getLeaf() { return leaf; }
Object* Tree::getTrunk() { return trunk; }
int Tree::getNumOfTree(){ return numOfTree; }
TreeData* Tree::getTreeData() { return &treeData; }


//=============================================================================
// Setter
//=============================================================================
void Tree::setDataToTree(TreeData _treeData) { treeData = _treeData; }
void Tree::setLeaf(Object* _leaf) { leaf = _leaf; }
void Tree::setTrunk(Object* _trunk) {trunk = _trunk;}
