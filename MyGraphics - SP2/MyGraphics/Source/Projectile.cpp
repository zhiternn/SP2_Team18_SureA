#include "Projectile.h"
#include "Effect_Explosion.h"

Projectile::Projectile(Vector3 pos, Vector3 dir, float r, float s, int d)
{
	position = pos;
	direction = dir;
	deleteBullet = false;

	range = r;
	speed = s;
	damage = d;

	distanceTravelled = 0.f;
}

Projectile::~Projectile()
{
	delete this;
}

bool Projectile::Update(double dt)
{
	distanceTravelled += dt * speed;
	position += direction * dt * speed;

	if (Hitbox::CheckHitBox(position)){
		deleteBullet = true;

		Effect_Explosion::explosionList.push_back(new Effect_Explosion(position));
	}
	if (distanceTravelled >= range){
		deleteBullet = true;
	}
	 return deleteBullet;
}