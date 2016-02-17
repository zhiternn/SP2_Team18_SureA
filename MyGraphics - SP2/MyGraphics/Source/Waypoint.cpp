#include "Waypoint.h"
#include "Object.h"

vector<Waypoint*> Waypoint::waypointList;
float Waypoint::sizeH;
float Waypoint::sizeV;

Waypoint::Waypoint(Vector3 pos, float hSize, float vSize)
{
	position = pos;

	reachableWaypoints.clear();

	sizeH = hSize;
	sizeV = vSize;

	movementCost = 999.f; // supposedly required to be an infinite value
}
Waypoint::~Waypoint()
{
}

void Waypoint::Reset()
{
	movementCost = 999.f;
}

void StoreWaypoints(int mapSizeX, int mapSizeZ, float waypointSizeH, float waypointSizeV)
{
	Hitbox forWaypoint1;
	Hitbox forWaypoint2;
	Hitbox forWaypoint3;
	Hitbox forWaypoint4;

	forWaypoint1.SetSize(waypointSizeH, 1, waypointSizeH);
	forWaypoint2.SetSize(waypointSizeH, 1, waypointSizeH);
	forWaypoint3.SetSize(waypointSizeH, 1, waypointSizeH);
	forWaypoint4.SetSize(waypointSizeH, 1, waypointSizeH);

	for (size_t i = 0; i < Object::objectList.size(); ++i){
		if (Object::objectList[i]->hitbox.minPoint.y < 3.f){
			forWaypoint1.SetPosition(Vector3(Object::objectList[i]->hitbox.position.x + (Object::objectList[i]->hitbox.sizeX / 2 + 0.5f), 0.6f, Object::objectList[i]->hitbox.position.z + (Object::objectList[i]->hitbox.sizeZ / 2 + 0.5f)));
			forWaypoint2.SetPosition(Vector3(Object::objectList[i]->hitbox.position.x + (Object::objectList[i]->hitbox.sizeX / 2 + 0.5f), 0.6f, Object::objectList[i]->hitbox.position.z - (Object::objectList[i]->hitbox.sizeZ / 2 + 0.5f)));
			forWaypoint3.SetPosition(Vector3(Object::objectList[i]->hitbox.position.x - (Object::objectList[i]->hitbox.sizeX / 2 + 0.5f), 0.6f, Object::objectList[i]->hitbox.position.z + (Object::objectList[i]->hitbox.sizeZ / 2 + 0.5f)));
			forWaypoint4.SetPosition(Vector3(Object::objectList[i]->hitbox.position.x - (Object::objectList[i]->hitbox.sizeX / 2 + 0.5f), 0.6f, Object::objectList[i]->hitbox.position.z - (Object::objectList[i]->hitbox.sizeZ / 2 + 0.5f)));

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
void Waypoint::LinkWaypoints()
{
	Hitbox collisionChecker;
	collisionChecker.SetSize(Waypoint::sizeH, Waypoint::sizeV, Waypoint::sizeH);

	for (int j = 0; j < Waypoint::waypointList.size(); ++j){// Check waypoints one by one with gotten waypoint
		if (this != Waypoint::waypointList[j]){//Check if its comparing with itself
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

				collided = Hitbox::CheckHitBox(collisionChecker);
			}
			if (!collided){
				this->reachableWaypoints.insert(std::pair<float, Waypoint*>(distance, Waypoint::waypointList[j]));
			}
		}

	}
}
void GenerateWaypoints(int mapSizeX, int mapSizeZ, float waypointSizeH, float waypointSizeV)
{
	StoreWaypoints(mapSizeX, mapSizeZ, waypointSizeH, waypointSizeV);

	//iterates through each waypoint and create a link to all reachable waypoints from curr waypoint
	for (vector<Waypoint*>::iterator it = Waypoint::waypointList.begin(); it != Waypoint::waypointList.end(); ++it){
		(*it)->LinkWaypoints();
	}


}

void ResetWaypoints()
{
	for (vector<Waypoint*>::iterator it = Waypoint::waypointList.begin(); it != Waypoint::waypointList.end(); ++it){
		(*it)->Reset();
	}
}