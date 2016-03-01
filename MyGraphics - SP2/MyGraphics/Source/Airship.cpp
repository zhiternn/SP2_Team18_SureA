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

void Airship::Init(const Vector3& pos, const Vector3& view)
{
	this->position = pos;
	this->view = defaultFront = view.Normalized();
	this->up = Vector3(0, 1, 0);
	this->right = this->defaultRight = (this->view.Cross(this->up)).Normalized();

	Mtx44 rotate;
	rotate.SetToRotation(-25, right.x, right.y, right.z);

	Vector3 forCamDir = rotate * view;

	camera.Init(pos + forCamDir * 3, pos, Vector3(0, 1, 0));
	ySpeed = hSpeed = 0.f;

	facingYaw = 0.f;
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
			view = rotate * view;
			right = rotate * right;

			camera.right = rotate * camera.right;
			camera.up = rotate * camera.up;
			camera.view = rotate * camera.view;

			facingYaw = (((defaultFront.Cross(view)).y / abs((defaultFront.Cross(view)).y)) * Math::RadianToDegree(acos(defaultFront.Dot(view))));
		}
		if (Application::IsKeyPressed('D'))
		{
			float yaw = (float)(-TURN_SPEED * dt);

			Mtx44 rotate;
			rotate.SetToRotation(yaw, 0, 1, 0);
			view = rotate * view;
			right = rotate * right;

			camera.right = rotate * camera.right;
			camera.up = rotate * camera.up;
			camera.view = rotate * camera.view;

			facingYaw = (((defaultFront.Cross(view)).y / abs((defaultFront.Cross(view)).y)) * Math::RadianToDegree(acos(defaultFront.Dot(view))));
		}
		if (Application::IsKeyPressed('W'))
		{
			ySpeed += (THRUST_LIMIT/2) * dt;
		}
		if (Application::IsKeyPressed('S'))
		{
			ySpeed -= (THRUST_LIMIT/2) * dt;
		}

		camera.target = position;
		camera.Update(dt);
	 }
	view.y = 0;
	view.Normalize();
	right.Normalize();

	ySpeed += ((view.y * thrustSpeed) - WV_GRAVITY) * dt;
	hSpeed += thrustSpeed * dt;
	position.x += view.x * hSpeed * dt;
	position.y += ySpeed * dt;
	position.z += view.z * hSpeed * dt;

	hitbox.SetPosition(position);

	bool xCollided = false;
	bool yCollided = false;
	bool zCollided = false;

	if (Hitbox::CheckHitBox(hitbox, oldPos, xCollided, yCollided, zCollided)){
		if (xCollided){
			position.x = oldPos.x;
			hSpeed = 0;
		}
		if (yCollided){
			position.y = oldPos.y;
			ySpeed = 0;
		}
		if (zCollided){
			position.z = oldPos.z;
			hSpeed = 0;
		}

		hitbox.SetPosition(position);
	}
}