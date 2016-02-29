#include "NPC.h"

NPC::NPC(Vector3 pos, Vector3 dir, float speed) :
defaultDirection(dir)
{
	position = pos;
	checkPoint = path.rend();
	checkPointDir.SetZero();

	this->speed = speed;
	facingYaw = 0.f;
}

NPC::~NPC()
{
}

void CalculateMovementCost(Waypoint* node, Waypoint* prevNode)
{
	for (vector<Waypoint*>::iterator it = (node->reachableWaypoints).begin(); it != (node->reachableWaypoints).end(); ++it){
		float totalCost = node->movementCost + ((*it)->position - node->position).Length(); // gets the total cost to get from starting waypoint to curr waypoint
		if (totalCost < (*it)->movementCost){
			(*it)->movementCost = totalCost;// first is distance between curr node
			(*it)->next = prevNode;
		}
	}
	if (node->target != nullptr){
		float totalCost = node->movementCost + ((node->target)->position - node->position).Length();
		if (totalCost < (node->target)->movementCost){
			(node->target)->movementCost = totalCost;
			(node->target)->next = prevNode;
		}
	}
}

Waypoint* GetLowestInList(vector<Waypoint*> vec)
{
	float currentLowestMovementCost = 999.f;
	Waypoint* belongingWaypoint = nullptr;

	for (vector<Waypoint*>::iterator it = vec.begin(); it != vec.end(); ++it){
		if ((*it)->movementCost <= currentLowestMovementCost){
			currentLowestMovementCost = (*it)->movementCost;
			belongingWaypoint = *it;
		}
	}

	return belongingWaypoint;
}

list<Waypoint*> Dijkstra(Waypoint* start, Waypoint* end)
{
	Waypoint* parentWaypoint = nullptr;
	Waypoint* currWaypoint = start;

	vector<Waypoint*> openList;

	//Store all waypoints into openList
	for (vector<Waypoint*>::iterator it = Waypoint::waypointList.begin(); it != Waypoint::waypointList.end(); ++it){
		openList.push_back(*it);
	}
	currWaypoint->movementCost = 0.f;
	openList.push_back(currWaypoint);
	openList.push_back(end);

	while (currWaypoint != end){
		//find lowest movementCost
		currWaypoint = GetLowestInList(openList);

		//if == end, break
		if (currWaypoint == end){
			break;
		}

		//else calculate neighbours
		parentWaypoint = currWaypoint;
		CalculateMovementCost(currWaypoint, parentWaypoint);

		//pop lowest movementCost
		for (vector<Waypoint*>::iterator it = openList.begin(); it != openList.end();){
			if ((*it) == currWaypoint){
				it = openList.erase(it);
			}
			else{
				++it;
			}
		}
	}

	list<Waypoint*> result; // closed list

	while (currWaypoint != nullptr){
		result.push_back(currWaypoint);
		currWaypoint = currWaypoint->next;
	}

	ResetWaypoints(); // resets movementCosts

	return result;
}

void NPC::GoTo(Vector3 destination)
{
	path.clear();

	Waypoint* currLocation = new Waypoint(position, Waypoint::sizeH, Waypoint::sizeV);
	Waypoint* targetLocation = new Waypoint(destination, Waypoint::sizeH, Waypoint::sizeV);

	currLocation->position.y = Waypoint::sizeV / 2;
	targetLocation->position.y = Waypoint::sizeV / 2;

	if (currLocation->CheckLink(*targetLocation)){//if there is a clear path between location and destination
		path.push_back(targetLocation);
	}
	else{ //else follow Dijkstra

		currLocation->LinkWaypoints();
		targetLocation->LinkWaypoints();

		for (vector<Waypoint*>::iterator it = (targetLocation->reachableWaypoints).begin(); it != (targetLocation->reachableWaypoints).end(); ++it){
			(*it)->target = targetLocation;
		}

		path = Dijkstra(currLocation, targetLocation);

		if (path.size() > 0){
			path.pop_back(); // removes the last waypoint - it represents current position
		}
	}

	checkPoint = path.rbegin();
}