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

<<<<<<< 029b1855139d72acdcca5d0d021453c2caa07c8c
	enum FRIENDLY_STATE
	{
		IDLE,
		ROAM,
		PANIC,
		CHAT,
		EVACUATE
=======
	enum STATUS
	{
		STATUS_CIVILIAN,
		STATUS_GENERAL
>>>>>>> bc47c15713c5bb9e307b6723d388a25c3dedb179
	};

	Friendly(Vector3 pos = Vector3(0, 0, 0), Vector3 dir = Vector3(0, 0, 1), float speed = 1.f);
	virtual  ~Friendly();

	static vector<Friendly*> friendlyList;

	virtual void Update(double dt);
	void StoreDialogue(vector<string> svec);
	string GetDialogue();

<<<<<<< 029b1855139d72acdcca5d0d021453c2caa07c8c
	bool reachedDestination;
	FRIENDLY_STATE state;
=======
	short state;
	STATUS status;
>>>>>>> bc47c15713c5bb9e307b6723d388a25c3dedb179
private:
	vector<string> dialogue;
};

#endif