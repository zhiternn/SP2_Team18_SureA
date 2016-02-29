#ifndef AIRSHIP_H
#define AIRSHIP_H

#include "Hitbox.h"
#include "Camera_LockTarget.h"

class Airship
{
public:
	Airship(Vector3 pos = Vector3(0, 0, 0), Vector3 dir = Vector3(0, 0, 1));
	~Airship();

	Vector3 defaultFront;
	Vector3 defaultRight;

	Vector3 position;
	Vector3 frontDir;
	Vector3 right;

	Camera_LockTarget camera;

	Hitbox hitbox;

	float thrustSpeed;
	float ySpeed;
	float xSpeed;
	float zSpeed;

	float facingYaw;

	void Init(const Vector3& pos, const Vector3& frontDir);
	void Update(double dt, bool controlling);
private:

};

#endif