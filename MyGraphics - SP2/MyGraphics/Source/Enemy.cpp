#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Init(Vector3 pos, float speed)
{
	position = pos;
	this->speed = speed;
	checkPoint = path.rend();
	checkPointDir.SetZero();
}

void Enemy::Update(double dt)
{
	if (checkPoint != path.rend()){
		//MOVE TO
		position += checkPointDir * speed * dt;
		checkPointDir = ((*checkPoint)->position - position).Normalized();
		checkPointDir.y = 0;

		if ((position - (*checkPoint)->position).Length() <= Waypoint::sizeH / 2){
			checkPoint++;
		}
	}
}

//also assigns parent Node
void CalculateMovementCost(Waypoint* node, Waypoint* prevNode)
{
	for (map<float, Waypoint*>::iterator it = (node->reachableWaypoints).begin(); it != (node->reachableWaypoints).end(); ++it){
		if (node->movementCost + it->first < (it->second)->movementCost){
			(it->second)->movementCost = node->movementCost + it->first;// first is distance between curr node
			(it->second)->next = prevNode;
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

	list<Waypoint*> result; // closed list
	vector<Waypoint*> openList;
	openList.clear();

	currWaypoint->movementCost = 0.f;

	//Store all waypoints into openList
	for (vector<Waypoint*>::iterator it = Waypoint::waypointList.begin(); it != Waypoint::waypointList.end(); ++it){
		openList.push_back(*it);
	}
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

	while (currWaypoint != nullptr){
		result.push_back(currWaypoint);
		currWaypoint = currWaypoint->next;
	}

	ResetWaypoints(); // resets movementCosts

	return result;
}
void Enemy::GoTo(Vector3 destination)
{
	path.clear();

	Waypoint *currLocation = new Waypoint(position, Waypoint::sizeH, Waypoint::sizeV);
	Waypoint *targetLocation = new Waypoint(destination, Waypoint::sizeH, Waypoint::sizeV);

	currLocation->position.y = Waypoint::sizeV / 2;
	targetLocation->position.y = Waypoint::sizeV / 2;

	currLocation->LinkWaypoints();
	targetLocation->LinkWaypoints();

	if (currLocation->CheckLink(*targetLocation)){//if there is a clear path between location and destination
		path.push_back(targetLocation);
		checkPoint = path.rbegin();
	}
	else{ //else follow Dijkstra
		//get waypoint nearest to Target
		float lowestDistance = 999.f; // supposedly infinity
		Waypoint* nearestToTarget = nullptr;

		for (map<float, Waypoint*>::iterator it = (targetLocation->reachableWaypoints).begin(); it != (targetLocation->reachableWaypoints).end(); ++it){
			if (it->first < lowestDistance){
				lowestDistance = it->first;
				nearestToTarget = it->second;
			}
		}
		path = Dijkstra(currLocation, nearestToTarget);
		path.pop_back(); // removes the last waypoint - it represents current position

		checkPoint = path.rbegin();
	}
}