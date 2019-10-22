//===================================================================================================================================
//【Text.cpp】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/10/18
// [更新日]2019/10/18
//===================================================================================================================================

//===================================================================================================================================
//【インクルード】
//===================================================================================================================================
#include "Text.h"
#include "Direct3D9.h"

//===================================================================================================================================
//【コンストラクタ】
//===================================================================================================================================
Text::Text()
{
	font = NULL;
	color = D3DXCOLOR(255, 255, 255, 255);
}

//===================================================================================================================================
//【デストラクタ】
//===================================================================================================================================
Text::~Text()
{
}

//===================================================================================================================================
//【初期化：デフォルトテキスト(tahome)】
//===================================================================================================================================
void Text::initialize(int height,int width,D3DXCOLOR _color)
{
	color = _color;
	//文字列レンダリングの初期化
	D3DXCreateFont(getDevice(), height, width, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "tahome", &font);
}

//===================================================================================================================================
//【初期化：任意のフォントを使用(LPCSTR fontName)】
//===================================================================================================================================
void Text::initialize(int height,int width,D3DXCOLOR _color,LPCSTR fontName)
{
	color = _color;
	//文字列レンダリングの初期化
	D3DXCreateFont(getDevice(), height, width, FW_REGULAR, NULL, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH | FF_DONTCARE, fontName, &font);
}

//===================================================================================================================================
//【プリント】
//===================================================================================================================================
void Text::print(float x,float y, const char* string, ...)
{
	TCHAR str[2048];
	va_list _argList;
	__crt_va_start(_argList, string);

	_vsprintf_l(str, string, NULL, _argList);

	__crt_va_end(_argList);

	RECT rect = { x,y,0,0 };
	//文字列のサイズを計算
	font->DrawTextA(NULL, str, -1, &rect, DT_CALCRECT, NULL);
	//そのサイズでレンダリング
	font->DrawTextA(NULL, str, -1, &rect, DT_LEFT | DT_BOTTOM, color);
}