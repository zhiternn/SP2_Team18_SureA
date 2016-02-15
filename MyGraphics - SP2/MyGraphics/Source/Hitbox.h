#ifndef HITBOX_H
#define HITBOX_H

#include "Vector3.h"
#include <vector>

class Hitbox{
public:
	Hitbox(Vector3 pos = Vector3(0, 0, 0), float scaleX = 1, float scaleY = 1, float scaleZ = 1);
	~Hitbox();

	void SetSize(float scaleX, float scaleY, float scaleZ);
	void SetPivot(float x, float y, float z);
	void SetPosition(Vector3 pos);

	// ALL check functions return true if collide
	static bool CheckHitBox(Hitbox lhs, Vector3& pos, Vector3 oldPos, Hitbox* selfHitBox = nullptr);	// AABB - AABB list
	static bool CheckHitBox(Vector3 lhs);	// Point - AABB list

	Vector3 minPoint, maxPoint;
	Vector3 pivot;

	Vector3 position;
	float sizeX, sizeY, sizeZ;
private:
	void FinalizeHitbox();
};

#endif