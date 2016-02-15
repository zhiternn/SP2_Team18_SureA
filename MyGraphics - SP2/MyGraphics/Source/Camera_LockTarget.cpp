#include "Camera_LockTarget.h"
#include "Application.h"
#include "Mtx44.h"

Camera_LockTarget::Camera_LockTarget()
{
}

Camera_LockTarget::~Camera_LockTarget()
{
}

void Camera_LockTarget::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->target = target;
	this->position = pos;
	view = (pos - target).Normalized();
	this->right = view.Cross(up);
	this->right.Normalize();
	this->up = up;
	this->up.Normalize();

}

void Camera_LockTarget::Update(double dt)
{
	static const float CAMERA_SPEED = 10.f;
	static float ZOOM = 5.f;
	
	double mouseY, mouseX;

	Application::GetMouseMovement(mouseX, mouseY);
	float yaw = (float)(-mouseX * CAMERA_SPEED * dt);
	Mtx44 rotate;
	rotate.SetToRotation(yaw, 0, 1, 0);
	view = rotate * view;
	right = rotate * right;
	up = rotate * up;
	position = target - view * ZOOM;

	if (view.y < 0.9396 && mouseY > 0 || view.y > -0.9396 && mouseY < 0){
		float pitch = (float)(mouseY * CAMERA_SPEED * dt);
		rotate.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotate * view;
		right = rotate * right;
		up = rotate * up;
		position = target - view * ZOOM;
	}

	view.Normalize();
	right.Normalized();
	up.Normalize();
}

void Camera_LockTarget::Reset()
{
}

void Camera_LockTarget::Rotate(float angle, float axisX, float axisY, float axisZ)
{
	Mtx44 rotate;
	rotate.SetToRotation(angle, axisX, axisY, axisZ);
	view = rotate * view;
	right = rotate * right;
	up = rotate * up;
}