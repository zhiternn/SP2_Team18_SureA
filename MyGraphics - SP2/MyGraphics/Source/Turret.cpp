#include "Turret.h"
#include "Application.h"
#include "Projectile.h"
#include "Mtx44.h"

Turret::Turret(Vector3 pos, Vector3 dir)
{
}

Turret::~Turret()
{
}

void Turret::Init(Vector3 pos, Vector3 dir, int atkSpeed)
{
	SetPosition(pos.x, pos.y, pos.z);
	view = dir.Normalized();

	seatPos = position;
	seatPos.y += hitbox.sizeY*0.85;

	barrelPos = seatPos + (view * (hitbox.sizeX / 1.5f));

	roundPerSecond = atkSpeed;
	
	forRotationYaw = forRotationPitch = 0.f;
	
	camera.Init(seatPos, barrelPos, up);
}

void Turret::Update(double dt)
{
	static float readyToShoot = 0.f;
	static float TURN_SPEED = 15.f;

	if (Application::IsKeyPressed('W')){
		if (view.y > -0.5f){
			float pitch = -(float)(TURN_SPEED * dt);
			forRotationPitch += pitch;
			Mtx44 rotate;
			rotate.SetToRotation(pitch, right.x, right.y, right.z);
			view = rotate * view;
			right = rotate * right;
			up = rotate * up;
		}
	}
	if (Application::IsKeyPressed('S')){
		if (view.y < 0.5f){
			float pitch = (float)(TURN_SPEED * dt);
			forRotationPitch += pitch;
			Mtx44 rotate;
			rotate.SetToRotation(pitch, right.x, right.y, right.z);
			view = rotate * view;
			right = rotate * right;
			up = rotate * up;
		}
	}
	if (Application::IsKeyPressed('A')){
		float yaw = (float)(TURN_SPEED * dt);
		forRotationYaw += yaw;
		Mtx44 rotate;
		rotate.SetToRotation(yaw, 0, 1, 0);
		view = rotate * view;
		right = rotate * right;
		up = rotate * up;
	}
	if (Application::IsKeyPressed('D')){
		float yaw = -(float)(TURN_SPEED * dt);
		forRotationYaw += yaw;
		Mtx44 rotate;
		rotate.SetToRotation(yaw, 0, 1, 0);
		view = rotate * view;
		right = rotate * right;
		up = rotate * up;
	}

	barrelPos = seatPos + (view * (hitbox.sizeX / 1.5f));
	barrelPos.y -= (hitbox.sizeY*0.05);

	if (Application::IsKeyPressed(VK_SPACE) && readyToShoot >= (float)(1.f/roundPerSecond)){
		readyToShoot = 0.f;
		Projectile::projectileList.push_back(new Projectile(
			Vector3(barrelPos.x, barrelPos.y, barrelPos.z),
			Vector3(view.x, view.y, view.z),
			100,
			50,
			5
			));
	}
	else if (readyToShoot < (float)(1.f/roundPerSecond)){
		readyToShoot += (float)(dt);
	}

	camera.Update(dt);
}

float Turret::GetPitch()
{
	return forRotationPitch;
}
float Turret::GetYaw()
{
	return forRotationYaw;
}