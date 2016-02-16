#ifndef ENEMY_H
#define ENEMY_H

#include "Waypoint.h"

#include <vector>
#include <list>
#include <queue>

using std::vector;
using std::queue;
using std::list;

class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init(Vector3 pos, float speed);
	void Update(double dt);

	void FindPath(Vector3 destination);
	list<Waypoint*> Dijkstra(Waypoint* start, Waypoint* end);

	Vector3 position;
	list<Waypoint*>::iterator checkPoint;//determines at which waypoint of the path it is at
	list<Waypoint*> path;
private:
	float speed;
};

#endif