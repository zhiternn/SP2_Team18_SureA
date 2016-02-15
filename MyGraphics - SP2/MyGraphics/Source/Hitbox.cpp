#include "Hitbox.h"
#include "Object.h"

Hitbox::Hitbox(Vector3 pos, float scaleX, float scaleY, float scaleZ)
{
	this->sizeX = scaleX;
	this->sizeY = scaleY;
	this->sizeZ = scaleZ;

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

bool Hitbox::CheckHitBox(Hitbox lhs, Vector3& pos, Vector3 oldPos, Hitbox* selfHitBox)
{
	bool collided = false;
	for (size_t i = 0; i < Object::objectList.size(); ++i){
		if (
			lhs.maxPoint.x > Object::objectList[i]->hitbox.minPoint.x &&
			lhs.minPoint.x < Object::objectList[i]->hitbox.maxPoint.x &&
			lhs.maxPoint.y > Object::objectList[i]->hitbox.minPoint.y &&
			lhs.minPoint.y < Object::objectList[i]->hitbox.maxPoint.y &&
			lhs.maxPoint.z > Object::objectList[i]->hitbox.minPoint.z &&
			lhs.minPoint.z < Object::objectList[i]->hitbox.maxPoint.z &&
			selfHitBox != &(Object::objectList[i]->hitbox)
		){
			collided = true;
			float xDistMoved = pos.x - oldPos.x;
			float yDistMoved = pos.y - oldPos.y;
			float zDistMoved = pos.z - oldPos.z;

			//CHECK X
			if (
				lhs.maxPoint.x > Object::objectList[i]->hitbox.minPoint.x &&
				lhs.minPoint.x < Object::objectList[i]->hitbox.maxPoint.x &&
				lhs.maxPoint.y - yDistMoved > Object::objectList[i]->hitbox.minPoint.y &&
				lhs.minPoint.y - yDistMoved < Object::objectList[i]->hitbox.maxPoint.y &&
				lhs.maxPoint.z - zDistMoved > Object::objectList[i]->hitbox.minPoint.z &&
				lhs.minPoint.z - zDistMoved < Object::objectList[i]->hitbox.maxPoint.z
				){
				pos.x = oldPos.x;
			}
			//CHECK Y
			if (
				lhs.maxPoint.x - xDistMoved > Object::objectList[i]->hitbox.minPoint.x &&
				lhs.minPoint.x - xDistMoved < Object::objectList[i]->hitbox.maxPoint.x &&
				lhs.maxPoint.y > Object::objectList[i]->hitbox.minPoint.y &&
				lhs.minPoint.y < Object::objectList[i]->hitbox.maxPoint.y &&
				lhs.maxPoint.z - zDistMoved > Object::objectList[i]->hitbox.minPoint.z &&
				lhs.minPoint.z - zDistMoved < Object::objectList[i]->hitbox.maxPoint.z
				){
				pos.y = oldPos.y;
			}
			//CHECK Z
			if (
				lhs.maxPoint.x - xDistMoved > Object::objectList[i]->hitbox.minPoint.x &&
				lhs.minPoint.x - xDistMoved < Object::objectList[i]->hitbox.maxPoint.x &&
				lhs.maxPoint.y - yDistMoved > Object::objectList[i]->hitbox.minPoint.y &&
				lhs.minPoint.y - yDistMoved < Object::objectList[i]->hitbox.maxPoint.y &&
				lhs.maxPoint.z > Object::objectList[i]->hitbox.minPoint.z &&
				lhs.minPoint.z < Object::objectList[i]->hitbox.maxPoint.z
				){
				pos.z = oldPos.z;
			}
			lhs.SetPosition(pos);
		}
	}
	return collided;
}

bool Hitbox::CheckHitBox(Vector3 lhs)
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
			Object::objectList[i]->ReceiveDamage(5);

			return true;
		}
	}
	return false;
}