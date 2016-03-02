#include "Friendly.h"

vector<Friendly*> Friendly::friendlyList;

Friendly::Friendly(Vector3 pos, Vector3 dir, float speed) :
NPC(pos, dir, speed)
{
	this->status = status;

	state = IDLE;
	dialogue.clear();
	reachedDestination = false;
	chatLineCounter = 0;
	finishedTalking = false;

	Friendly::friendlyList.push_back(this);
}

Friendly::~Friendly()
{
}

void Friendly::Update(double dt)
{
	if (status == STATUS_CIVILIAN){
		StateChart_Civilian(dt);
	}
	else{
		StateChart_General(dt);
	}
}

void Friendly::StoreDialogue(vector<string> svec)
{
	dialogue.clear();
	dialogue = svec;
}

string Friendly::GetDialogue()
{
	if (status == STATUS_CIVILIAN){
		return dialogue[rand() % dialogue.size()];
	}
	else{
		return dialogue[chatLineCounter];
	}
}

void Friendly::TalkTo(Vector3 pos)
{
	if(status == STATUS_CIVILIAN){
		timer.StartCountdown(2);//stays for 2 seconds
		if (position != pos){
			Vector3 view = (pos - position).Normalized();
			facingYaw = (((defaultDirection.Cross(view)).y / abs((defaultDirection.Cross(view)).y)) * Math::RadianToDegree(acos(defaultDirection.Dot(view))));
			state = CHAT;
		}
	}
	else{
		chatLineCounter++;

		if (chatLineCounter >= dialogue.size()){
			finishedTalking = true;
			chatLineCounter = 0;
		}
	}
}

void Friendly::StateChart_Civilian(double dt)
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
			if (position != (*checkPoint)->position){
				checkPointDir = ((*checkPoint)->position - position).Normalized();
			}
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
		if (timer.GetTimeLeft() <= 0){
			state = ROAM;
		}
		break;

	case EVACUATE:
		if (checkPoint != path.rend()){
			//MOVE TO
			if (position != (*checkPoint)->position){
				checkPointDir = ((*checkPoint)->position - position).Normalized();
			}
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

void Friendly::StateChart_General(double dt)
{
	switch (state)
	{
	case IDLE:
		facingYaw = (((Vector3(0, 0, 1).Cross(defaultDirection)).y / abs((Vector3(0, 0, 1).Cross(defaultDirection)).y)) * Math::RadianToDegree(acos(Vector3(0, 0, 1).Dot(defaultDirection))));
		break;

	case ROAM:
		break;

	case PANIC:
		break;

	case CHAT:
		break;

	case EVACUATE:
		break;

	default:
		break;
	}
}