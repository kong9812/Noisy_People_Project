//==================================
//ボタンUI処理[UIButtoon.cpp]
//染矢　晃介
//==================================

//==================================
//インクルード
//==================================
#include "UIButton.h"

//==================================
// using宣言
//==================================
using namespace uiButtonNS;

//==================================
//コンストラクタ
//==================================
UiButton::UiButton()
{
	for (int i = 0; i < TYPE_MAX; i++)
	{
		button[i] = new Sprite;
	}
}

//==================================
//デストラクタ
//==================================
UiButton::~UiButton()
{
	for (int i = 0; i < TYPE_MAX; i++)
	{
		delete button[i];
	}
}

//==================================
//初期化
//==================================
void UiButton::initialize()
{

}

//==================================
//描画
//==================================
void UiButton::render()
{

}