#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Vector3.h"
#include "Hitbox.h"

class Projectile
{
public:
	Projectile(Vector3 pos, Vector3 dir, float r, float s, int d);
	~Projectile();

	bool Update(double dt);

	Vector3 position;
private:
	Vector3 direction;

	float range;
	float speed;
	float distanceTravelled;

	int damage;

	bool deleteBullet;
};

#endif