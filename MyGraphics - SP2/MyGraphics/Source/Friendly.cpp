#include "Friendly.h"

vector<Friendly*> Friendly::friendlyList;

Friendly::Friendly(Vector3 pos, Vector3 dir, float speed) :
NPC(pos, dir, speed)
{
}

Friendly::~Friendly()
{
}

void Friendly::Update(double dt)
{
	switch (state)
	{
	case IDLE:
		break;
	case ROAM:
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