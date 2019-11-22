//===================================
//電力ゲージ処理[ElectGuage.cpp]
//染矢晃介
//===================================

//===================================
//インクルード
//===================================
#include "ElectGuage.h"

//===================================
// usuing宣言
//===================================
using namespace electGuageNS;

//===================================
//コンストラクタ
//===================================
ElectGuage::ElectGuage()
{
	electGuage = new Sprite;
	width = WIDTH_EN_GUAGE;
}

//===================================
//デストラクタ
//===================================
ElectGuage::~ElectGuage()
{
	delete electGuage;
}

//===================================
//初期化
//===================================
void ElectGuage::initialize(int playerType)
{
	switch (playerType)
	{
	case basicUiNS::P1:
		BasicUI::assingSize(WIDTH_EN_GUAGE, HEIGHT_EN_GUAGE);
		BasicUI::assingPosition(POSITION_EN_GUAGE);
		BasicUI::changePivot(SpriteNS::TOP_LEFT);
		BasicUI::initialize(electGuage, textureNS::reference(textureNS::UI_EN_GUAGE_P1));
		break;
	case basicUiNS::P2:
		BasicUI::assingSize(WIDTH_EN_GUAGE, HEIGHT_EN_GUAGE);
		BasicUI::assingPosition(POSITION_EN_GUAGE_P2);
		BasicUI::changePivot(SpriteNS::TOP_RIGHT);
		BasicUI::initialize(electGuage, textureNS::reference(textureNS::UI_EN_GUAGE_P2));
		break;

	}
}

//===================================
//描画
//===================================
void ElectGuage::render()
{
	electGuage->render();
}

//===================================
//更新
//引数：電力
//===================================
void ElectGuage::update(int power)
{
	changeGuage(power);
}

//===================================
//ゲージの変化処理
//引数：現在の電力
//===================================
void ElectGuage::changeGuage(int power)
{
	//電力の下2桁を取り出す
	int  enPersent = power % 100;
	if (BasicUI::widthSize > WIDTH_EN_GUAGE*enPersent)
	{
		BasicUI::reductionWidthSize(electGuage, 1.0);
	}
	else if (enPersent == 0)//0の時はゲージがMAX
	{
		BasicUI::changeWhidthSize(electGuage, WIDTH_EN_GUAGE);
	}
}