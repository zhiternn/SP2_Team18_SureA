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
	NPC(Vector3 pos, Vector3 dir, float speed);
	virtual ~NPC();

	virtual void Update(double dt) = 0;

	void GoTo(Vector3 destination);

	Vector3 position;
	Hitbox hitbox;
	float facingYaw;
protected:

	float speed;

	Vector3 checkPointDir;
	const Vector3 defaultDirection;
	list<Waypoint*>::reverse_iterator checkPoint;//determines at which waypoint of the path it is at
	list<Waypoint*> path;

};

#endif