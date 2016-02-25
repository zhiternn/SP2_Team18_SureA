#ifndef EFFECT_H
#define EFFECT_H

#include "Vector3.h"

#include <Vector>

using std::vector;

class Effect
{
public:
	Effect(Vector3 pos);
	virtual ~Effect();

	static vector<Effect*> effectList;

	virtual void Update(double dt) = 0;

	Vector3 position;

	Vector3 scale; // scale X, Y, Z
	Vector3 rotate; // rotate pitch, yaw, roll
	Vector3 translate; // translate X, Y, Z

	bool effectOver;
protected:
};

#endif