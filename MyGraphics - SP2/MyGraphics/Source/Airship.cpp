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
	SetPosition(pos.x, pos.y, pos.z);

	this->frontDir = defaultFront = view.Normalized();
	this->normalDir = Vector3(0, 1, 0);
	this->right = this->defaultRight = (this->frontDir.Cross(this->normalDir)).Normalized();

	Mtx44 rotate;
	rotate.SetToRotation(-25, right.x, right.y, right.z);

	Vector3 forCamDir = rotate * view;

	camera.Init(pos + forCamDir * 3, pos, Vector3(0, 1, 0), 20.f);
	vSpeed = hSpeed = 0.f;
	frontThrust = upThrust = 0.f;

	facingYaw = 0.f;
}

void Airship::Update(double dt, bool controlling)
{
	static const float THRUST_SPEED = 100.f;
	static const float THRUST_LIMIT = 5.f;
	static const float TURN_SPEED = 100.f;

	Vector3 oldPos = position;

	if (controlling){
		if (Application::IsKeyPressed('W'))
		{
			if (frontThrust < THRUST_LIMIT)
				frontThrust += (float)(THRUST_SPEED * dt);
		}
		if (Application::IsKeyPressed('S'))
		{
			if (frontThrust > -THRUST_LIMIT)
				frontThrust -= (float)(THRUST_SPEED)* dt;
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

			facingYaw = (((defaultFront.Cross(frontDir)).y / abs((defaultFront.Cross(frontDir)).y)) * Math::RadianToDegree(acos(defaultFront.Dot(frontDir))));
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

			facingYaw = (((defaultFront.Cross(frontDir)).y / abs((defaultFront.Cross(frontDir)).y)) * Math::RadianToDegree(acos(defaultFront.Dot(frontDir))));
		}
		if (Application::IsKeyPressed(VK_SPACE))
		{
			upThrust += (THRUST_SPEED)* dt;
		}
		if (Application::IsKeyPressed(VK_LCONTROL))
		{
			upThrust -= (THRUST_SPEED)* dt;
		}

		camera.target = position;
		camera.Update(dt);
	}
	frontDir.y = 0;
	frontDir.Normalize();
	right.Normalize();
	normalDir.Normalize();

	vSpeed += (upThrust - (WV_GRAVITY*dt)) * dt;
	hSpeed += frontThrust * dt;
	position.x += frontDir.x * hSpeed * dt;
	position.y += vSpeed * dt;
	position.z += frontDir.z * hSpeed * dt;

	hitbox.SetPosition(position);

	//hitbox check
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
			vSpeed = 0;
		}
		if (zCollided){
			position.z = oldPos.z;
			hSpeed = 0;
		}

		hitbox.SetPosition(position);
	}

	//stabalize thrust
	if (upThrust > 0)
		upThrust -= THRUST_SPEED * dt;
	else if (upThrust < 0)
		upThrust += THRUST_SPEED * dt;
	else if (abs(upThrust) <= THRUST_SPEED * dt)
		upThrust = 0;

	if (frontThrust > 0)
		frontThrust -= THRUST_SPEED * dt;
	else if (frontThrust < 0)
		frontThrust += THRUST_SPEED * dt;
	else if (abs(frontThrust) <= THRUST_SPEED * dt)
		frontThrust = 0;
}