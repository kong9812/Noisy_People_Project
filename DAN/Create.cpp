//===================================================================================================================================
//�yCreate.cpp�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/09/20
// [�X�V��]2019/10/18
//===================================================================================================================================

//===================================================================================================================================
//�y�C���N���[�h�z
//===================================================================================================================================
#include "Create.h"

//===================================================================================================================================
//�yusing�錾�z
//===================================================================================================================================
using namespace createNS;

//===================================================================================================================================
//�y�R���X�g���N�^�z
//===================================================================================================================================
Create::Create()
{
	sceneName = "Scene -Create-";

	nextScene = SceneList::RESULT;

	//�V�[���̍X�V
	SoundInterface::SwitchAudioBuffer(SceneList::CREATE);

	//�G�l�~�[�c�[��
	enemyTools = new ENEMY_TOOLS;
}

//===================================================================================================================================
//�y�f�X�g���N�^�z
//===================================================================================================================================
Create::~Create()
{
	//�G�l�~�[�c�[��
	SAFE_DELETE(enemyTools);
}

//===================================================================================================================================
//�y�������z
//===================================================================================================================================
void Create::initialize() {

	//player
	player = new Player;

	//-----�����e�X�g�]�[�����̂P---------------
	//enemy = new Enemy;
	//camera = new Camera;

	//camera->initialize(WINDOW_WIDTH, WINDOW_HEIGHT);
	//camera->setTarget(enemy->getPosition());
	//camera->setTargetX(&enemy->getAxisX()->direction);
	//camera->setTargetY(&enemy->getAxisY()->direction);
	//camera->setTargetZ(&enemy->getAxisZ()->direction);
	//camera->setRelative(CAMERA_RELATIVE_QUATERNION);
	//camera->setGaze(D3DXVECTOR3(0, 0, 0));
	//camera->setRelativeGaze(CAMERA_RELATIVE_GAZE);
	//camera->setUpVector(D3DXVECTOR3(0, 1, 0));
	//camera->setFieldOfView((D3DX_PI / 18) * 10);
	//-------------------------------------------

	//camera
	camera = new Camera;
	camera->initialize(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	camera->setTarget(player->getPosition());
	camera->setTargetX(&player->getAxisX()->direction);
	camera->setTargetY(&player->getAxisY()->direction);
	camera->setTargetZ(&player->getAxisZ()->direction);
	camera->setRelative(CAMERA_RELATIVE_QUATERNION);
	camera->setGaze(D3DXVECTOR3(0, 0, 0));
	camera->setRelativeGaze(CAMERA_RELATIVE_GAZE);
	camera->setUpVector(D3DXVECTOR3(0, 1, 0));
	camera->setFieldOfView((D3DX_PI / 18) * 9);

	//light
	light = new Light;
	light->initialize();

	//�e�X�g�t�B�[���h
	testField = new Object();
	testFieldRenderer = new StaticMeshObject(staticMeshNS::reference(staticMeshNS::YAMADA_TEST_ZONE));
	testFieldRenderer->generateObject(testField);
	testField->initialize(&D3DXVECTOR3(0, 0, 0));

	//�v���C���[�̏�����
	player->initialize(inputNS::DINPUT_1P, 0);
	player->setCamera(camera);	//�J�����|�C���^�̃Z�b�g
	playerRenderer = new StaticMeshObject(staticMeshNS::reference(staticMeshNS::YAMADA_ROBOT2));
	playerRenderer->generateObject(player);
	player->configurationGravityWithRay(testField->getPosition(), testFieldRenderer->getStaticMesh()->mesh, testField->getMatrixWorld());	//�d�͂�ݒ�

	//�͖؂̏�����
	deadTree = new DeadTree();
	//��A�̏�����
	treeA = new TreeTypeA();
	//��B�̏�����
	treeB = new TreeTypeB();
	//�΂̏�����
	stone = new Stone();

	// �T�E���h�̍Đ�
	//sound->play(soundNS::TYPE::BGM_GAME, soundNS::METHOD::LOOP);

	//�e�L�X�g�̏�����
	//text.initialize(direct3D9->device,10,10, 0xff00ff00);
	//text2.initialize(direct3D9->device,11,11, 0xff0000ff);

	//�G�t�F�N�g�i�C���X�^���V���O�j�e�X�g
	testEffect = new TestEffect();

	//-----�����e�X�g�]�[������2---------------
	//enemy->setDebugEnvironment();
	//enemy->setCamera(camera);	//�J�����̃Z�b�g
	//enemy->configurationGravityWithRay(testField->getPosition(), testField->getStaticMesh()->mesh, testField->getMatrixWorld());	//�d�͂�ݒ�
	//-----------------------------------------

	// �c���[
	treeManager = new TreeManager;
	treeManager->initialize();

	// �A�C�e��
	itemManager = new ItemManager;
	itemManager->initialize();

	// �e���b�v
	telop = new Telop;
	telop->initialize();

	// AI
	aiDirector = new AIDirector;
	aiDirector->initialize();
	naviAI = new NavigationMesh(staticMeshNS::reference(staticMeshNS::SAMPLE_NAVMESH));
	naviAI->initialize();
}

//===================================================================================================================================
//�y�I�������z
//===================================================================================================================================
void Create::uninitialize() {
	SAFE_DELETE(camera);
	SAFE_DELETE(light);
	SAFE_DELETE(testField);
	SAFE_DELETE(testFieldRenderer);
	SAFE_DELETE(player);
	SAFE_DELETE(playerRenderer);
	SAFE_DELETE(deadTree);
	SAFE_DELETE(treeA);
	SAFE_DELETE(treeB);
	SAFE_DELETE(stone);
	SAFE_DELETE(testEffect);
	SAFE_DELETE(treeManager);
	SAFE_DELETE(itemManager);
	SAFE_DELETE(telop);
	SAFE_DELETE(aiDirector);
}

//===================================================================================================================================
//�y�X�V�z
//===================================================================================================================================
void Create::update(float _frameTime) {

	sceneTimer += _frameTime;
	frameTime = _frameTime;

	//�y���������z
	//�t���[�����Ԃ���10FPS���̎��̎��Ԃ�蒷���ꍇ�́A���������i�X�V���Ȃ��j
	//���t���[�����Ԃɏ������Ă��鏈��������ɋ@�\���Ȃ�����
	if (frameTime > 0.10)return;

	//�G�t�F�N�g�i�C���X�^���V���O�j�e�X�g
	testEffect->update(frameTime);

	//�e�X�g�t�B�[���h�̍X�V
	testField->update();
	testFieldRenderer->update();

	//�v���C���[�̍X�V
	player->update(frameTime);

	// �G�l�~�[�̍X�V
	//enemy->update(frameTime);

	// �c���[�̍X�V
	treeManager->update(frameTime);

	// �A�C�e���̍X�V
	if (input->wasKeyPressed('0'))
	{
		itemNS::ItemData unko = { 0, itemNS::BATTERY, *player->getPosition() };
		itemManager->createItem(&unko);
	}
	if (input->wasKeyPressed('9'))
	{
		itemManager->uninitialize();
	}
	itemManager->update(frameTime);

	// �e���b�v�̍X�V
	telop->update(frameTime);

	////�J�����̍X�V
	//camera->update();
	playerRenderer->update();

	//�͖؂̍X�V
	deadTree->update();
	//��A�̍X�V
	treeA->update();
	//��B�̍X�V
	treeB->update();
	//�΂̍X�V
	stone->update();

	//�G�l�~�[�c�[���̍X�V
	enemyTools->outputEnemyToolsGUI(*player->getPosition(), player->getAxisZ()->direction);
	enemyTools->update();

	//�J�����̍X�V
	camera->update();

	//sound->updateSound(*player->getPosition(), player->getAxisZ()->direction);

	// Enter�܂��́Z�{�^���Ń��U���g��
	if (input->wasKeyPressed(VK_RETURN) ||
		input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::A) ||
		input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::A))
	{
		// �T�E���h�̍Đ�
		//sound->play(soundNS::TYPE::SE_DECISION, soundNS::METHOD::PLAY);
		// �V�[���J��
		changeScene(nextScene);
	}

}

//===================================================================================================================================
//�y�`��z
//===================================================================================================================================
void Create::render() {

	//1P�J�����E�E�B���h�E
	camera->renderReady();
	direct3D9->changeViewport1PWindow();
	render3D(*camera);

	//2P�J�����E�E�B���h�E
	camera->renderReady();
	direct3D9->changeViewport2PWindow();
	render3D(*camera);

	//UI
	direct3D9->changeViewportFullWindow();
	renderUI();
}

//===================================================================================================================================
//�y3D�`��z
//===================================================================================================================================
void Create::render3D(Camera currentCamera) {


	//�e�X�g�t�B�[���h�̕`��
	testField->setAlpha(0.1f);
	testFieldRenderer->render(*shaderNS::reference(shaderNS::INSTANCE_STATIC_MESH), currentCamera.view, currentCamera.projection, currentCamera.position);

	//�G�t�F�N�g�i�C���X�^���V���O�j�e�X�g
	testEffect->render(currentCamera.view, currentCamera.projection, currentCamera.position);

	// �v���C���[�̕`��
	playerRenderer->render(*shaderNS::reference(shaderNS::INSTANCE_STATIC_MESH), currentCamera.view, currentCamera.projection, currentCamera.position);
	// �v���C���[�̑��̃I�u�W�F�N�g�̕`��
	player->otherRender(currentCamera.view, currentCamera.projection, currentCamera.position);

	//�͖؂̕`��
	deadTree->render(currentCamera.view, currentCamera.projection, currentCamera.position);
	//��A�̕`��
	treeA->render(currentCamera.view, currentCamera.projection, currentCamera.position);
	//��B�̕`��
	treeB->render(currentCamera.view, currentCamera.projection, currentCamera.position);
	//�΂̕`��
	stone->render(currentCamera.view, currentCamera.projection, currentCamera.position);

	// �G�l�~�[�̕`��
	//enemy->render(currentCamera.view, currentCamera.projection, currentCamera.position);

	//�G�l�~�[�c�[���̕`��(test�p)
	enemyTools->render(currentCamera.view, currentCamera.projection, currentCamera.position);

	// �c���[�̕`��
	treeManager->render(currentCamera.view, currentCamera.projection, currentCamera.position);

	// �A�C�e���̕`��
	itemManager->render(currentCamera.view, currentCamera.projection, currentCamera.position);

#ifdef DEBUG_NAVIMESH
#endif
}

//===================================================================================================================================
//�yUI/2D�`��z
//===================================================================================================================================
void Create::renderUI() {

	//device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);						// ���u�����h���s��
	//device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);				// ���\�[�X�J���[�̎w��
	//device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);			// ���f�X�e�B�l�[�V�����J���[�̎w��

	//device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	//device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// ���e�X�g�𖳌���
	device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	telop->render();	// �e���b�v�̕`��
}

//===================================================================================================================================
//�y�Փ˔��菈���z
//===================================================================================================================================
void Create::collisions()
{
	// �v���C���[�ƃA�C�e��
	std::vector<Item*> itemList = itemManager->getList();
	for (size_t i = 0; i < itemList.size(); i++)
	{
		if (itemList[i]->sphereCollider.collide(player->getBodyCollide()->getCenter(),
			player->getRadius(), *itemList[i]->getMatrixWorld(), *player->getMatrixWorld()))
		{
			player->addSpeed(D3DXVECTOR3(0, 10, 0));
		}
	}
}

//===================================================================================================================================
//�yAI�����z
//===================================================================================================================================
void Create::AI() {
	aiDirector->run();		// ���^AI���s
}

//===================================================================================================================================
//�yGUI�쐬�����z
//===================================================================================================================================
#ifdef _DEBUG
void Create::createGUI()
{
	ImGui::Text(sceneName.c_str());
	ImGui::Text("sceneTime = %f", sceneTimer);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("node:%d", testEffect->getList().nodeNum);

	player->outputGUI();			//�v���C���[
	//enemy->outputGUI();			//�G�l�~�[
	itemManager->outputGUI();		// �A�C�e���}�l�[�W��
	testField->outputGUI();			//�e�X�g�t�B�[���h
	camera->outputGUI();			//�J����
	naviAI->outputGUI();			//�i�r�Q�[�V����AI

}
#endif // _DEBUG