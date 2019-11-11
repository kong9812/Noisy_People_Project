//===================================================================================================================================
//yCollisionManager.cppz
// [์ฌา]HALGP12A332 11 ์ ๗
// [์ฌ๚]2019/11/11
// [XV๚]2019/11/11
//===================================================================================================================================

//===================================================================================================================================
//yCN[hz
//===================================================================================================================================
#include "CollisionManager.h"

//===================================================================================================================================
//yusing้พz
//===================================================================================================================================
using namespace CollisionManagerNS;

//===================================================================================================================================
//yRXgN^z
//===================================================================================================================================
CollisionManager::CollisionManager()
{

}

//===================================================================================================================================
//yfXgN^z
//===================================================================================================================================
CollisionManager::~CollisionManager()
{
}


//===================================================================================================================================
//yีหป่z
//===================================================================================================================================
bool CollisionManager::collision(Object* obj1, Object* obj2)
{
	if (obj1->type == ObjectType::NONE || obj2->type == ObjectType::NONE)return false;

	int type1 = obj1->type;
	int type2 = obj2->type;

	switch (COMBI[type1][type2])
	{
		//PLAYER
	case PLAYER_PLAYER:	return playerAndPlayer((Player*)obj1, (Player*)obj2); break;
	case PLAYER_BULLET: return playerAndBullet((Player*)obj1, (Bullet*)obj2); break;

		//BULLET
	case BULLET_PLAYER: return playerAndBullet((Player*)obj1, (Bullet*)obj2); break;
	case BULLET_BULLET: break;

	default:break;
	}

	return false;
}


//===================================================================================================================================
//yvC[ <-> vC[z
//===================================================================================================================================
bool CollisionManager::playerAndPlayer(Player* player1, Player* player2)
{
	bool hit = false;
	hit = player1->getBodyCollide()->collide(
		player2->getBodyCollide()->getCenter(), player2->radius,
		player1->matrixWorld, player2->matrixWorld);

	if (hit)
	{
		D3DXVECTOR3 repulsion;//ฝญxNg
		float length = Base::between2VectorDirection(&repulsion, player1->position, player2->position);
		length = ((player1->radius+player2->radius)-length)/2.0f;
		player1->position -= repulsion * length;
		player2->position += repulsion * length;
		player1->Object::update();
		player2->Object::update();
	}

	return hit;
}

//===================================================================================================================================
//yvC[ <-> obgz
//===================================================================================================================================
bool CollisionManager::playerAndBullet(Player* player, Bullet* bullet)
{
	bool hit = false;



	return hit;
}