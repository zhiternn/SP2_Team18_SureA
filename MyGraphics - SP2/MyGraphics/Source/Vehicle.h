#ifndef VEHICLE_H
#define VEHICLE_H

#include "Vector3.h"
#include "Hitbox.h"
#include "Camera.h"
#include "Object.h"

class Vehicle : public Object
{
protected:
	Vehicle(Vector3 pos = Vector3(0, 0, 0), Vector3 dir = Vector3(0, 0, 1))
	{
		position = pos;
		frontDir = dir.Normalized();
		normalDir = Vector3(0, 1, 0);
		right = frontDir.Cross(normalDir);
	}
public:
	virtual ~Vehicle(){}

	virtual void Update(double dt, bool controlling) = 0;

	Vector3 frontDir;
	Vector3 normalDir;
	Vector3 right;
};

#endif