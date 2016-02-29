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
	this->right = this->defaultRight = (this->frontDir.Cross(Vector3(0, 1, 0))).Normalized();

	camera.Init(pos - frontDir, pos, Vector3(0, 1, 0));
	ySpeed = xSpeed = zSpeed = 0.f;

	facingYaw = 0.f;

	hitbox.SetSize(1.8f, 1.5f, 1.8f);
	hitbox.SetPosition(position);
}

void Airship::Update(double dt, bool controlling)
{
	static const float THRUST_SPEED = 100.f;
	static const float THRUST_LIMIT = 5.f;
	static const float TURN_SPEED = 100.f;

	Vector3 oldPos = position;

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
			frontDir = rotate * frontDir;
			right = rotate * right;

			camera.right = rotate * camera.right;
			camera.up = rotate * camera.up;
			camera.view = rotate * camera.view;
		}
		if (Application::IsKeyPressed('D'))
		{
			float yaw = (float)(-TURN_SPEED * dt);

			Mtx44 rotate;
			rotate.SetToRotation(yaw, 0, 1, 0);
			frontDir = rotate * frontDir;
			right = rotate * right;

			camera.right = rotate * camera.right;
			camera.up = rotate * camera.up;
			camera.view = rotate * camera.view;
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
	frontDir.y = 0;
	frontDir.Normalize();
	right.Normalize();

	xSpeed += ((frontDir.x * thrustSpeed)) * dt;
	ySpeed += ((frontDir.y * thrustSpeed) - WV_GRAVITY) * dt;
	zSpeed += ((frontDir.z * thrustSpeed)) * dt;
	position.x += xSpeed * dt;
	position.y += ySpeed * dt;
	position.z += zSpeed * dt;

	hitbox.SetPosition(position);

	bool xCollided = false;
	bool yCollided = false;
	bool zCollided = false;

	if (Hitbox::CheckHitBox(hitbox, oldPos, xCollided, yCollided, zCollided)){
		if (xCollided){
			position.x = oldPos.x;
			xSpeed = 0;
		}
		if (yCollided){
			position.y = oldPos.y;
			ySpeed = 0;
		}
		if (zCollided){
			position.z = oldPos.z;
			zSpeed = 0;
		}

		hitbox.SetPosition(position);
	}

	facingYaw = (((defaultFront.Cross(frontDir)).y / abs((defaultFront.Cross(frontDir)).y)) * Math::RadianToDegree(acos(defaultFront.Dot(frontDir))));
	std::cout << facingYaw << std::endl;

	camera.target = position;
	camera.Update(dt);
}