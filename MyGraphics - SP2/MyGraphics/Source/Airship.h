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

	float frontThrust;
	float upThrust;
	float hSpeed;
	float vSpeed;

	float facingYaw;

	void Init(const Vector3& pos, const Vector3& frontDir);
	void Update(double dt, bool controlling);
private:

};

#endif