#ifndef NPC_H
#define NPC_H

#include "Waypoint.h"
#include "Hitbox.h"

#include <vector>
#include <list>

using std::vector;
using std::list;

class NPC
{
public:
	NPC(Vector3 pos, float speed);
	virtual ~NPC();

	virtual void Update(double dt) = 0;

	static vector<NPC*> npcList;

	void GoTo(Vector3 destination);
	void SetHealth(int amount);
	void ReceiveDamage(int amount);

	Vector3 position;
	Hitbox hitbox;
protected:

	float speed;

	Vector3 checkPointDir;
	list<Waypoint*>::reverse_iterator checkPoint;//determines at which waypoint of the path it is at
	list<Waypoint*> path;

	int HP;
	bool isDead;
	
};

#endif