#include "Enemy.h"

vector<Enemy*> Enemy::enemyList;

Enemy::Enemy(Vector3 pos, Vector3 dir, float speed) :
NPC(pos, dir, speed)
{
	state = FALL;

	isDead = false;
	HP = 15;

	hitbox.SetSize(
		1.5f,
		2.f,
		1.5f
	);

	isHit = false;
	reachedDestination = false;

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
			facingYaw = (defaultDirection.Cross(checkPointDir)).Dot(Vector3(0, 1, 0) * Math::RadianToDegree(acos(defaultDirection.Dot(checkPointDir))));
			position += checkPointDir * speed * dt;

			if ((position - (*checkPoint)->position).Length() <= Waypoint::sizeH / 2){
				 checkPoint++;
			}
		}
		else{
			reachedDestination = true;
		}
		break;

	case HIT:
		std::cout << " HIT" << std::endl;
		speed *= 1.5f;
		isHit = true;
		state = FALL;
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

void Enemy::SetHealth(int amount)
{
	HP = amount;
}

void Enemy::ReceiveDamage(int amount)
{
	HP -= amount;
	state = HIT;

	if (HP <= 0){
		isDead = true;
	}
}