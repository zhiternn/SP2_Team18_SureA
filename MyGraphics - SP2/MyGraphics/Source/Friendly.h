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
	Friendly(Vector3 pos = Vector3(0, 0, 0), float speed = 1.f);
	virtual  ~Friendly();

	virtual void Update(double dt);

private:
	string dialogue;
};

#endif

/*
roams
if enemy near, increase speed and panic

*/