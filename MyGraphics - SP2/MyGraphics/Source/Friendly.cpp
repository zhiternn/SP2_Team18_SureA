#include "Friendly.h"

vector<Friendly*> Friendly::friendlyList;

Friendly::Friendly(Vector3 pos, Vector3 dir, float speed) :
NPC(pos, dir, speed)
{
	state = IDLE;
}

Friendly::~Friendly()
{
}

void Friendly::Update(double dt)
{
	static int IDLE_TIME = 10; // average idle time
	switch (state)
	{
	case IDLE:
		// 60 represents FPS
		if (rand() % (IDLE_TIME * 60)){ // continues idling
		}
		else{ // stop idling
			GoTo(Vector3(rand() % 97 - 48, 0, rand() % 97 - 48));//rand() % 97 - 48 gives a random value between -48 to 48
			state = ROAM;
		}
		break;
	case ROAM:
		if (checkPoint != path.rend()){
			//MOVE TO
			checkPointDir = ((*checkPoint)->position - position).Normalized();
			facingYaw = (defaultDirection.Cross(checkPointDir)).Dot(Vector3(0, 1, 0) * Math::RadianToDegree(acos(defaultDirection.Dot(checkPointDir))));
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
		//static float panic_speed = speed * 2;
		//speed = panic_speed;
		break;
	case CHAT:
		break;
	case EVACUATE:
		break;
	default:
		break;
	}
}