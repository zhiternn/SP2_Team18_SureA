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
	checkPoint = path.begin();
}

void Enemy::Update(double dt)
{
	if (checkPoint != path.end()){
		//MOVE TO
		if (position.x > (*checkPoint)->position.x)
			position.x -= speed * dt;
		else if (position.x < (*checkPoint)->position.x)
			position.x += speed * dt;

		if (position.z > (*checkPoint)->position.z)
			position.z -= speed * dt;
		else if (position.z < (*checkPoint)->position.z)\
			position.z += speed * dt;

		if ((position - (*checkPoint)->position).Length() <= 1.f){
			checkPoint++;
		}
	}
}

void CalculateMovementCost(Waypoint* node)
{
	for (map<float, Waypoint*>::iterator it = (node->reachableWaypoints).begin(); it != (node->reachableWaypoints).end(); ++it){
		if (node->movementCost + it->first < (it->second)->movementCost){
			(it->second)->movementCost = node->movementCost + it->first;// first is distance between curr node
		}
	}
}
Waypoint* GetLowestInList(vector<Waypoint*> vec)
{
	float currentLowestMovementCost = 999;
	Waypoint* belongingWaypoint = nullptr;

	for (vector<Waypoint*>::iterator it = vec.begin(); it != vec.end(); ++it){
		if ((*it)->movementCost <= currentLowestMovementCost){
			currentLowestMovementCost = (*it)->movementCost;
			belongingWaypoint = *it;
		}
	}

	return belongingWaypoint;
}

list<Waypoint*> Enemy::Dijkstra(Waypoint* start, Waypoint* end)
{
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
		Waypoint* lowestMovementCost = GetLowestInList(openList);

		//store in result and assign to curr
		result.push_back(lowestMovementCost);
		currWaypoint = lowestMovementCost;

		//if == end, return
		if (currWaypoint == end){	
			break;
		}

		//else calculate neighbours
		CalculateMovementCost(currWaypoint);

		//pop lowest movementCost
		for (vector<Waypoint*>::iterator it = openList.begin(); it != openList.end();){
			if ((*it)->movementCost == currWaypoint->movementCost){
				it = openList.erase(it);
			}
			else{
				++it;
			}
		}
	}

	return result;
}
void Enemy::FindPath(Vector3 destination)
{
	Waypoint* currLocation = new Waypoint(position, Waypoint::sizeH, Waypoint::sizeV);
	Waypoint* targetLocation = new Waypoint(destination, Waypoint::sizeH, Waypoint::sizeV);
	
	currLocation->position.y = 0;
	targetLocation->position.y = 0;

	currLocation->LinkWaypoints();
	targetLocation->LinkWaypoints();

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

	checkPoint = path.begin();
	std::cout << path.size() << std::endl;

	ResetWaypoints(); // resets movementCosts
}