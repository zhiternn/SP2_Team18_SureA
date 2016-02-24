#include "Enemy.h"

vector<Enemy*> Enemy::enemyList;

Enemy::Enemy(Vector3 pos, float speed) :
NPC(pos, speed)
{
	state = FALL;

	Enemy::enemyList.push_back(this);
}

Enemy::~Enemy()
{
	for (std::vector<Enemy*>::iterator it = enemyList.begin(); it != Enemy::enemyList.end();){
		if ((*it)->isDead){
			it = Enemy::enemyList.erase(it);
		}
		else{
			++it;
		}
	}
}

void Enemy::Update(double dt)
{
	hitbox.SetPosition(position);

	switch (state)
	{
	case MOVE:
		if (checkPoint != path.rend()){
			//MOVE TO
			checkPointDir = ((*checkPoint)->position - position).Normalized();
			position += checkPointDir * speed * dt;

			if ((position - (*checkPoint)->position).Length() <= Waypoint::sizeH / 2){
				 checkPoint++;
			}
		}
		break;

	case HIT:
		break;

	case FALL:
		if (position.y > Waypoint::sizeV / 2){
			position.y -= speed * dt;
		}
		else{
			position.y = Waypoint::sizeV / 2;
			state = MOVE;
		}
		break;

	default:
		break;
	}
}