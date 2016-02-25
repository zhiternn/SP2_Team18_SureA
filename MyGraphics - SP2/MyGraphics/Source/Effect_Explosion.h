#ifndef EFFECT_EXPLOSION_H
#define EFFECT_EXPLOSION_H

#include "Effect.h"

class Effect_Explosion : public Effect
{
public:
	Effect_Explosion(Vector3 pos = Vector3(0, 0, 0));
	virtual ~Effect_Explosion();

	virtual void Update(double dt);

private:
	float explosionScale;
};

#endif