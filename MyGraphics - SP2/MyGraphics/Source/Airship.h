#ifndef AIRSHIP_H
#define AIRSHIP_H

#include "Vehicle.h"
#include "Camera_LockTarget.h"

class Airship : public Vehicle
{
public:
	Airship(Vector3 pos = Vector3(0, 0, 0), Vector3 dir = Vector3(0, 0, 1));
	~Airship();

	Vector3 defaultFront;
	Vector3 defaultRight;

	Camera_LockTarget camera;

	float thrustSpeed;
	float ySpeed;
	float hSpeed;

	float facingYaw;

	void Init(const Vector3& pos, const Vector3& frontDir);
	void Update(double dt, bool controlling);
private:

};

#endif