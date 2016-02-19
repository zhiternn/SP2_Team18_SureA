#ifndef CAMERA_LOCKPOSITION_H
#define CAMERA_LOCKPOSITION_H

#include "Vector3.h"

class Camera_LockPosition
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;
	Vector3 view;
	Vector3 right;

	Camera_LockPosition();
	~Camera_LockPosition();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	void Update(double dt);
	virtual void Reset();
};

#endif