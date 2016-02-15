#ifndef HELICOPTER_H
#define HELICOPTER_H

#include "Hitbox.h"
#include "Camera_LockTarget.h"

class Helicopter
{
public:
	Vector3 defaultFront;
	Vector3 defaultRight;

	Vector3 position;
	Vector3 thrustDir;
	Vector3 frontDir;
	Vector3 right;

	Camera_LockTarget camera;

	Hitbox hitbox;

	float thrustSpeed;
	float vSpeed;
	float xSpeed;
	float zSpeed;

	Helicopter();
	~Helicopter();
	void Init(const Vector3& pos, const Vector3& frontDir);
	void Update(double dt, bool controlling);

	float rotateYaw;
	float rotatePitch;
	float rotateRoll;
private:
	
};

#endif