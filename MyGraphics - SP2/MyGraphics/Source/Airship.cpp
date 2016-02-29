#include "Airship.h"
#include "Application.h"
#include "Mtx44.h"
#include "WorldValues.h"

Airship::Airship(Vector3 pos, Vector3 dir)
{
}

Airship::~Airship()
{
}

void Airship::Init(const Vector3& pos, const Vector3& frontDir)
{
	this->position = pos;
	this->frontDir = defaultFront = frontDir.Normalized();
	this->thrustDir = Vector3(0, 1, 0);
	this->right = this->defaultRight = (this->frontDir.Cross(Vector3(0, 1, 0))).Normalized();

	camera.Init(pos - frontDir*-10.f, pos, Vector3(0, 1, 0));
	ySpeed = xSpeed = zSpeed = 0.f;

	hitbox.SetSize(1.8f, 1.5f, 1.8f);
	hitbox.SetPosition(position);
}

void Airship::Update(double dt, bool controlling)
{
	static const float THRUST_SPEED = 10.f;
	static const float THRUST_LIMIT = 5.f;
	static const float TURN_SPEED = 100.f;

	bool piloting = false;

	if (controlling){
		if (Application::IsKeyPressed('R'))
		{
			if (thrustSpeed < THRUST_LIMIT)
				thrustSpeed += (float)(THRUST_SPEED * dt);
		}
		if (Application::IsKeyPressed('F'))
		{
			if (thrustSpeed > -THRUST_LIMIT)
				thrustSpeed -= (float)(THRUST_SPEED * dt);
		}
		if (Application::IsKeyPressed('A'))
		{
			float yaw = (float)(TURN_SPEED * dt);

			Mtx44 rotate;
			rotate.SetToRotation(yaw, 0, 1, 0);
			thrustDir = rotate * thrustDir;
			frontDir = rotate * frontDir;
			right = rotate * right;
		}
		if (Application::IsKeyPressed('D'))
		{
			float yaw = (float)(-TURN_SPEED * dt);

			Mtx44 rotate;
			rotate.SetToRotation(yaw, 0, 1, 0);
			thrustDir = rotate * thrustDir;
			frontDir = rotate * frontDir;
			right = rotate * right;
		}
		if (Application::IsKeyPressed('W'))
		{
			ySpeed += (THRUST_LIMIT/2) * dt;
		}
		if (Application::IsKeyPressed('S'))
		{
			ySpeed -= (THRUST_LIMIT/2) * dt;
		}
	}
	if (thrustSpeed > 0.f){
		thrustSpeed -= (float)(THRUST_SPEED * dt);
	}
	else if (thrustSpeed < 0.f){
		thrustSpeed += (float)(THRUST_SPEED * dt);
	}

	frontDir.Normalize();
	right.Normalize();
	thrustDir.Normalize();

	Vector3 oldPos = position;

	ySpeed += ((thrustDir.y * thrustSpeed) - WV_GRAVITY) * dt;
	xSpeed += ((thrustDir.x * thrustSpeed)) * dt;
	zSpeed += ((thrustDir.z * thrustSpeed)) * dt;
	position.x += xSpeed * dt;
	position.z += zSpeed * dt;
	position.y += ySpeed * dt;
	hitbox.SetPosition(position);

	camera.target = position;
	camera.Update(dt);
}