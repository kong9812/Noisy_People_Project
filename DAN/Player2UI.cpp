//===============================
//プレイヤーUIの処理[PlayerUI.cpp]
//染矢晃介
//===============================

//================================
//インクルード
//================================
#include "Player2UI.h"

//================================
//コンストラクタ
//================================
Player2UI::Player2UI()
{
	buttonUi = new ButtonUI;
	hpGuage = new HPguageP2;
	charaIcon = new CharaIcon;
	hpGuageEmp = new HPguageEmp;
	electGuageEmp = new ElectGuageEmp;
	electGuage = new ElectGuage;
	electTank = new ElectTank;
}

//=================================
//デストラクタ
//=================================
Player2UI::~Player2UI()
{
	delete buttonUi;
	delete hpGuage;
	delete charaIcon;
	delete hpGuageEmp;
	delete electGuageEmp;
	delete electGuage;
	delete electTank;
}

//==================================
//初期化
//==================================
void Player2UI::initialize(Player *player)
{
	this->player = player;
	buttonUi->initialize();
	hpGuage->initialize();
	charaIcon->initialize(basicUiNS::P2);
	hpGuageEmp->initialize(basicUiNS::P2);
	electGuageEmp->initialize(basicUiNS::P2);
	electGuage->initialize(basicUiNS::P2);
	electTank->initialize(basicUiNS::P2);
}

//==================================
//描画
//==================================
void Player2UI::render()
{
	state = player->getState();
	buttonUi->renderP2(state);
	hpGuageEmp->render();
	hpGuage->render();
	charaIcon->render();
	electGuageEmp->render();
	electGuage->render();
	electTank->render();
}

//==================================
//更新
//==================================
void Player2UI::update()
{

	//各フラグの獲得
	getFlag();

	//P2用
	buttonUi->update(shotFlag, 0);
	buttonUi->update(jumpFlag, 1);
	buttonUi->update(visionFlag, 2);
	buttonUi->update(skyVisionFlag, 3);
	buttonUi->update(shiftFlag, 4);

	//HPゲージ処理
	hpGuage->update(hp);

	//電力ゲージ処理
	electGuage->update(power);
	electTank->update(power, basicUiNS::P2);
}

//==================================
//各フラグの獲得
//==================================
void Player2UI::getFlag()
{
	//各フラグの獲得
	skyVisionFlag = player->canDoSkyVision();
	shiftFlag = player->canShift();
	shotFlag = player->canShot();
	visionFlag = player->canDoVision();
	jumpFlag = player->canJump();
	hp = player->getHp();
	power = player->getPower();
}