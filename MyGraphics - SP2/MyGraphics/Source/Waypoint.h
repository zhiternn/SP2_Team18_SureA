#ifndef WAYPOINT_H
#define WAYPOINT_H

#include "Hitbox.h"

#include <vector>

using std::vector;

class Waypoint
{
public:
	Waypoint(Vector3 pos, float hSize, float vSize);
	~Waypoint();

	void Reset();
	void LinkWaypoints();
	bool CheckLink(Waypoint toBeLinked);

	static vector<Waypoint*> waypointList;
	static float sizeH;
	static float sizeV;

	Vector3 position;
	float movementCost; //cost to move from start node to curr node
	Waypoint* next; // points to parenting node
	Waypoint* target; // nullptr if target is not reachable from this waypoint
	vector<Waypoint*> reachableWaypoints; // stores all reachable pre-generated waypoints

private:
};

void GenerateWaypoints(int sizeX, int sizeZ, float waypointSizeH, float waypointSizeV);
void ResetWaypoints();
#endif