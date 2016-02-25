#include "Effect.h"

vector<Effect*> Effect::effectList;

Effect::Effect(Vector3 pos)
{
	position = pos;
	scale.Set(1, 1, 1);
	translate.SetZero();
	rotate.SetZero();

	effectOver = false;
}

Effect::~Effect()
{
}