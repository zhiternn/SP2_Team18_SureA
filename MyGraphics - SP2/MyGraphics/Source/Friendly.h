#ifndef FRIENDLY_H
#define FRIENDLY_H

#include "NPC.h"

#include <vector>
#include <list>
#include <string>

#include "Countdown.h"

using std::string;
using std::vector;
using std::list;

class Friendly : public NPC
{
public:
	enum FRIENDLY_STATE
	{
		IDLE,
		ROAM,
		PANIC,
		CHAT,
		EVACUATE
	};
	enum STATUS
	{
		STATUS_CIVILIAN,
		STATUS_GENERAL1,
		STATUS_GENERAL2,
		STATUS_GENERAL3
	};

	Friendly(Vector3 pos = Vector3(0, 0, 0), Vector3 dir = Vector3(0, 0, 1), float speed = 1.f);
	virtual  ~Friendly();

	static vector<Friendly*> friendlyList;

	virtual void Update(double dt);
	void TalkTo(Vector3 pos);

	void StoreDialogue(vector<string> svec);
	string GetDialogue();

	bool reachedDestination;
	FRIENDLY_STATE state;
	STATUS status;
private:
	void StateChart_Civilian(double dt);
	void StateChart_General(double dt);
	vector<string> dialogue;
	Countdown timer;
};

#endif