//============================
//[CrediTex.cpp]
//๕๎W๎
//============================

//============================
//CN[h
//============================
#include "CreditTex.h"

//============================
//yusing้พz
//============================
using namespace creditTex;

//============================
//O[oฯ
//============================

//============================
//๚ป
//============================
void CreditTex::initialize()
{
	for (int i = 0; i < CREDIT_MAX; i++)
	{
		credit[i] = new Sprite;
	}
	
	credit[0]->initialize(
						*textureNS::reference(textureNS::CREDIT)//eNX`
						,SpriteNS::CENTER						//S
						,WIDTH									//ก
						,HEIGHT									//c
						,POSITION								//\ฆสu
						,ROTATION								//๑]
						,COLOR);								//F

	credit[1]->initialize(
						*textureNS::reference(textureNS::CREDIT2)//eNX`
						, SpriteNS::CENTER						//S
						, WIDTH									//ก
						, HEIGHT								//c
						, POSITION_2							//\ฆสu
						, ROTATION								//๑]
						, COLOR);								//F
						
	pos[0] = POSITION;
	pos[1] = POSITION_2;

}

//============================
//`ๆ
//============================
void CreditTex::render()
{
	for (int i = 0; i < CREDIT_MAX; i++)
	{
		credit[i]->render();
	}
}

//============================
//XV
//============================
void CreditTex::update()
{
	if (pos[1].y >= MOVE_MAX)
	{
		moveCredit();
	}
}

//============================
//Iน
//============================
void CreditTex::uninitialize()
{
	for (int i = 0; i < CREDIT_MAX; i++)
	{
		delete credit[i];
	}
}

//===========================
// ใษฎฉท
//===========================
void CreditTex::moveCredit()
{
	pos[0].y -= MOVE_SPEED;
	pos[1].y -= MOVE_SPEED;

	credit[0]->setPosition(pos[0]);
	credit[1]->setPosition(pos[1]);
	credit[0]->setVertex();
	credit[1]->setVertex();
}