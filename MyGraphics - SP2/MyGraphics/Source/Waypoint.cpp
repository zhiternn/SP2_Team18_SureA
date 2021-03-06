/******************************************************************************/
/*!
\file	Waypoint.cpp
\author Tang Zhi Tern
\par	email: 155134X@mymail.nyp.edu.sg
\brief
Class to define a Waypoint
*/
/******************************************************************************/

#include "Waypoint.h"
#include "Object.h"

vector<Waypoint*> Waypoint::waypointList;
float Waypoint::sizeH;
float Waypoint::sizeV;

/******************************************************************************/
/*!
\brief	Waypoint default constructor

\param	pos
	position of waypoint
\param	hSize
	horizontal size of waypoint
\param	vSize
	vertical size of waypoint
*/
/******************************************************************************/
Waypoint::Waypoint(Vector3 pos, float hSize, float vSize)
{
	position = pos;

	reachableWaypoints.clear();

	sizeH = hSize;
	sizeV = vSize;

	next = nullptr;
	target = nullptr;

	movementCost = 999.f; // supposedly required to be an infinite value
}

/******************************************************************************/
/*!
\brief	Waypoint destructor
*/
/******************************************************************************/
Waypoint::~Waypoint()
{
}

/******************************************************************************/
/*!
\brief	Reset the properties of this waypoint
	resets H costs, parenting node, and target node. Will not remove
	pre-generated reachable waypoints list.
*/
/******************************************************************************/
void Waypoint::Reset()
{
	movementCost = 999.f;
	next = nullptr;
	target = nullptr;
}

/******************************************************************************/
/*!
\brief	Stores waypoints into waypoint list
	Waypoints generated beyond map boundaries will not be stored

\param	mapSizeX
	map X boundary
\param	mapSizeZ
	map Z boundary
\param	waypointSizeH
	horizontal size of waypoint
\param	waypointSizeV
	vertical size of waypoint
*/
/******************************************************************************/
void StoreWaypoints(int mapSizeX, int mapSizeZ, float waypointSizeH, float waypointSizeV)
{
	Hitbox forWaypoint1;
	Hitbox forWaypoint2;
	Hitbox forWaypoint3;
	Hitbox forWaypoint4;

	forWaypoint1.SetSize(waypointSizeH, waypointSizeV, waypointSizeH);
	forWaypoint2.SetSize(waypointSizeH, waypointSizeV, waypointSizeH);
	forWaypoint3.SetSize(waypointSizeH, waypointSizeV, waypointSizeH);
	forWaypoint4.SetSize(waypointSizeH, waypointSizeV, waypointSizeH);

	for (size_t i = 0; i < Object::objectList.size(); ++i){
		if (Object::objectList[i]->hitbox.minPoint.y < waypointSizeV){
			forWaypoint1.SetPosition(Vector3(Object::objectList[i]->hitbox.position.x + (Object::objectList[i]->hitbox.sizeX / 2 + waypointSizeH / 2), waypointSizeV / 2, Object::objectList[i]->hitbox.position.z + (Object::objectList[i]->hitbox.sizeZ / 2 + waypointSizeH / 2)));
			forWaypoint2.SetPosition(Vector3(Object::objectList[i]->hitbox.position.x + (Object::objectList[i]->hitbox.sizeX / 2 + waypointSizeH / 2), waypointSizeV / 2, Object::objectList[i]->hitbox.position.z - (Object::objectList[i]->hitbox.sizeZ / 2 + waypointSizeH / 2)));
			forWaypoint3.SetPosition(Vector3(Object::objectList[i]->hitbox.position.x - (Object::objectList[i]->hitbox.sizeX / 2 + waypointSizeH / 2), waypointSizeV / 2, Object::objectList[i]->hitbox.position.z + (Object::objectList[i]->hitbox.sizeZ / 2 + waypointSizeH / 2)));
			forWaypoint4.SetPosition(Vector3(Object::objectList[i]->hitbox.position.x - (Object::objectList[i]->hitbox.sizeX / 2 + waypointSizeH / 2), waypointSizeV / 2, Object::objectList[i]->hitbox.position.z - (Object::objectList[i]->hitbox.sizeZ / 2 + waypointSizeH / 2)));

			if (!Hitbox::CheckHitBox(forWaypoint1) && forWaypoint1.position.x < mapSizeX / 2 && forWaypoint1.position.x > -mapSizeX / 2 && forWaypoint1.position.z < mapSizeZ / 2 && forWaypoint1.position.z > -mapSizeZ / 2)
				Waypoint::waypointList.push_back(new Waypoint(forWaypoint1.position, waypointSizeH, waypointSizeV));
			if (!Hitbox::CheckHitBox(forWaypoint2) && forWaypoint2.position.x < mapSizeX / 2 && forWaypoint2.position.x > -mapSizeX / 2 && forWaypoint2.position.z < mapSizeZ / 2 && forWaypoint2.position.z > -mapSizeZ / 2)
				Waypoint::waypointList.push_back(new Waypoint(forWaypoint2.position, waypointSizeH, waypointSizeV));
			if (!Hitbox::CheckHitBox(forWaypoint3) && forWaypoint3.position.x < mapSizeX / 2 && forWaypoint3.position.x > -mapSizeX / 2 && forWaypoint3.position.z < mapSizeZ / 2 && forWaypoint3.position.z > -mapSizeZ / 2)
				Waypoint::waypointList.push_back(new Waypoint(forWaypoint3.position, waypointSizeH, waypointSizeV));
			if (!Hitbox::CheckHitBox(forWaypoint4) && forWaypoint4.position.x < mapSizeX / 2 && forWaypoint4.position.x > -mapSizeX / 2 && forWaypoint4.position.z < mapSizeZ / 2 && forWaypoint4.position.z > -mapSizeZ / 2)
				Waypoint::waypointList.push_back(new Waypoint(forWaypoint4.position, waypointSizeH, waypointSizeV));
		}
	}
}

/******************************************************************************/
/*!
\brief	Check if 2 waypoints are in reach of each other
returns true if waypoint can reach checking waypoint without being obstructed

\param	toBeLinked
	waypoint to be checked against
*/
/******************************************************************************/
bool Waypoint::CheckLink(Waypoint toBeLinked)
{
	Hitbox collisionChecker;
	collisionChecker.SetSize(Waypoint::sizeH, Waypoint::sizeV, Waypoint::sizeH);

	if (this->position != toBeLinked.position){//Check if its comparing with itself
		float distance = (toBeLinked.position - this->position).Length();
		Vector3 pathDir = (toBeLinked.position - this->position).Normalized();
		pathDir.y = 0;

		for (float d = 0; d < distance; d += Waypoint::sizeH){
			if (d > distance){
				d = distance;
			}
			Vector3 pos = (this->position + pathDir * d);
			pos.y = Waypoint::sizeV / 2;
			collisionChecker.SetPosition(pos);

			if (Hitbox::CheckHitBox(collisionChecker)){//collided
				return false;
			}
		}
		return true;
	}
}

/******************************************************************************/
/*!
\brief	Push all reachable waypoints into this waypoint's reachable list
*/
/******************************************************************************/
void Waypoint::LinkWaypoints()
{
	Hitbox collisionChecker;
	collisionChecker.SetSize(Waypoint::sizeH, Waypoint::sizeV, Waypoint::sizeH);

	reachableWaypoints.clear();

	for (int j = 0; j < Waypoint::waypointList.size(); ++j){// Check waypoints one by one with gotten waypoint
		if (this->position != Waypoint::waypointList[j]->position){//Check if its comparing with itself
			float distance = (Waypoint::waypointList[j]->position - this->position).Length();
			Vector3 pathDir = (Waypoint::waypointList[j]->position - this->position).Normalized();
			pathDir.y = 0;
			bool collided = false;

			for (float d = 0; d < distance; d += Waypoint::sizeH){
				if (d > distance){
					d = distance;
				}
				Vector3 pos = (this->position + pathDir * d);
				pos.y = Waypoint::sizeV / 2;
				collisionChecker.SetPosition(pos);

				if (Hitbox::CheckHitBox(collisionChecker)){//collided
					collided = true;

					break;
				}
			}
			if (!collided){
				this->reachableWaypoints.push_back(Waypoint::waypointList[j]);
			}
		}
	}
}

/******************************************************************************/
/*!
\brief	Generates waypoints and link them to each other

\param	mapSizeX
	map X boundary
\param	mapSizeZ
	map Z boundary
\param	waypointSizeH
	horizontal size of waypoint
\param	waypointSizeV
	vertical size of waypoint
*/
/******************************************************************************/
void GenerateWaypoints(int mapSizeX, int mapSizeZ, float waypointSizeH, float waypointSizeV)
{
	Waypoint::sizeH = waypointSizeH;
	Waypoint::sizeV = waypointSizeV;

	StoreWaypoints(mapSizeX, mapSizeZ, waypointSizeH, waypointSizeV);
	//iterates through each waypoint and create a link to all reachable waypoints from curr waypoint
	for (vector<Waypoint*>::iterator it = Waypoint::waypointList.begin(); it != Waypoint::waypointList.end(); ++it){
		(*it)->LinkWaypoints();
	}
}

/******************************************************************************/
/*!
\brief	run Reset function for all waypoints in waypointList
*/
/******************************************************************************/
void ResetWaypoints()
{
	for (vector<Waypoint*>::iterator it = Waypoint::waypointList.begin(); it != Waypoint::waypointList.end(); ++it){
		(*it)->Reset();
	}
}