#include "Camera_LockPosition.h"
#include "Application.h"
#include "Mtx44.h"

Camera_LockPosition::Camera_LockPosition()
{
}

Camera_LockPosition::~Camera_LockPosition()
{
}

void Camera_LockPosition::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->target = target;
	this->position = pos;
	view = (target - pos).Normalized();
	this->right = view.Cross(up);
	this->right.Normalize();
	this->up = up;
	this->up.Normalize();

}

void Camera_LockPosition::Update(double dt)
{
	static const float CAMERA_SPEED = 10.f;
	static float ZOOM = 5.f;

	double mouseX, mouseY;

	Application::GetMouseMovement(mouseX, mouseY);
	float yaw = (float)(mouseX * CAMERA_SPEED * dt);
	Mtx44 rotate;
	rotate.SetToRotation(yaw, 0, 1, 0);
	view = rotate * view;
	right = rotate * right;
	up = rotate * up;
	target = position + view * ZOOM;

	if (view.y < 0.95 && mouseY > 0 || view.y > -0.95 && mouseY < 0){
		float pitch = (float)(mouseY * CAMERA_SPEED * dt);
		rotate.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotate * view;
		right = rotate * right;
		up = rotate * up;
		target = position + view * ZOOM;
	}

	view.Normalize();
	right.Normalize();
	up.Normalize();
}

void Camera_LockPosition::Reset()
{
}