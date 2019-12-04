//===================================================================================================================================
//【LinkedList.h】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/09/29
// [更新日]2019/10/04
//===================================================================================================================================
#pragma once

//===================================================================================================================================
//【インクルード】
//===================================================================================================================================
#include "Base.h"

//===================================================================================================================================
//【ノード構造体】
//===================================================================================================================================
template <class T>
struct Node
{
	T value;
	Node<T>* prev;
	Node<T>* next;
	Node()		{ prev = NULL; next = NULL; }
	~Node()		{ prev = NULL; next = NULL; }
};

//===================================================================================================================================
//【双方向循環リストクラス】
//===================================================================================================================================
template <class T>
class LinkedList:Base
{
protected:
	Node<T>* head;			//先頭ダミーノード
	Node<T>* current;		//着目ダミーノード
	Node<T>** nodeList;		//全ノードのポインタ配列
public:
	//Data
	int nodeNum;		//全ノード数

	//===================================================================================================================================
	//【getter】
	//===================================================================================================================================
	Node<T>* getFrontNode() { return head->next; }		//先頭ノードにアクセス
	T* getFrontValue() { return &head->next->value; }	//先頭ノードの値にアクセス
	Node<T>* getNode(int i) { return nodeList[i]; }		//ランダムアクセス用リストにアクセス
	T* getValue(int i) { return &nodeList[i]->value; }	//ノード内の値にアクセス

	//===================================================================================================================================
	//【コンストラクタ】
	//===================================================================================================================================
	LinkedList()
	{
		head = new Node<T>;
		head->next = head;			//先頭ダミーノードの次ノードは自身
		head->prev = head;			//先頭ダミーノードの前ノードは自身
		current = head;				//初期着目ノードは先頭ダミーノード
		nodeNum = 0;
	}

	//===================================================================================================================================
	//【デストラクタ】
	//===================================================================================================================================
	~LinkedList()
	{

	}

	//===================================================================================================================================
	//【終了処理】
	//===================================================================================================================================
	void terminate()
	{
		allClear();
		SAFE_DELETE(head);
	}

	//===================================================================================================================================
	//【ノードのセット】
	//===================================================================================================================================
	void setNode(Node<T>* node, Node<T>* prev, Node<T>* next)
	{
		node->prev = prev;			//前ノードへのポインタ
		node->next = next;			//次ノードへのポインタ
	}

	//===================================================================================================================================
	//【空かどうか】
	//===================================================================================================================================
	bool isEnpty()
	{
		return head->next == head;
	}

	//===================================================================================================================================
	//【指定ノードの後ろに挿入】
	// Prev0	:	[node	]	[target]		[node	]				:処理前の着目ノード位置
	// Next1	:	[node	]	[target]		[newNode]	[node	]	:着目ノードの次に新規追加
	// Next2	:	[node	]	[node  ]		[target ]	[node	]	:新規ノードを着目ノードへ変更
	//===================================================================================================================================
	void insertAfter(Node<T>* target)
	{
		//着目ノードの次の位置に新規追加
		Node<T>* newNode = new Node<T>;
		Node<T>* nextNode = target->next;					//変更前に対象ノードの次ノード保存する
		target->next = target->next->prev = newNode;		//新規ノードの挿入
		setNode(newNode, target, nextNode);					//新規ノードのセット
		nodeNum++;
	}

	//===================================================================================================================================
	//【指定ノードを削除】
	//Prev0	:	[node	]	[current]	[node	]	:処理前の着目ノード位置
	//Next1	:	[current]	[deleteN]	[node	]	:着目ノードを削除対象にし、削除対象の前ノードを着目ノードへ
	//Next2	:	[current]	[node	]				:削除対象を削除
	//===================================================================================================================================
	bool remove(Node<T>* target)
	{
		if (target == head)return false;
		target->prev->next = target->next;			//対象ノードの前ノードの次ノードの入れ替え
		target->next->prev = target->prev;			//対象ノードの次ノードの前ノードの入れ替え
		delete target;
		nodeNum--;
		return true;
	}

	//===================================================================================================================================
	//【先頭ノードの削除】
	//===================================================================================================================================
	void removeFront()
	{
		remove(head->next);
	}

	//===================================================================================================================================
	//【先頭にノードを挿入】
	//===================================================================================================================================
	void insertFront()
	{
		insertAfter(head);
	}

	//===================================================================================================================================
	//【先頭にノードを挿入し、データを定義】
	//===================================================================================================================================
	void insertFront(T value)
	{
		insertAfter(head);
		head->next->value = value;
	}

	//===================================================================================================================================
	//【ランダムアクセス用ポインタ配列の更新】
	//===================================================================================================================================
	void listUpdate()
	{
		SAFE_DELETE_ARRAY(nodeList);				//ポインタ配列を削除
		if (nodeNum <= 0)return;					//ノード数が0の場合終了
		nodeList = new Node<T>*[nodeNum];			//全ノード数分のポインタメモリを確保
		current = head->next;						//先頭アドレスの次のポインタから開始
		int iterator = 0;							//list配列メモリアクセス防止イテレータ
		
		//while終了条件：現在の指し示すノードが先頭ノードかつイテレータが全ノード数
		while (current != head && iterator != nodeNum)
		{
			nodeList[iterator] = current;			//現在のノードポインタをポインタ配列へ記録
			current = current->next;				//次のノードポインタへ移動
			iterator++;								//iteratorを次へ
		}
	}

	//===================================================================================================================================
	//【全てのノードの削除】
	//===================================================================================================================================
	void allClear()
	{
		bool isRemaining = true;
		while (isRemaining)
		{
			isRemaining = remove(head->next);
		}
		SAFE_DELETE_ARRAY(nodeList);				//ポインタ配列を削除
		nodeNum = 0;
	}

};

