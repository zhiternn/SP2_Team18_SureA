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
	enum ENEMY_STATE
	{
		MOVE,
		HIT,
		FALL,
	};

	Enemy(Vector3 pos = Vector3(0, 0, 0), Vector3 dir = Vector3(0, 0, -1), float speed = 1.f);
	virtual ~Enemy();

	static vector<Enemy*> enemyList;

	virtual void Update(double dt);
	void SetHealth(int amount);
	void ReceiveDamage(int amount);

	
	bool reachedDestination;
	bool isDead;
	bool isHit;
private:

	ENEMY_STATE state;
	int HP;
};

#endif