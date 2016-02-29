#ifndef HITBOX_H
#define HITBOX_H

#include "Vector3.h"
#include "Projectile.h"

#include <vector>

using std::vector;

class Hitbox{
public:
	Hitbox(Vector3 pos = Vector3(0, 0, 0), float scaleX = 1, float scaleY = 1, float scaleZ = 1);
	virtual ~Hitbox();
	
	static vector<Hitbox*> hitboxList;

	void SetSize(float scaleX, float scaleY, float scaleZ);
	void SetPivot(float x, float y, float z);
	void SetPosition(Vector3 pos);

	// ALL check functions return true if collide
	static bool CheckHitBox(Hitbox& hitbox, Vector3 oldPos, bool& x, bool& y, bool& z); //Hitbox check for move-able objects
	static bool CheckHitBox(Vector3 lhs, int damage);	// Point -> AABB list
	static bool CheckHitBox(Hitbox lhs);	// AABB -> AABB list (For Waypoints)
	static bool CheckItems(Hitbox lhs, Hitbox rhs); // AABB->AABB (1 to 1 comparison)

	Vector3 minPoint, maxPoint;
	Vector3 pivot;

	Vector3 position;
	float sizeX, sizeY, sizeZ;
private:
	void FinalizeHitbox();
};

#endif