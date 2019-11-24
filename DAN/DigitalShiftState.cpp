//===================================================================================================================================
//yDigitalShiftState.cppz
// [์ฌา]HALGP12A332 11 ์ ๗
// [์ฌ๚]2019/11/17
// [XV๚]2019/11/24
//===================================================================================================================================

//===================================================================================================================================
//yCN[hz
//===================================================================================================================================
#include "DigitalShiftState.h"
#include "NormalState.h"

//===================================================================================================================================
//yusing้พz
//===================================================================================================================================
using namespace playerNS;
using namespace digitalShiftNS;

//===================================================================================================================================
//yRXgN^z
//===================================================================================================================================
DigitalShiftState::DigitalShiftState(Player* player):AbstractState()
{
	//คสฺ
	this->player = player;
	stateTimer	= 0.0f;
	type		= DIGITAL_SHIFT;
	nextType	= NORMAL;
	stateName	= "DIGITAL_SHIFT";
	onTrans		= false;
	player->setValidOperation(
		DISABLE_OPERATION		//์s\
	);
	//ลLฺ
	shiftTimer = 0.0f;			//Vtgิ
}

//===================================================================================================================================
//yfXgN^z
//===================================================================================================================================
DigitalShiftState::~DigitalShiftState()
{
	
}

//===================================================================================================================================
//yJnz
//===================================================================================================================================
void DigitalShiftState::start()
{
}

//===================================================================================================================================
//yXVz
//===================================================================================================================================
void DigitalShiftState::update(float frameTime)
{
	this->frameTime = frameTime;
	stateTimer += frameTime;
	shiftTimer += frameTime;

	if (EFFECT_TIME > effectTimer && effectTimer >= 0.0f )
	{
		effectTimer += frameTime;
	}
	else if(effectTimer > EFFECT_TIME){
		//GtFNgใfW^Vtg๐ภs
		player->executionDigitalShift();
		effectTimer = -1.0f;
	}

	//๓ิJฺ
	if (shiftTimer > SHIFT_TIME)
	{
		player->returnTransitionCamera(0.5f);
		player->transState(NORMAL); return;//สํ๓ิษ฿้
	}

}

//===================================================================================================================================
//y์z
//===================================================================================================================================
void DigitalShiftState::operation()
{
	// ์
}

//===================================================================================================================================
//yจz
//===================================================================================================================================
void DigitalShiftState::physics()
{

}

//===================================================================================================================================
//yจz
//===================================================================================================================================
void DigitalShiftState::controlCamera()
{
	if (effectTimer> EFFECT_TIME) {
		//GtFNgใJ๐Jฺ
		player->transitionCamera();
	}

	player->controlCamera(frameTime);
}

//===================================================================================================================================
//y๓ิJฺz
//===================================================================================================================================
AbstractState* DigitalShiftState::transition()
{
	return new normalNS::NormalState(player);
}

//===================================================================================================================================
//yIนz
//===================================================================================================================================
void DigitalShiftState::end()
{

}



