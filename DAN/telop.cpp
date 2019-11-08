//-----------------------------------------------------------------------------
// テロップクラス [Telop.h]
// Author : HAL東京昼間部 2年制ゲーム学科 GP12A332 32 中込和輝
// 作成開始日 : 2019/10/17
//-----------------------------------------------------------------------------
#include "Telop.h"
#include "UtilityFunction.h"
using namespace telopNS;


//=============================================================================
// 初期化
//=============================================================================
void Telop::initialize(LPDIRECT3DTEXTURE9 _texture, int _pivot,
	int _width, int _height, D3DXVECTOR3 _position, D3DXVECTOR3 _rotation, D3DCOLOR color)
{

	input = getInput();
	telopFlag = false;
	state = CLOSE;
	telopTimer = 0.0f;
	displayTimer = 0.0f;
	

	sprite = new Sprite;
	sprite->initialize(_texture, _pivot,
		_width,  _height, _position, _rotation, color);
	
	
}


//=============================================================================
// 終了処理
//=============================================================================
void Telop::uninitialize()
{
	SAFE_DELETE(sprite);
}


//=============================================================================
// 更新処理
//=============================================================================
void Telop::update(float _frameTime)
{
	frameTime = _frameTime;				//フレームタイムの保存
	
	rate = 0.0f;
	switch (state)
	{
	case OPEN://オープン

		telopTimer += _frameTime;		//シーンタイムの更新

		//高さの更新
		Telop::open();
		
		break;
	case DISPLAY:	

		//表示待機　
		displayTimer -= _frameTime;
		Telop::display();
		
		break;
	case CLOSE:		

		//クローズ
		Telop::close();
		
		//オープンへ遷移
		if (telopFlag)
		{
			telopFlag = false;
			state = OPEN;
			telopTimer = 0.0f;
		}
		
		break;
		
	}

	//サイズの更新
	sprite->setSize(WIDTH, heightValue);
	sprite->setVertex();
}


//=============================================================================
// 描画処理
//=============================================================================
void Telop::render()
{
	if (telopTimer>0)
	{
		sprite->render();
	}
	
}

//=============================================================================
// オープン処理
//=============================================================================
void Telop::open()
{
	//高さの更新
	rate = telopTimer / telopNS::OPEN_TIME;
	heightValue = (int)((float)telopNS::MAX_HEIGHT * rate);
	if (telopTimer > telopNS::OPEN_TIME)
	{
		state = telopNS::DISPLAY;
		displayTimer = telopNS::DISPLAY_TIME;
		telopTimer = telopNS::CLOSE_TIME;
	}
}

//=============================================================================
// 待機処理
//=============================================================================
void Telop::display()
{
	if (displayTimer < 0)
	{
		state = CLOSE;
		displayTimer = 0.0f;
	}
}
//=============================================================================
// クローズ処理
//=============================================================================
void Telop::close()
{
	if (telopTimer > 0)
	{
		telopTimer -= frameTime;
		//高さの更新
		rate = telopTimer / CLOSE_TIME;
		heightValue = (int)((float)MAX_HEIGHT * rate);
	}
	
}

//=============================================================================
// テロップ再生処理
//=============================================================================
void Telop::playTelop()
{
	telopFlag = true;
}