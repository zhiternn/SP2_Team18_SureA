#ifndef ENEMY_H
#define ENEMY_H

#include "NPC.h"

#include <vector>
#include <list>

using std::vector;
using std::list;

class Enemy : public NPC
{
public:
	Enemy(Vector3 pos = Vector3(0, 0, 0), float speed = 1.f);
	virtual  ~Enemy();

	virtual void Update(double dt);
};

#endif