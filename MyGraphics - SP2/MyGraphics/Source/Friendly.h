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
		STATUS_GENERAL
	};

	Friendly(Vector3 pos = Vector3(0, 0, 0), Vector3 dir = Vector3(0, 0, 1), float speed = 1.f);
	virtual  ~Friendly();

	static vector<Friendly*> friendlyList;

	virtual void Update(double dt);
	void StoreDialogue(vector<string> svec);
	string GetDialogue();

	bool reachedDestination;
	FRIENDLY_STATE state;
	STATUS status;
private:
	vector<string> dialogue;
};

#endif