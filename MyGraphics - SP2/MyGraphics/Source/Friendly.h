#ifndef FRIENDLY_H
#define FRIENDLY_H

#include "NPC.h"

#include <vector>
#include <list>
#include <string>

using std::string;
using std::vector;
using std::list;

class Friendly : public NPC
{
public:
	Friendly(Vector3 pos = Vector3(0, 0, 0), Vector3 dir = Vector3(0, 0, 1), float speed = 1.f);
	virtual  ~Friendly();

	static vector<Friendly*> friendlyList;

	virtual void Update(double dt);

	short state;
private:
	enum STATE
	{
		IDLE,
		ROAM,
		PANIC,
		CHAT,
		EVACUATE
	};

	string dialogue;
};

#endif