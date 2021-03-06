#include "Hitbox.h"
#include "Object.h"
#include "ItemBox.h"
#include "Enemy.h"

vector<Hitbox*> Hitbox::hitboxList;

Hitbox::Hitbox(Vector3 pos, float scaleX, float scaleY, float scaleZ)
{
	pivot.Set(0, 0, 0);

	position.Set(pos.x, pos.y, pos.z);
	maxPoint.Set(
		scaleX*0.5 + pos.x,
		scaleY*0.5 + pos.y,
		scaleZ*0.5 + pos.z
	);
	minPoint.Set(
		-scaleX*0.5 + pos.x,
		-scaleY*0.5 + pos.y,
		-scaleZ*0.5 + pos.z
	);

	Hitbox::hitboxList.push_back(this);
}

Hitbox::~Hitbox()
{
}

void Hitbox::SetSize(float scaleX, float scaleY, float scaleZ)
{
	this->sizeX = scaleX;
	this->sizeY = scaleY;
	this->sizeZ = scaleZ;

	SetPosition(position);
}

void Hitbox::SetPosition(Vector3 pos)
{
	position = pos;

	FinalizeHitbox();
}

void Hitbox::SetPivot(float x, float y, float z)
{
	pivot.Set(x, y, z);
	
	FinalizeHitbox();
}

void Hitbox::FinalizeHitbox()
{
	maxPoint.Set(
		sizeX*0.5 + position.x + pivot.x,
		sizeY*0.5 + position.y + pivot.y,
		sizeZ*0.5 + position.z + pivot.z
		);
	minPoint.Set(
		-sizeX*0.5 + position.x + pivot.x,
		-sizeY*0.5 + position.y + pivot.y,
		-sizeZ*0.5 + position.z + pivot.z
		);
}

bool Hitbox::CheckHitBox(Hitbox& hitbox, Vector3 oldPos, bool& x, bool& y, bool& z)
{
	bool collided = false;
	for (size_t i = 0; i < Object::objectList.size(); ++i){
		if (
			hitbox.maxPoint.x > Object::objectList[i]->hitbox.minPoint.x &&
			hitbox.minPoint.x < Object::objectList[i]->hitbox.maxPoint.x &&
			hitbox.maxPoint.y > Object::objectList[i]->hitbox.minPoint.y &&
			hitbox.minPoint.y < Object::objectList[i]->hitbox.maxPoint.y &&
			hitbox.maxPoint.z > Object::objectList[i]->hitbox.minPoint.z &&
			hitbox.minPoint.z < Object::objectList[i]->hitbox.maxPoint.z &&
			&hitbox != &(Object::objectList[i]->hitbox)
			){
			collided = true;
			float xDistMoved = hitbox.position.x - oldPos.x;
			float yDistMoved = hitbox.position.y - oldPos.y;
			float zDistMoved = hitbox.position.z - oldPos.z;

			//CHECK X
			if (
				hitbox.maxPoint.x > Object::objectList[i]->hitbox.minPoint.x &&
				hitbox.minPoint.x < Object::objectList[i]->hitbox.maxPoint.x &&
				hitbox.maxPoint.y - yDistMoved > Object::objectList[i]->hitbox.minPoint.y &&
				hitbox.minPoint.y - yDistMoved < Object::objectList[i]->hitbox.maxPoint.y &&
				hitbox.maxPoint.z - zDistMoved > Object::objectList[i]->hitbox.minPoint.z &&
				hitbox.minPoint.z - zDistMoved < Object::objectList[i]->hitbox.maxPoint.z
				){
				x = true;
			}
			//CHECK Y
			if (
				hitbox.maxPoint.x - xDistMoved > Object::objectList[i]->hitbox.minPoint.x &&
				hitbox.minPoint.x - xDistMoved < Object::objectList[i]->hitbox.maxPoint.x &&
				hitbox.maxPoint.y > Object::objectList[i]->hitbox.minPoint.y &&
				hitbox.minPoint.y < Object::objectList[i]->hitbox.maxPoint.y &&
				hitbox.maxPoint.z - zDistMoved > Object::objectList[i]->hitbox.minPoint.z &&
				hitbox.minPoint.z - zDistMoved < Object::objectList[i]->hitbox.maxPoint.z
				){
				y = true;
			}
			//CHECK Z
			if (
				hitbox.maxPoint.x - xDistMoved > Object::objectList[i]->hitbox.minPoint.x &&
				hitbox.minPoint.x - xDistMoved < Object::objectList[i]->hitbox.maxPoint.x &&
				hitbox.maxPoint.y - yDistMoved > Object::objectList[i]->hitbox.minPoint.y &&
				hitbox.minPoint.y - yDistMoved < Object::objectList[i]->hitbox.maxPoint.y &&
				hitbox.maxPoint.z > Object::objectList[i]->hitbox.minPoint.z &&
				hitbox.minPoint.z < Object::objectList[i]->hitbox.maxPoint.z
				){
				z = true;
			}
		}
	}

	return collided;
}

bool Hitbox::CheckHitBox(Hitbox lhs)
{
	for (size_t i = 0; i < Object::objectList.size(); ++i){
		if (Object::objectList[i]->toBeIgnored != true){
			if (
				//check agasint objs
				lhs.maxPoint.x > Object::objectList[i]->hitbox.minPoint.x &&
				lhs.minPoint.x < Object::objectList[i]->hitbox.maxPoint.x &&
				lhs.maxPoint.y > Object::objectList[i]->hitbox.minPoint.y &&
				lhs.minPoint.y < Object::objectList[i]->hitbox.maxPoint.y &&
				lhs.maxPoint.z > Object::objectList[i]->hitbox.minPoint.z &&
				lhs.minPoint.z < Object::objectList[i]->hitbox.maxPoint.z
				||
				//objs check against this
				//counter checker for accuracy
				Object::objectList[i]->hitbox.maxPoint.x > lhs.minPoint.x &&
				Object::objectList[i]->hitbox.minPoint.x < lhs.maxPoint.x &&
				Object::objectList[i]->hitbox.maxPoint.y > lhs.minPoint.y &&
				Object::objectList[i]->hitbox.minPoint.y < lhs.maxPoint.y &&
				Object::objectList[i]->hitbox.maxPoint.z > lhs.minPoint.z &&
				Object::objectList[i]->hitbox.minPoint.z < lhs.maxPoint.z
				){
				return true;
			}
		}
	}
	return false;
}

bool Hitbox::CheckHitBox(Vector3 lhs, int damage)
{
	for (size_t i = 0; i < Object::objectList.size(); ++i){
		if (
			lhs.x > Object::objectList[i]->hitbox.minPoint.x &&
			lhs.x < Object::objectList[i]->hitbox.maxPoint.x &&
			lhs.y > Object::objectList[i]->hitbox.minPoint.y &&
			lhs.y < Object::objectList[i]->hitbox.maxPoint.y &&
			lhs.z > Object::objectList[i]->hitbox.minPoint.z &&
			lhs.z < Object::objectList[i]->hitbox.maxPoint.z
			){
			Object::objectList[i]->ReceiveDamage(damage);

			return true;
		}
	}
	for (size_t i = 0; i < Enemy::enemyList.size(); ++i){
		if (
			lhs.x > Enemy::enemyList[i]->hitbox.minPoint.x &&
			lhs.x < Enemy::enemyList[i]->hitbox.maxPoint.x &&
			lhs.y > Enemy::enemyList[i]->hitbox.minPoint.y &&
			lhs.y < Enemy::enemyList[i]->hitbox.maxPoint.y &&
			lhs.z > Enemy::enemyList[i]->hitbox.minPoint.z &&
			lhs.z < Enemy::enemyList[i]->hitbox.maxPoint.z
			){
			Enemy::enemyList[i]->ReceiveDamage(damage);

			return true;
		}
	}

	return false;
}

bool Hitbox::CheckItems(Hitbox lhs, Hitbox rhs)
{
		if (
			lhs.maxPoint.x > rhs.minPoint.x &&
			lhs.minPoint.x < rhs.maxPoint.x &&
			lhs.maxPoint.y > rhs.minPoint.y &&
			lhs.minPoint.y < rhs.maxPoint.y &&
			lhs.maxPoint.z > rhs.minPoint.z &&
			lhs.minPoint.z < rhs.maxPoint.z
			||
			rhs.maxPoint.x > lhs.minPoint.x &&
			rhs.minPoint.x < lhs.maxPoint.x &&
			rhs.maxPoint.y > lhs.minPoint.y &&
			rhs.minPoint.y < lhs.maxPoint.y &&
			rhs.maxPoint.z > lhs.minPoint.z &&
			rhs.minPoint.z < lhs.maxPoint.z
			){
			return true;
		}
		else{
			return false;
		}
}