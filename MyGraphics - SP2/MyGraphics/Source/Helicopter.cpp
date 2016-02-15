#include "Helicopter.h"
#include "Application.h"
#include "Mtx44.h"
#include "WorldValues.h"

Helicopter::Helicopter()
{
}

Helicopter::~Helicopter()
{
}

void Helicopter::Init(const Vector3& pos, const Vector3& frontDir)
{
	this->position = pos;
	this->frontDir = defaultFront = frontDir.Normalized();
	this->thrustDir = Vector3(0, 1, 0);
	this->right = this->defaultRight = (this->frontDir.Cross(Vector3(0, 1, 0))).Normalized();

	camera.Init(pos-frontDir*-10.f, pos, Vector3(0, 1, 0));
	rotateYaw = rotatePitch = rotateRoll = 0.f;
	vSpeed = xSpeed = zSpeed = 0.f;

	hitbox.SetSize(1.8f, 1.5f, 1.8f);
	hitbox.SetPosition(position);
}

void Helicopter::Update(double dt, bool controlling)
{
	static const float THRUST_SPEED = 10.f;
	static const float THRUST_LIMIT = 5.f;
	static const float TURN_SPEED = 100.f;

	bool piloting = false;

	if (controlling){
		if (Application::IsKeyPressed('W'))
		{
			if (thrustSpeed < THRUST_LIMIT)
				thrustSpeed += (float)(THRUST_SPEED * dt);

			piloting = true;
		}
		if (Application::IsKeyPressed('S'))
		{
			if (thrustSpeed > -THRUST_LIMIT)
				thrustSpeed -= (float)(THRUST_SPEED * dt);

			piloting = true;
		}

		if (Application::IsKeyPressed('A'))
		{
			float yaw = (float)(TURN_SPEED * dt);

			rotateYaw += yaw;
			camera.Rotate(yaw, 0, 1, 0);

			Mtx44 rotate;
			rotate.SetToRotation(yaw, 0, 1, 0);
			thrustDir = rotate * thrustDir;
			frontDir = rotate * frontDir;
			right = rotate * right;
		}
		if (Application::IsKeyPressed('D'))
		{
			float yaw = (float)(-TURN_SPEED * dt);

			rotateYaw += yaw;
			camera.Rotate(yaw, 0, 1, 0);

			Mtx44 rotate;
			rotate.SetToRotation(yaw, 0, 1, 0);
			thrustDir = rotate * thrustDir;
			frontDir = rotate * frontDir;
			right = rotate * right;
		}
		if (Application::IsKeyPressed(VK_NUMPAD8))
		{
			float pitch = (float)(-TURN_SPEED * dt);

			rotatePitch += pitch;
			//camera.Rotate(pitch, right.x, right.y, right.z);

			Mtx44 rotate;
			rotate.SetToRotation(pitch, right.x, right.y, right.z);
			thrustDir = rotate * thrustDir;
			frontDir = rotate * frontDir;
			std::cout << frontDir << std::endl;
		}
		if (Application::IsKeyPressed(VK_NUMPAD5))
		{
			float pitch = (float)(TURN_SPEED * dt);

			rotatePitch += pitch;
			//camera.Rotate(pitch, right.x, right.y, right.z);

			Mtx44 rotate;
			rotate.SetToRotation(pitch, right.x, right.y, right.z);
			thrustDir = rotate * thrustDir;
			frontDir = rotate * frontDir;
		}
		if (Application::IsKeyPressed(VK_NUMPAD4))
		{
			float roll = (float)(-TURN_SPEED * dt);

			rotateRoll += roll;

			Mtx44 rotate;
			rotate.SetToRotation(roll, frontDir.x, frontDir.y, frontDir.z);
			thrustDir = rotate * thrustDir;
			right = rotate * right;
		}
		if (Application::IsKeyPressed(VK_NUMPAD6))
		{
			float roll = (float)(TURN_SPEED * dt);

			rotateRoll += roll;

			Mtx44 rotate;
			rotate.SetToRotation(roll, frontDir.x, frontDir.y, frontDir.z);
			thrustDir = rotate * thrustDir;
			right = rotate * right;
		}
	}
	if (!piloting){
		if (thrustSpeed > 0.f){
			thrustSpeed -= (float)(THRUST_SPEED * dt);
		}
		else if (thrustSpeed < 0.f){
			thrustSpeed += (float)(THRUST_SPEED * dt);
		}
	}

	frontDir.Normalize();
	right.Normalize();
	thrustDir.Normalize();

	Vector3 oldPos = position;

	vSpeed += ((thrustDir.y * thrustSpeed) - WV_GRAVITY) * dt;
	xSpeed += ((thrustDir.x * thrustSpeed)) * dt;
	zSpeed += ((thrustDir.z * thrustSpeed)) * dt;
	position.x += xSpeed * dt;
	position.z += zSpeed * dt;
	position.y += vSpeed * dt;
	hitbox.SetPosition(position);

	if (Hitbox::CheckHitBox(hitbox, position, oldPos, &hitbox)){
		vSpeed = 0.f;
		xSpeed = 0.f;
		zSpeed = 0.f;
	}


	camera.target = position;
	camera.Update(dt);
}