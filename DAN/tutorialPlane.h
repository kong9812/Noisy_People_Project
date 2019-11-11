//===================================================================================================================================
//【tutorialPlane.h】
// [作成者]HAL東京GP12A332 16 蔡 友剛
// [作成日]2019/11/05
// [更新日]2019/11/05
//===================================================================================================================================
#pragma once

//===================================================================================================================================
//【インクルード】
//===================================================================================================================================
#include "InstancingBillboard.h"

//===================================================================================================================================
//【名前空間】
//===================================================================================================================================
namespace tutorialPlaneNS
{
	enum TUTORIAL_PLANE_ID
	{
		PLANE_ENEMY,
		PLANE_TREE,
		PLANE_DIGITAL,
		PLANE_SKY,
		PLANE_SHIFT_0,
		PLANE_SHIFT_1,
		PLANE_CLEAR,
		PLANE_MAX
	};

	//===================================================================================================================================
	//【テストプレーンインスタンスクラス】
	//[使い方]	インスタンスクラスを継承して新たなクラスを作成し、
	//				のvoid update(float frameTime)関数をオーバーライドして、新たな振る舞いを作成する
	//===================================================================================================================================
	class PlaneInstance :public InstancingBillboardNS::Instance
	{
	public:
		//コンストラクタ
		PlaneInstance(D3DXVECTOR3 position);
		//更新
		virtual void update(float frameTime)override;
	private:
		int tmpCnt;
	};
}

//===================================================================================================================================
//【テストプレーンレンダラークラス】
//[使い方]	基本的には継承して、基底クラスの関数を使用していけばＯＫ
//				加えて何か仕様を追加したい場合は、適宜変更
//				基底クラスが、インスタンスの更新・削除・リスト管理を行ってくれている[実質マネージャー]
//===================================================================================================================================
class TutorialPlane :public InstancingBillboard
{
private:
	int planeStep;

public:
	TutorialPlane(const D3DXVECTOR3 position);
	~TutorialPlane();

	int getPlaneStep(void) { return planeStep; }
	void update(float frameTime, int inPlaneStep);
};
