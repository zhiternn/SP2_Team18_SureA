#include "Camera_LockTarget.h"
#include "Application.h"
#include "Mtx44.h"

Camera_LockTarget::Camera_LockTarget()
{
}

Camera_LockTarget::~Camera_LockTarget()
{
}

void Camera_LockTarget::Init(const Vector3& pos, const Vector3& target, const Vector3& up, float zoom)
{
	this->target = target;
	this->position = pos;
	view = (pos - target).Normalized();
	this->right = view.Cross(up);
	this->right.Normalize();
	this->up = up;
	this->up.Normalize();

	this->zoom = zoom;

}

void Camera_LockTarget::Update(double dt)
{
	static const float CAMERA_SPEED = 6.f;
	static float ZOOM_SPEED = 30.f;

	if (Application::mouseWheelY > 0){
		zoom -= ZOOM_SPEED * dt;
		Application::mouseWheelY = 0;
	}
	else if (Application::mouseWheelY < 0){
		zoom += ZOOM_SPEED * dt;
		Application::mouseWheelY = 0;
	}

	double mouseY, mouseX;

	Application::GetMouseMovement(mouseX, mouseY);
	float yaw = -(float)(mouseX * CAMERA_SPEED * dt);
	Mtx44 rotate;
	rotate.SetToRotation(yaw, 0, 1, 0);
	view = rotate * view;
	right = rotate * right;
	up = rotate * up;
	position = target - view * zoom;

	if (view.y < 0.7 && mouseY < 0 || view.y > -0.7 && mouseY > 0){
		float pitch = -(float)(mouseY * CAMERA_SPEED * dt);
		rotate.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotate * view;
		right = rotate * right;
		up = rotate * up;
		position = target - view * zoom;
	}

	view.Normalize();
	right.Normalize();
	up.Normalize();

	Application::SetMousePosition();
}

void Camera_LockTarget::Reset()
{
}