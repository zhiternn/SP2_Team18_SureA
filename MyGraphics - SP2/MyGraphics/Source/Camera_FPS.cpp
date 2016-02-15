#include "Camera_FPS.h"
#include "Application.h"
#include "Mtx44.h"
#include "WorldValues.h"

extern std::vector<Hitbox> hitBoxList;

Camera_FPS::Camera_FPS()
{
}

Camera_FPS::~Camera_FPS()
{
}

void Camera_FPS::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	this->view = view;
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->right = right;
	this->up = defaultUp = right.Cross(view).Normalized();

	yaw = pitch = 0;
	readyToJump = true;
	vSpeed = 0.f;
}
static const float CAMERA_SPEED = 10.f;
static const float MOVEMENT_SPEED = 5.f;

void Camera_FPS::Update(double dt)
{
	if (Application::IsKeyPressed('W'))
	{
		Vector3 view_FPS = view;
		view_FPS.y = 0;
		position += (view_FPS * MOVEMENT_SPEED * dt);
		target += (view_FPS * MOVEMENT_SPEED * dt);
	}
	if (Application::IsKeyPressed('S'))
	{
		Vector3 view_FPS = view;
		view_FPS.y = 0;
		position -= (view_FPS * MOVEMENT_SPEED * dt);
		target -= (view_FPS * MOVEMENT_SPEED * dt);
	}
	if (Application::IsKeyPressed('A'))
	{
		Vector3 right_FPS = right;
		right_FPS.y = 0;
		position -= (right_FPS * MOVEMENT_SPEED * dt);
		target -= (right_FPS * MOVEMENT_SPEED * dt);
	}
	if (Application::IsKeyPressed('D'))
	{
		Vector3 right_FPS = right;
		right_FPS.y = 0;
		position += (right_FPS * MOVEMENT_SPEED * dt);
		target += (right_FPS * MOVEMENT_SPEED * dt);
	}

	Application::GetMouseMovement(yaw, pitch);
	float yaw = (float)(this->yaw * CAMERA_SPEED * dt);
	Mtx44 rotate;
	rotate.SetToRotation(yaw, 0, 1, 0);
	view = rotate * view;
	right = rotate * right;
	up = rotate * up;
	target = position + view;

	if (view.y < 0.9396 && pitch > 0 || view.y > -0.9396 && pitch < 0){
		float pitch = (float)(this->pitch * CAMERA_SPEED * dt);
		rotate.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotate * view;
		right = rotate * right;
		up = rotate * up;
		target = position + view;
	}

	view.Normalize();
	right.Normalized();
	up.Normalize();
	
	if (Application::IsKeyPressed('R'))
	{
		Reset();
	}
}

void Camera_FPS::Reset()
{
	Init(defaultPosition, defaultTarget, defaultUp);
}