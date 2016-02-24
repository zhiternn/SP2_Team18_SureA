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
	virtual ~Enemy();

	static vector<Enemy*> enemyList;

	virtual void Update(double dt);

	short state;
private:
	enum STATE
	{
		MOVE,
		HIT,
		FALL
	};
};

#endif