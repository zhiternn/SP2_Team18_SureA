#ifndef CAMERA_FPS_H
#define CAMERA_FPS_H

#include "Hitbox.h"
#include "Camera.h"

class Camera_FPS : public Camera
{
public:

	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;

	Vector3 view;
	Vector3 right;

	double yaw, pitch;

	Camera_FPS();
	~Camera_FPS();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	void Update(double dt);
	virtual void Reset();

private:
	bool readyToJump;
	float vSpeed;
};

#endif