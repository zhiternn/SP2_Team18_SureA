#include "Object.h"

std::vector<Object*> Object::objectList;

Object::Object()
{
	position.Set(0, 0, 0);
	hitbox.SetSize(1, 1, 1);
	HP = 0;
	isInvulnerable = true;

	objectList.push_back(this);
}

Object::~Object()
{
}

void Object::SetPosition(float x, float y, float z)
{
	position.Set(
	position.x + x,
	position.y + y,
	position.z + z
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

		if (HP < 0)
			delete this;
	}
}

void Object::SetHealth(int amount)
{
	HP = amount;
	isInvulnerable = false;
}