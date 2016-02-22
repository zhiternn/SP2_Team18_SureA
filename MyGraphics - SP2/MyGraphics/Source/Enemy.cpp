#include "Enemy.h"

Enemy::Enemy(Vector3 pos, float speed) :
NPC(pos, speed)
{
}

Enemy::~Enemy()
{
}

void Enemy::Update(double dt)
{
	hitbox.SetPosition(position);

	if (position.y > Waypoint::sizeV / 2){
		position.y -= speed * dt;
	}
	else if (checkPoint != path.rend()){

		//MOVE TO
		checkPointDir = ((*checkPoint)->position - position).Normalized();
		position += checkPointDir * speed * dt;
		
		if ((position - (*checkPoint)->position).Length() <= Waypoint::sizeH / 2){
			checkPoint++;
		}
	}
}