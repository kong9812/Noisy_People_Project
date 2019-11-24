//===================================================================================================================================
//【VisionState.h】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/11/17
// [更新日]2019/11/17
//===================================================================================================================================
#pragma once

//===================================================================================================================================
//【インクルード】
//===================================================================================================================================
#include "Player.h"

//===================================================================================================================================
//【名前空間】
//===================================================================================================================================
namespace visionNS {
	const float COST_TIME		= 1.0f;//パワー消費時間
	const int	COST			= (int)((float)playerNS::FULL_POWER / 20.0f);//電力消費量

	//===================================================================================================================================
	//【ビジョンステート】
	//===================================================================================================================================
	class VisionState :	public AbstractState
	{
	private:
		Player* player;
		float	costTimer;
	public:
		VisionState(Player* player);
		~VisionState();
		
		virtual void update(float frameTime);
		virtual void start();
		virtual void operation();
		virtual void physics();
		virtual void controlCamera();
		virtual AbstractState* transition();
		virtual void end();

	};

}
