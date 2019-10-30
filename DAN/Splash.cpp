//===================================================================================================================================
//【Splash.cpp】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/09/20
// [更新日]2019/10/21
//===================================================================================================================================
#include "Splash.h"

//===================================================================================================================================
//【using宣言】
//===================================================================================================================================
using namespace splashNS;

//===================================================================================================================================
//【コンストラクタ】
//===================================================================================================================================
Splash::Splash()
{
	// 現在のシーン(スプラッシュ)
	sceneName = "Scene -Splash-";
	// 次のシーン(タイトル)
	nextScene = SceneList::TITLE;

	//シーンの更新
	SoundInterface::SwitchAudioBuffer(SceneList::SPLASH);

	//再生パラメータ
	memset(playParameters, 0, sizeof(playParameters));
	FILTER_PARAMETERS filterParameters = { XAUDIO2_FILTER_TYPE::LowPassFilter, 0.1f, 1.5f };
	playParameters[0] = { ENDPOINT_VOICE_LIST::ENDPOINT_SE, SPLASH_SE_LIST::SPLASH_SE_01, false,NULL,false,NULL,true, filterParameters };
	playParameters[1] = { ENDPOINT_VOICE_LIST::ENDPOINT_BGM, SPLASH_BGM_LIST::SPLASH_BGM_01, true ,1.0f,false,NULL,true, filterParameters };

	//再生
	SoundInterface::SE->playSound(playParameters[0]);
	SoundInterface::BGM->playSound(playParameters[1]);

	//エフェクシアーテスト
	effekseerNS::setProjectionMatrix(90.0f / 180.0f * 3.14f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 10000.0f);

}

//===================================================================================================================================
//【デストラクタ】
//===================================================================================================================================
Splash::~Splash()
{
	//サウンドの停止
	SoundInterface::SE->stopSound(playParameters[0]);
	SoundInterface::BGM->stopSound(playParameters[1]);
	effekseerNS::stop(effekseerNS::TEST0);
}

//===================================================================================================================================
//【初期化】
//===================================================================================================================================
void Splash::initialize()
{
	// スプラッシュspriteの作成
	splashSprite = new SplashSprite;
}

//===================================================================================================================================
//【終了処理】
//===================================================================================================================================
void Splash::uninitialize()
{
	//スプラッシュの削除
	SAFE_DELETE(splashSprite);
}

//===================================================================================================================================
//【更新】
//===================================================================================================================================
void Splash::update(float _frameTime)
{
	//フレーム落ち
	if (_frameTime > 1.0f / (FRAME_RATE / 4))
	{
		stopTimer += _frameTime;					//処理落ち時間の蓄積
		return;
	}
	stopTimer = max(stopTimer-_frameTime,0.0f);		//停止時間の減衰
	sceneTimer += _frameTime;						//シーンタイムの更新
	frameTime = _frameTime;							//フレームタイムの保存

	//スプラッシュ2D更新
	float rate = sceneTimer / SCENE_TIME;
	splashSprite->update(rate);

	//エフェクトの再生
	if (input->wasKeyPressed('1'))
	{
		effekseerNS::play(new effekseerNS::Instance);
	}

	//Enter,Spaceまたは〇ボタン,Optionsでタイトルへ
	if (input->wasKeyPressed(VK_RETURN) ||
		input->wasKeyPressed(VK_SPACE) ||
		input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::A) ||
		input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::A) ||
		input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::SPECIAL_MAIN) ||
		input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::SPECIAL_MAIN)
		)
	{
		changeScene(nextScene);
	}

	// フェードが終わったらタイトルへ
	if(sceneTimer > SCENE_TIME)changeScene(nextScene);
}

//===================================================================================================================================
//【描画処理】
//===================================================================================================================================
void Splash::render()
{
	//描画対象をウィンドウ全体に切替
	direct3D9->changeViewportFullWindow();

	//エフェクシアーテスト
	effekseerNS::setCameraMatrix(D3DXVECTOR3(10.0f, 5.0f, 20.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	effekseerNS::render();

	//UI
	renderUI();

}

//===================================================================================================================================
//【3D描画】
//===================================================================================================================================
//void Splash::render3D(Camera _currentCamera)
//{
//
//}

//===================================================================================================================================
//【UI描画】
//===================================================================================================================================
void Splash::renderUI()
{
	// スプラッシュ2D描画
	splashSprite->render();

}

//===================================================================================================================================
//【衝突処理】
//===================================================================================================================================
void Splash::collisions()
{

}

//===================================================================================================================================
//【AI処理】
//===================================================================================================================================
void Splash::AI()
{

}

//===================================================================================================================================
//【GUI作成処理】
//===================================================================================================================================
#ifdef _DEBUG
void Splash::createGUI()
{
	ImGui::Text(sceneName.c_str());
	ImGui::Text("sceneTime = %f", sceneTimer);
	ImGui::Text("stopTime = %f", stopTimer);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
#endif // _DEBUG
