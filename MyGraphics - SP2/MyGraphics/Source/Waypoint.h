#ifndef WAYPOINT_H
#define WAYPOINT_H

#include "Hitbox.h"

#include <map>
#include <vector>

using std::vector;
using std::map;

class Waypoint
{
public:
	Waypoint(Vector3 pos, float hSize, float vSize);
	~Waypoint();

	void Reset();
	void LinkWaypoints();

	static vector<Waypoint*> waypointList;
	static float sizeH;
	static float sizeV;

	Vector3 position;
	float movementCost; //cost to move from start node to curr node
	Waypoint* next;
	map<float, Waypoint*> reachableWaypoints;
private:
};

void GenerateWaypoints(int sizeX, int sizeZ, float waypointSizeH, float waypointSizeV);
void ResetWaypoints();
#endif