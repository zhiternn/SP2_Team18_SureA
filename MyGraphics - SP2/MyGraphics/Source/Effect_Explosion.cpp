#include "Effect_Explosion.h"

Effect_Explosion::Effect_Explosion(Vector3 pos):
Effect(pos)
{
	explosionScale = 0.01f;
	scale.Set(explosionScale, explosionScale, explosionScale);
}

Effect_Explosion::~Effect_Explosion()
{
}

void Effect_Explosion::Update(double dt)
{
	static const float EXPLOSION_SPEED = 10.f;

	explosionScale += (float)(EXPLOSION_SPEED * dt);

	scale.Set(
		explosionScale,
		explosionScale,
		explosionScale
		);

	if (explosionScale >= 1.f){
		effectOver = true;
	}
}