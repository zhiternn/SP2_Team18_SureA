#ifndef EFFECT_EXPLOSION_H
#define EFFECT_EXPLOSION_H

#include "Vector3.h"

#include <Vector>
using std::vector;

class Effect_Explosion
{
public:
	Effect_Explosion(Vector3 pos);
	~Effect_Explosion();

	static vector<Effect_Explosion*> explosionList;

	bool Update(double dt);

	Vector3 position;
	float scale;
private:
	
	bool deleteExplosion;
};

#endif