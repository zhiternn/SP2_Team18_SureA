#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"

Camera3::Camera3()
{
}

Camera3::~Camera3()
{
}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();

	yaw = 0.f;
}

void Camera3::Update(double dt)
{
	static const float CAMERA_SPEED = 80.f;
	static const float MOVEMENT_SPEED = 30.f;
	if (Application::IsKeyPressed('W'))
	{
		Vector3 camDir = (target - position).Normalized();
		position += (camDir * MOVEMENT_SPEED * dt);
		target += (camDir * MOVEMENT_SPEED * dt);
	}
	if (Application::IsKeyPressed('S'))
	{
		Vector3 camDir = (target - position).Normalized();
		position -= (camDir * MOVEMENT_SPEED * dt);
		target -= (camDir * MOVEMENT_SPEED * dt);
	}
	if (Application::IsKeyPressed('A'))
	{
		Vector3 camDir = (target - position).Normalized();
		Vector3 leftDir = (up.Cross(camDir)).Normalized();

		position += (leftDir * MOVEMENT_SPEED * dt);
		target += (leftDir * MOVEMENT_SPEED * dt);
	}
	if (Application::IsKeyPressed('D'))
	{
		Vector3 camDir = (target - position).Normalized();
		Vector3 rightDir = (camDir.Cross(up)).Normalized();

		position += (rightDir * MOVEMENT_SPEED * dt);
		target += (rightDir * MOVEMENT_SPEED * dt);
	}
	if (Application::IsKeyPressed(VK_LEFT))
	{
		float yaw = (float)(CAMERA_SPEED * dt);
		Mtx44 rotate;
		rotate.SetToRotation(yaw, 0, 1, 0);
		target.x -= position.x;
		target.y -= position.y;
		target.z -= position.z;
		target = rotate * target;
		target.x += position.x;
		target.y += position.y;
		target.z += position.z;
		up = rotate * up;
	}
	if (Application::IsKeyPressed(VK_RIGHT))
	{
		float yaw = (float)(-CAMERA_SPEED * dt);
		Mtx44 rotate;
		rotate.SetToRotation(yaw, 0, 1, 0);
		target.x -= position.x;
		target.y -= position.y;
		target.z -= position.z;
		target = rotate * target;
		target.x += position.x;
		target.y += position.y;
		target.z += position.z;
		up = rotate * up;
	}
	if (Application::IsKeyPressed(VK_UP))
	{
		float pitch = (float)(CAMERA_SPEED * dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotate;
		rotate.SetToRotation(pitch, right.x, right.y, right.z);
		target.x -= position.x;
		target.y -= position.y;
		target.z -= position.z;
		target = rotate * target;
		target.x += position.x;
		target.y += position.y;
		target.z += position.z;
	}
	if (Application::IsKeyPressed(VK_DOWN))
	{
		float pitch = (float)(-CAMERA_SPEED * dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotate;
		rotate.SetToRotation(pitch, right.x, right.y, right.z);
		target.x -= position.x;
		target.y -= position.y;
		target.z -= position.z;
		target = rotate * target;
		target.x += position.x;
		target.y += position.y;
		target.z += position.z;
	}
	if (Application::IsKeyPressed('R'))
	{
		Reset();
	}
}

void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
	yaw = 0.f;
}