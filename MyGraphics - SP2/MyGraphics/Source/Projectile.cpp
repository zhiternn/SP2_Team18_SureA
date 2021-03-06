#include "Projectile.h"
#include "Effect_Explosion.h"
#include "WorldValues.h"

vector<Projectile*> Projectile::projectileList;

Projectile::Projectile(Vector3 pos, Vector3 dir, float r, float s, int d)
{
	position = pos;
	direction = dir;
	deleteBullet = false;

	range = r;
	speed = s;
	damage = d;
	vSpeed = 0;

	distanceTravelled = 0.f;
}

Projectile::~Projectile()
{
}

void Projectile::Update(double dt)
{
	distanceTravelled += dt * speed;
	position += direction * dt * speed;
	vSpeed -= WV_GRAVITY/4 * dt;

	position.y += vSpeed;

	if (Hitbox::CheckHitBox(position, damage)){
		deleteBullet = true;

		Effect::effectList.push_back(new Effect_Explosion(position));
	}
	else if (distanceTravelled >= range){
		deleteBullet = true;
	}
}