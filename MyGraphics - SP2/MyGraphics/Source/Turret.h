#ifndef TURRET_H
#define TURRET_H

#include "Vehicle.h"
#include "Camera_LockPosition.h"

#include "Sound.h"

class Turret : public Vehicle
{
public:
	Turret(Vector3 pos = Vector3(0, 0, 0), Vector3 dir = Vector3(0, 0, 1));
	virtual ~Turret();

	Vector3 seatPos;
	Vector3 barrelPos;

	Camera_LockPosition camera;

	float GetPitch();
	float GetYaw();

	void Init(Vector3 pos, Vector3 dir, int atkSpeed = 1);
	virtual void Update(double dt, bool controlling);

	float heatSystem;
private:
	float forRotationYaw, forRotationPitch;
	int roundPerSecond;
	float heatAmount;
	bool isOverHeated;
	
	Sound sound;

};

#endif