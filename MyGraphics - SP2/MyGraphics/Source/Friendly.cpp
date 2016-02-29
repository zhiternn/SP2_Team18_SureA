#include "Friendly.h"

vector<Friendly*> Friendly::friendlyList;

Friendly::Friendly(Vector3 pos, Vector3 dir, float speed) :
NPC(pos, dir, speed)
{
	state = IDLE;
	dialogue.clear();
	reachedDestination = false;

	Friendly::friendlyList.push_back(this);
}

Friendly::~Friendly()
{
}

void Friendly::Update(double dt)
{
	static int IDLE_TIME = 10; // average idle time in seconds
	switch (state)
	{
	case IDLE:
		// 60 represents FPS
		if (rand() % (IDLE_TIME * 60)){ // continues idling
		}
		else{ // stop idling
			//rand() % 97 - 48 gives a random value between -48 to 48
			GoTo(Vector3(rand() % 97 - 48, 0, rand() % 97 - 48));
			state = ROAM;
		}
		break;

	case ROAM:
		if (checkPoint != path.rend()){
			//MOVE TO
			checkPointDir = ((*checkPoint)->position - position).Normalized();
			facingYaw = (((defaultDirection.Cross(checkPointDir)).y / abs((defaultDirection.Cross(checkPointDir)).y)) * Math::RadianToDegree(acos(defaultDirection.Dot(checkPointDir))));
			position += checkPointDir * speed * dt;

			if ((position - (*checkPoint)->position).Length() <= Waypoint::sizeH / 2){
				checkPoint++;
			}
		}
		else{
			state = IDLE;
		}
		break;

	case PANIC:
		break;

	case CHAT:

		break;

	case EVACUATE:
		if (checkPoint != path.rend()){
			//MOVE TO
			checkPointDir = ((*checkPoint)->position - position).Normalized();
			facingYaw = (((defaultDirection.Cross(checkPointDir)).y / abs((defaultDirection.Cross(checkPointDir)).y)) * Math::RadianToDegree(acos(defaultDirection.Dot(checkPointDir))));
			position += checkPointDir * speed * dt;

			if ((position - (*checkPoint)->position).Length() <= Waypoint::sizeH / 2){
				checkPoint++;
			}
		}
		else{
			reachedDestination = true;;
		}
		break;

	default:
		break;
	}
}

void Friendly::StoreDialogue(vector<string> svec)
{
	dialogue = svec;
}

string Friendly::GetDialogue()
{
	return dialogue[rand()%dialogue.size()];
}