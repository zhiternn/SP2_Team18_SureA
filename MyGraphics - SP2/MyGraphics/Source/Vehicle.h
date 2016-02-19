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
		view = dir.Normalized();
		up = Vector3(0, 1, 0);
		right = view.Cross(up);
	}
public:
	virtual ~Vehicle(){}

	virtual void Update(double dt) = 0;

	Vector3 view;
	Vector3 up;
	Vector3 right;
};

#endif