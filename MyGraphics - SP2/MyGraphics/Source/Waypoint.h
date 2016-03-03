/******************************************************************************/
/*!
\file	Waypoint.h
\author Tang Zhi Tern
\par	email: 155134X@mymail.nyp.edu.sg
\brief
Class to define a Waypoint
*/
/******************************************************************************/

#ifndef WAYPOINT_H
#define WAYPOINT_H

#include "Hitbox.h"

#include <vector>

using std::vector;

/******************************************************************************/
/*!
Class Vector3:
\brief	Defines a Waypoint and its required variables and methods
*/
/******************************************************************************/
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
	Waypoint* next; // pointer to parent node
	Waypoint* target;
	vector<Waypoint*> reachableWaypoints; // list of reachable pre-generated waypoints
private:
};

void GenerateWaypoints(int sizeX, int sizeZ, float waypointSizeH, float waypointSizeV);
void ResetWaypoints();

#endif //WAYPOINT_H