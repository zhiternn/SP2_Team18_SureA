#ifndef OBJECT_H
#define OBJECT_H

#include "Vector3.h"
#include "Hitbox.h"

class Object
{
public:
	Object();
	~Object();

	Vector3 position;
	Hitbox hitbox;

	static std::vector<Object*> objectList;

	void SetHealth(int amount);
	void SetPosition(float x, float y, float z);
	void ReceiveDamage(int amount);
private:
	int HP;
	bool isInvulnerable;
};

#endif