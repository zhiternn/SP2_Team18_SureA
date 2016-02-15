#ifndef CAMERA_LOCKTARGET_H
#define CAMERA_LOCKTARGET_H

#include "Vector3.h"

class Camera_LockTarget
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;
	Vector3 view;
	Vector3 right;

	Camera_LockTarget();
	~Camera_LockTarget();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	void Update(double dt);
	virtual void Reset();

	void Rotate(float angle, float axisX, float axisY, float axisZ);
};

#endif