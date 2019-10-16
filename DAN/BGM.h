//===================================================================================================================================
//【BGM.h】
// [作成者]HAL東京GP12A332 16 蔡 友剛
// [作成日]2019/10/14
// [更新日]2019/10/14
//===================================================================================================================================
#pragma once

//===================================================================================================================================
//【インクルード】
//===================================================================================================================================
#include "Base.h"
#include "LinkedList.h"
#include "SoundBase.h"

//===================================================================================================================================
//【列挙型定数】
//===================================================================================================================================
enum SPLASH_BGM_LIST
{
	SPLASH_BGM_01,
	SPLASH_BGM_MAX
};

enum TITLE_BGM_LIST
{
	TITLE_BGM_01,
	TITLE_BGM_MAX
};

enum GAME_BGM_LIST
{
	GAME_BGM_01,
	GAME_BGM_MAX
};

//===================================================================================================================================
//【サウンド(XAudio2)】
//サウンドのBGMクラス
//===================================================================================================================================
class BGMManager : public SoundBase
{
public:
	BGMManager();
	~BGMManager();

	//変数
	static const char * const splashBGMPathList[];
	static const char * const titleBGMPathList[];
	static const char * const gameBGMPathList[];
	static int		BGMScene;
	static float		startTime;
	static float		currentTime;

	//関数
	static void		SwitchAudioBuffer(int scene);	//ステージ遷移に合わせて必要なサウンドバッファを用意する
	void				outputBGMGUI(void);				//ImGUIへの出力
	void				SetSpeed(void);					//再生速度の設定
	void				SetSpeedOn(void);				//再生速度の設定(On)

	//debug用
#ifdef _DEBUG

#endif

};