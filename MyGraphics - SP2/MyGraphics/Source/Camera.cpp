#include "Camera.h"
#include "Application.h"
#include "Mtx44.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	this->up = up;
}

void Camera::Update(Vector3 playerPos, Vector3 playerDir)
{
	position = playerPos;
	target = playerPos + playerDir;
}

void Camera::Reset()
{
}