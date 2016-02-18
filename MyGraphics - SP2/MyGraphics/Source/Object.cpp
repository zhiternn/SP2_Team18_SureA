#include "Object.h"

std::vector<Object*> Object::objectList;

Object::Object()
{
	position.Set(0, 0, 0);
	hitbox.SetSize(1, 1, 1);
	HP = 0;
	isInvulnerable = true;
	isDead = false;

	objectList.push_back(this);
}

Object::~Object()
{
	for (std::vector<Object*>::iterator it = Object::objectList.begin(); it != Object::objectList.end();){
		if ((*it)->isDead){
			it = Object::objectList.erase(it);
		}
		else{
			++it;
		}
	}
}

void Object::SetPosition(float x, float y, float z)
{
	position.Set(
	x,
	y,
	z
	);
	hitbox.SetPosition(Vector3(
		position.x,
		position.y, 
		position.z
		));
}

void Object::ReceiveDamage(int amount)
{
	if (!isInvulnerable){
		HP -= amount;

		if (HP < 0){
			isDead = true;
			delete this;
		}
	}
}

void Object::SetHealth(int amount)
{
	HP = amount;
	isInvulnerable = false;
}