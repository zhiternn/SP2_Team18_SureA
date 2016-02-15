#include "Effect_Explosion.h"
vector<Effect_Explosion*> Effect_Explosion::explosionList;

Effect_Explosion::Effect_Explosion(Vector3 pos)
{
	position = pos;
	scale = 0.01f;
	deleteExplosion = false;
}
Effect_Explosion::~Effect_Explosion()
{
	delete this;
}

bool Effect_Explosion::Update(double dt)
{
	static const float EXPLOSION_SPEED = 10.f;

	scale += (float)(EXPLOSION_SPEED * dt);

	if (scale >= 1.f){
		deleteExplosion = true;
	}

	return deleteExplosion;
}