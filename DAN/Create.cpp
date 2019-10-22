//===================================================================================================================================
//【Create.cpp】
// [作成者]HAL東京GP12A332 16 蔡 友剛
// [作成日]2019/09/20
// [更新日]2019/10/18
//===================================================================================================================================

//===================================================================================================================================
//【インクルード】
//===================================================================================================================================
#include "Create.h"
#include "Game.h"

//===================================================================================================================================
//【using宣言】
//===================================================================================================================================
using namespace gameNS;

//===================================================================================================================================
//【コンストラクタ】
//===================================================================================================================================
Create::Create()
{
	sceneName = "Scene -Create-";

	nextScene = SceneList::RESULT;

	//シーンの更新
	SoundInterface::SwitchAudioBuffer(SceneList::CREATE);

	//エネミーツール
	enemyTools = new ENEMY_TOOLS;
	//アイテムツール
	itemTools = new ITEM_TOOLS;

}

//===================================================================================================================================
//【デストラクタ】
//===================================================================================================================================
Create::~Create()
{
	//エネミーツール
	SAFE_DELETE(enemyTools);
	//アイテムツール
	SAFE_DELETE(itemTools);
}

//===================================================================================================================================
//【初期化】
//===================================================================================================================================
void Create::initialize() {

	//tmpObj
	tmpObject = new TmpObject;

	//camera
	camera = new Camera;
	camera->initialize(WINDOW_WIDTH, WINDOW_HEIGHT);
	camera->setTarget(tmpObject->getPosition());
	camera->setTargetX(&tmpObject->getAxisX()->direction);
	camera->setTargetY(&tmpObject->getAxisY()->direction);
	camera->setTargetZ(&tmpObject->getAxisZ()->direction);
	camera->setRelative(CAMERA_RELATIVE_QUATERNION);
	camera->setGaze(D3DXVECTOR3(0, 0, 0));
	camera->setRelativeGaze(CAMERA_RELATIVE_GAZE);
	camera->setUpVector(D3DXVECTOR3(0, 1, 0));
	camera->setFieldOfView((D3DX_PI / 18) * 9);

	//light
	light = new Light;
	light->initialize();

	//テストフィールド
	testField = new Object();
	testFieldRenderer = new StaticMeshObject(staticMeshNS::reference(staticMeshNS::YAMADA_TEST_ZONE));
	testFieldRenderer->generateObject(testField);
	testField->initialize(&D3DXVECTOR3(0, 0, 0));

	//プレイヤーの初期化
	tmpObject->initialize(inputNS::DINPUT_1P, 0);
	tmpObject->setCamera(camera);	//カメラポインタのセット
	for (int i = 0; i < tmpObjNS::TMPOBJ_LIST::TMPOBJ_MAX; i++)
	{
		int staticMeshNo = 0;
		switch (i)
		{
		case tmpObjNS::TMPOBJ_LIST::TMPOBJ_PLAYER:
			staticMeshNo = staticMeshNS::YAMADA_ROBOT2;
			break;
		case tmpObjNS::TMPOBJ_LIST::TMPOBJ_WOLF:
			staticMeshNo = staticMeshNS::SAMPLE_REDBULL;
			break;
		case tmpObjNS::TMPOBJ_LIST::TMPOBJ_TIGER:
			staticMeshNo = staticMeshNS::SAMPLE_BUNNY;
			break;
		case tmpObjNS::TMPOBJ_LIST::TMPOBJ_BEAR:
			staticMeshNo = staticMeshNS::SAMPLE_HAT;
			break;
		case tmpObjNS::TMPOBJ_LIST::TMPOBJ_BATTERY:
			staticMeshNo = staticMeshNS::SAMPLE_SCISSORS;
			break;
		default:
			break;
		}
		tmpObjRenderer[i] = new StaticMeshObject(staticMeshNS::reference(staticMeshNo));
		tmpObjRenderer[i]->generateObject(tmpObject);
	}
	tmpObject->configurationGravityWithRay(testField->getPosition(), testFieldRenderer->getStaticMesh()->mesh, testField->getMatrixWorld());	//重力を設定

	//枯木の初期化
	deadTree = new DeadTree();
	//木Aの初期化
	treeA = new TreeTypeA();
	//木Bの初期化
	treeB = new TreeTypeB();
	//石の初期化
	stone = new Stone();

	// サウンドの再生
	//sound->play(soundNS::TYPE::BGM_GAME, soundNS::METHOD::LOOP);

	//テキストの初期化
	//text.initialize(direct3D9->device,10,10, 0xff00ff00);
	//text2.initialize(direct3D9->device,11,11, 0xff0000ff);

	//エフェクト（インスタンシング）テスト
	testEffect = new TestEffect();

	// エネミー
	enemyManager = new EnemyManager;
	enemyManager->initialize(testFieldRenderer->getStaticMesh()->mesh, testField->getMatrixWorld());

	// ツリー
	treeManager = new TreeManager;
	treeManager->initialize();

	// アイテム
	itemManager = new ItemManager;
	itemManager->initialize();

}

//===================================================================================================================================
//【終了処理】
//===================================================================================================================================
void Create::uninitialize() {
	SAFE_DELETE(camera);
	SAFE_DELETE(light);
	//SAFE_DELETE(testField);
	SAFE_DELETE(testFieldRenderer);
	//SAFE_DELETE(player);
	for (int i = 0; i < tmpObjNS::TMPOBJ_LIST::TMPOBJ_MAX; i++)
	{
		SAFE_DELETE(tmpObjRenderer[i]);
	}
	SAFE_DELETE(deadTree);
	SAFE_DELETE(treeA);
	SAFE_DELETE(treeB);
	SAFE_DELETE(stone);
	SAFE_DELETE(testEffect);
	SAFE_DELETE(enemyManager);
	SAFE_DELETE(treeManager);
	SAFE_DELETE(itemManager);
}

//===================================================================================================================================
//【更新】
//===================================================================================================================================
void Create::update(float _frameTime) {

	sceneTimer += _frameTime;
	frameTime = _frameTime;

	//【処理落ち】
	//フレーム時間が約10FPS時の時の時間より長い場合は、処理落ち（更新しない）
	//※フレーム時間に準拠している処理が正常に機能しないため
	if (frameTime > 0.10)return;

	//エフェクト（インスタンシング）テスト
	testEffect->update(frameTime);

	//テストフィールドの更新
	testField->update();
	testFieldRenderer->update();

	//エネミーツールの更新
	enemyTools->outputEnemyToolsGUI(*tmpObject->getPosition(), tmpObject->getAxisZ()->direction);
	if (enemyTools->resetEnemy)
	{
		//最新のenemy.enemyの読み込み
		enemyManager->relocateEnemyAccordingToFile();
		enemyTools->resetEnemy = false;
	}

	//アイテムツールの更新
	itemTools->outputItemToolsGUI(*tmpObject->getPosition(), tmpObject->getAxisZ()->direction);

	//プレイヤーの更新
	tmpObject->update(frameTime);

	// エネミーの更新
	enemyManager->update(frameTime);

	// ツリーの更新
	treeManager->update(frameTime);

	// アイテムの更新
	if (input->wasKeyPressed('0'))
	{
		itemNS::ItemData unko = { 0, itemNS::BATTERY, *tmpObject->getPosition() };
		itemManager->createItem(&unko);
	}
	if (input->wasKeyPressed('9'))
	{
		itemManager->uninitialize();
	}
	itemManager->update(frameTime);

	////カメラの更新
	//camera->update();
	for (int i = 0; i < tmpObjNS::TMPOBJ_LIST::TMPOBJ_MAX; i++)
	{
		tmpObjRenderer[i]->update();
	}

	//枯木の更新
	deadTree->update();
	//木Aの更新
	treeA->update();
	//木Bの更新
	treeB->update();
	//石の更新
	stone->update();

	//カメラの更新
	camera->update();

	//sound->updateSound(*player->getPosition(), player->getAxisZ()->direction);

	// Enterまたは〇ボタンでリザルトへ
	if (input->wasKeyPressed(VK_RETURN) ||
		input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::A) ||
		input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::A))
	{
		// サウンドの再生
		//sound->play(soundNS::TYPE::SE_DECISION, soundNS::METHOD::PLAY);
		// シーン遷移
		changeScene(nextScene);
	}

}

//===================================================================================================================================
//【描画】
//===================================================================================================================================
void Create::render() {

	////1Pカメラ・ウィンドウ
	//camera->renderReady();
	//direct3D9->changeViewport1PWindow();
	//render3D(*camera);

	////2Pカメラ・ウィンドウ
	//camera->renderReady();
	//direct3D9->changeViewport2PWindow();
	//render3D(*camera);

	//test(訳アリ)
	camera->renderReady();
	direct3D9->changeViewportFullWindow();
	render3D(*camera);
	effekseerNS::setCameraMatrix(camera->position, camera->gazePosition, camera->upVector);
	effekseerNS::render();

	//UI
	direct3D9->changeViewportFullWindow();
	renderUI();

}

//===================================================================================================================================
//【3D描画】
//===================================================================================================================================
void Create::render3D(Camera currentCamera) {


	//テストフィールドの描画
	testField->setAlpha(0.1f);
	testFieldRenderer->render(*shaderNS::reference(shaderNS::INSTANCE_STATIC_MESH), currentCamera.view, currentCamera.projection, currentCamera.position);

	//エフェクト（インスタンシング）テスト
	testEffect->render(currentCamera.view, currentCamera.projection, currentCamera.position);

	// プレイヤーの描画
	tmpObjRenderer[tmpObject->getItemListboxMesh()]->render(*shaderNS::reference(shaderNS::INSTANCE_STATIC_MESH), currentCamera.view, currentCamera.projection, currentCamera.position);
	// プレイヤーの他のオブジェクトの描画
	tmpObject->otherRender(currentCamera.view, currentCamera.projection, currentCamera.position);

	//枯木の描画
	deadTree->render(currentCamera.view, currentCamera.projection, currentCamera.position);
	//木Aの描画
	treeA->render(currentCamera.view, currentCamera.projection, currentCamera.position);
	//木Bの描画
	treeB->render(currentCamera.view, currentCamera.projection, currentCamera.position);
	//石の描画
	stone->render(currentCamera.view, currentCamera.projection, currentCamera.position);

	// エネミーの描画
	enemyManager->render(currentCamera.view, currentCamera.projection, currentCamera.position);

	// ツリーの描画
	treeManager->render(currentCamera.view, currentCamera.projection, currentCamera.position);

	// アイテムの描画
	itemManager->render(currentCamera.view, currentCamera.projection, currentCamera.position);

}

//===================================================================================================================================
//【UI/2D描画】
//===================================================================================================================================
void Create::renderUI() {

	//device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);						// αブレンドを行う
	//device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);				// αソースカラーの指定
	//device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);			// αデスティネーションカラーの指定

	//device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	//device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// αテストを無効に
	device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//===================================================================================================================================
//【衝突判定処理】
//===================================================================================================================================
void Create::collisions()
{
	// プレイヤーとアイテム
	std::vector<Item*> itemList = itemManager->getList();
	for (size_t i = 0; i < itemList.size(); i++)
	{
		if (itemList[i]->sphereCollider.collide(tmpObject->getBodyCollide()->getCenter(),
			tmpObject->getRadius(), *itemList[i]->getMatrixWorld(), *tmpObject->getMatrixWorld()))
		{
			tmpObject->addSpeed(D3DXVECTOR3(0, 10, 0));
		}
	}
}

//===================================================================================================================================
//【AI処理】
//===================================================================================================================================
void Create::AI() {
}

//===================================================================================================================================
//【GUI作成処理】
//===================================================================================================================================
#ifdef _DEBUG
void Create::createGUI()
{
	ImGui::Text(sceneName.c_str());
	ImGui::Text("sceneTime = %f", sceneTimer);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("node:%d", testEffect->getList().nodeNum);

	tmpObject->outputGUI();			//プレイヤー
	//enemy->outputGUI();			//エネミー
	itemManager->outputGUI();		// アイテムマネージャ
	testField->outputGUI();			//テストフィールド
	camera->outputGUI();			//カメラ

}
#endif // _DEBUG
