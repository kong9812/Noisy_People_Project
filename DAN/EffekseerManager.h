//===================================================================================================================================
//【EffekseerManager.h】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/10/18
// [更新日]2019/10/21
//===================================================================================================================================
#pragma once

//===================================================================================================================================
//備考：このクラスをプロジェクトへ使用する際に、プロジェクトの設定を行う必要があります。
//	�@プロジェクト->プロパティ->C/C++->コード生成->ランタイムライブラリを以下の通りに設定する
//		Debug時		：マルチスレッドデバッグ(/MTd)
//		Release時	：マルチスレッド(/MT)
//		※ランタイムライブラリの設定をプロジェクト上、上記にできない場合は、Effekseerのランタイムライブラリの
//		　リソースを公式サイトやGitHub上からダウンロードし、自身のプロジェクトに合致するように、新たなライブラリを
//		　ランタイムライブラリを作成する必要がある。基本的には、EffekseerのHelp参照。
//	�Aプロジェクト->プロパティ->C/C++->全般->追加のインクルードディレクトリ
//		$(ProjectDir)Effekseer\Compiled\includeを入力	
//	�Bプロジェクト->プロパティ->リンカー->全般->追加のライブラリディレクトリ
//		$(ProjectDir)Effekseer\Compiled\lib	
//===================================================================================================================================

//===================================================================================================================================
//【インクルード】
//===================================================================================================================================
#include "Base.h"
#include <stdio.h>
#include <windows.h>
#include <string>
#include <d3d9.h>
#include <XAudio2.h>
#include <Effekseer.h>
#include <EffekseerRendererDX9.h>
#include <EffekseerSoundXAudio2.h>
#include "LinkedList.h"

//===================================================================================================================================
//【ライブラリの読み込み】
//===================================================================================================================================
#pragma comment(lib, "d3d9.lib" )
#pragma comment(lib, "xaudio2.lib" )
#if _DEBUG
#pragma comment(lib, "VS2017/Debug/Effekseer.lib" )
#pragma comment(lib, "VS2017/Debug/EffekseerRendererDX9.lib" )
#pragma comment(lib, "VS2017/Debug/EffekseerSoundXAudio2.lib" )
#else
#pragma comment(lib, "VS2017/Release/Effekseer.lib" )
#pragma comment(lib, "VS2017/Release/EffekseerRendererDX9.lib" )
#pragma comment(lib, "VS2017/Release/EffekseerSoundXAudio2.lib" )
#endif

//===================================================================================================================================
//【名前空間】
//===================================================================================================================================
namespace effekseerNS
{
	enum EFFEKSEER_NUMBER
	{
		TEST0,
		TEST1,
		MAX_EFFEKSEER,
	};

	class Instance
	{
		::Effekseer::Effect*	effect;
		::Effekseer::Handle		handle;

		Instance()
		{
			effect = NULL;
			handle = -1;
		}
	};

	//===================================================================================================================================
	//【外部参照】
	//===================================================================================================================================
	void play(int effekseerNo,D3DXVECTOR3 position);
	void stop(int effekseerNo);
	void setProjectionMatrix(float fov, float windowWidth, float windowHeight, float zn, float zf);
	void setCameraMatrix(D3DXVECTOR3 position, D3DXVECTOR3 eye, D3DXVECTOR3 up);
	void render();
	void pause(bool flag);
	void pause(::Effekseer::Handle handle, bool flag);
}

//===================================================================================================================================
//【エフェクシアーマネージャー】
//===================================================================================================================================
class EffekseerManager
{
public:

	::Effekseer::Manager*				manager;
	::EffekseerRendererDX9::Renderer*	renderer;
	::EffekseerSound::Sound*			sound;

	//カメラ情報
	::Effekseer::Vector3D				position;
	::Effekseer::Vector3D				eye;
	::Effekseer::Vector3D				up;

	IXAudio2*							xa2;
	IXAudio2MasteringVoice*				xa2Master;

	//ファイル名
	const wchar_t*						fileName[effekseerNS::MAX_EFFEKSEER];

	//エフェクト
	::Effekseer::Effect*				effect[effekseerNS::MAX_EFFEKSEER];

	//ハンドルリスト
	//LinkedList<effekseerNS::Instance>	instanceList;

public:
	EffekseerManager();
	~EffekseerManager();
	void initialize();
	void uninitialize();
	void update();
	void begin();
	void end();
	void render();

	void setProjectionMatrix(float fov, float windowWidth, float windowHeight, float zn, float zf);
	void setCameraMatrix(D3DXVECTOR3 position, D3DXVECTOR3 eye, D3DXVECTOR3 up);
	void play(int effekseerNo, D3DXVECTOR3 position);
	void stop(int effekseerNo);
	void pause(bool flag);
	void pause(::Effekseer::Handle handle, bool flag);

};

