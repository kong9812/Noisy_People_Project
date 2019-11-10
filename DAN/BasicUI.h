//================================
// 基礎UIクラスの定義[BasicUI.h]
// 染矢　晃介
//================================
#pragma once

//================================
// インクルード
//================================
#include"TextureLoader.h"
#include "Sprite.h"

//================================
// 名前空間
//================================
namespace basicUiNS
{
	//移動の種類
	enum MOVE_TYPE
	{
		slideRight,
		slideLeft,
		slideUp,
		slideDown,
	};

	const float SLIDE_SPEED = 20.0f;		//スライドインの速度
	const int	CHANGE_SIZE_SPEED = 20;		//サイズ変更の速度
	const float   CHANGE_ALPHA_SPEED = 155.0f;		//α値の変更速度
}

//================================
//クラス定義
//================================
class BasicUI
{
public://メンバー変数
	D3DXVECTOR3 position;	//表示位置
	D3DXVECTOR3 rotation;	//回転
	D3DCOLOR	color;		//色
	int widthSize;			//幅のサイズ
	int heightSize;			//高さサイズ
	float alphaValue;		//α値
	// uv座標用の変数
	D3DXVECTOR2 uvCoord01;
	D3DXVECTOR2 uvCoord02;
	D3DXVECTOR2 uvCoord03;
	D3DXVECTOR2 uvCoord04;

private:
public://メンバー関数
	BasicUI();				//コンストラクタ
	~BasicUI();				//デストラクタ
	void    initialize(Sprite *sprite, LPDIRECT3DTEXTURE9 *fileName);//初期化
	void	assingPosition(D3DXVECTOR3 pos);						//表示位置の代入
	void	assingRotation(D3DXVECTOR3 rot);						//回転の代入
	void	assingColor(D3DCOLOR col);								//色の代入
	void	assingSize(int widh, int height);						//サイズの代入
	void	changePostion(int movetype);//位置変更	
	void	increaseAlpha(float alpha);//透明度増加
	void	decreaseAlpha(float alpha);//透明度減少
	void	expansionWidthSize(int speed);//横サイズの拡大
	void	expansionHeightSize(int speed);//縦サイズの拡大
	void	reductionWidthSize(int speed);//横サイズの縮小
	void	reductionHeightSize(int speed);//縦サイズの縮小

private:
};