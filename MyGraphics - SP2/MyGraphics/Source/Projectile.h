#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Vector3.h"
#include "Hitbox.h"
#include "Sound.h"
#include <vector>

using std::vector;

class Projectile
{
public:
	Projectile(Vector3 pos, Vector3 dir, float r, float s, int d);
	~Projectile();

	void Update(double dt);

	static vector<Projectile*> projectileList;

	Vector3 position;
	bool deleteBullet;
private:
	Vector3 direction;

	float range;
	float speed;
	float distanceTravelled;
	float vSpeed;

	int damage;

	Sound sound;
};

#endif