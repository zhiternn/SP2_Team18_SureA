#ifndef WAYPOINT_H
#define WAYPOINT_H

#include "Hitbox.h"

#include <vector>
using std::vector;

class Waypoint
{
public:
	Waypoint(Vector3 pos)
	{
		position = pos;

		H = G = F = 0.f;

		parent = nullptr;
	}
	~Waypoint();

	void Reset()
	{
		H = G = F = 0.f;

		parent = nullptr;
	}

	static vector<Waypoint*> waypointList;

	//Distance between note and target
	float H; // Heuristic
	//Distance between each Waypoint
	float G; // Movement Cost

	float F; // (G + H)

	Vector3 position;

	Waypoint* parent; // A node to reach this node
}; 
vector<Waypoint*> Waypoint::waypointList;

void GenerateWaypoints(int sizeX, int sizeZ)
{
	Hitbox forWaypoint1;
	Hitbox forWaypoint2;
	Hitbox forWaypoint3;
	Hitbox forWaypoint4;

	forWaypoint1.SetSize(1, 1, 1);
	forWaypoint2.SetSize(1, 1, 1);
	forWaypoint3.SetSize(1, 1, 1);
	forWaypoint4.SetSize(1, 1, 1);

	for (size_t i = 0; i < Object::objectList.size(); ++i){
		if (Object::objectList[i]->hitbox.minPoint.y < 3.f){
			forWaypoint1.SetPosition(Vector3(Object::objectList[i]->hitbox.position.x + (Object::objectList[i]->hitbox.sizeX / 2 + 0.5f), 0.6f, Object::objectList[i]->hitbox.position.z + (Object::objectList[i]->hitbox.sizeZ / 2 + 0.5f)));
			forWaypoint2.SetPosition(Vector3(Object::objectList[i]->hitbox.position.x + (Object::objectList[i]->hitbox.sizeX / 2 + 0.5f), 0.6f, Object::objectList[i]->hitbox.position.z - (Object::objectList[i]->hitbox.sizeZ / 2 + 0.5f)));
			forWaypoint3.SetPosition(Vector3(Object::objectList[i]->hitbox.position.x - (Object::objectList[i]->hitbox.sizeX / 2 + 0.5f), 0.6f, Object::objectList[i]->hitbox.position.z + (Object::objectList[i]->hitbox.sizeZ / 2 + 0.5f)));
			forWaypoint4.SetPosition(Vector3(Object::objectList[i]->hitbox.position.x - (Object::objectList[i]->hitbox.sizeX / 2 + 0.5f), 0.6f, Object::objectList[i]->hitbox.position.z - (Object::objectList[i]->hitbox.sizeZ / 2 + 0.5f)));

			if (!Hitbox::CheckHitBox(forWaypoint1) && forWaypoint1.position.x < sizeX / 2 && forWaypoint1.position.x > -sizeX / 2 && forWaypoint1.position.z < sizeZ / 2 && forWaypoint1.position.z > -sizeZ / 2)
				Waypoint::waypointList.push_back(new Waypoint(forWaypoint1.position));
			if (!Hitbox::CheckHitBox(forWaypoint2) && forWaypoint2.position.x < sizeX / 2 && forWaypoint2.position.x > -sizeX / 2 && forWaypoint2.position.z < sizeZ / 2 && forWaypoint2.position.z > -sizeZ / 2)
				Waypoint::waypointList.push_back(new Waypoint(forWaypoint2.position));
			if (!Hitbox::CheckHitBox(forWaypoint3) && forWaypoint3.position.x < sizeX / 2 && forWaypoint3.position.x > -sizeX / 2 && forWaypoint3.position.z < sizeZ / 2 && forWaypoint3.position.z > -sizeZ / 2)
				Waypoint::waypointList.push_back(new Waypoint(forWaypoint3.position));
			if (!Hitbox::CheckHitBox(forWaypoint4) && forWaypoint4.position.x < sizeX / 2 && forWaypoint4.position.x > -sizeX / 2 && forWaypoint4.position.z < sizeZ / 2 && forWaypoint4.position.z > -sizeZ / 2)
				Waypoint::waypointList.push_back(new Waypoint(forWaypoint4.position));
		}
	}
}

void ResetWaypoints(){
	for (size_t i = 0; i < Waypoint::waypointList.size(); ++i){
		Waypoint::waypointList[i]->Reset();
	}
}

#endif