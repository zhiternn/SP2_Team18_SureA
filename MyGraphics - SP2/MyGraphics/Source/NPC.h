#ifndef NPC_H
#define NPC_H

#include "Waypoint.h"

#include <vector>
#include <list>

using std::vector;
using std::list;

class NPC
{
public:
	NPC(Vector3 pos, float speed);
	~NPC();

	virtual void Update(double dt) = 0;

	static vector<NPC*> npcList;

	void GoTo(Vector3 destination);
	//list<Waypoint*> Dijkstra(Waypoint* start, Waypoint* end);

	Vector3 position;
protected:
	float speed;

	Vector3 checkPointDir;
	list<Waypoint*>::reverse_iterator checkPoint;//determines at which waypoint of the path it is at
	list<Waypoint*> path;
};

void UpdateNPCs(double dt);
void RenderNPCs();

#endif