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
	heatSystem = 0.f;
	heatAmount = (float)(20.f / atkSpeed);
	isOverHeated = false;
	
	forRotationYaw = forRotationPitch = 0.f;
	camera.Init(seatPos, barrelPos, up);
}

void Turret::Update(double dt, bool controlling)
{
	static float readyToShoot = 0.f;
	static float TURN_SPEED = 30.f;
	static float HEAT_LIMIT = 100.f;

	if (controlling){
		if (Application::IsKeyPressed('W')){
			if (view.y < 0.5f){
				float pitch = (float)(TURN_SPEED / 2 * dt);
				forRotationPitch += pitch;
				Mtx44 rotate;
				rotate.SetToRotation(pitch, right.x, right.y, right.z);
				view = rotate * view;
				right = rotate * right;
				up = rotate * up;
			}
		}
		if (Application::IsKeyPressed('S')){
			if (view.y > -0.5f){
				float pitch = -(float)(TURN_SPEED / 2 * dt);
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
			camera.view = rotate * camera.view;
			camera.right = rotate * camera.right;
			camera.up = rotate * camera.up;
		}
		if (Application::IsKeyPressed('D')){
			float yaw = -(float)(TURN_SPEED * dt);
			forRotationYaw += yaw;
			Mtx44 rotate;
			rotate.SetToRotation(yaw, 0, 1, 0);
			view = rotate * view;
			right = rotate * right;
			up = rotate * up;
			camera.view = rotate * camera.view;
			camera.right = rotate * camera.right;
			camera.up = rotate * camera.up;
		}

		barrelPos = seatPos + (view * (hitbox.sizeX / 1.5f));
		barrelPos.y -= (hitbox.sizeY*0.05);

		if ((Application::IsKeyPressed(VK_SPACE) || Application::IsKeyPressed(VK_LBUTTON)) && readyToShoot >= (float)(1.f / roundPerSecond) && !isOverHeated){
			readyToShoot = 0.f;
			sound.playSoundEffect("Sound//Gun1.mp3");
			Projectile::projectileList.push_back(new Projectile(
				Vector3(barrelPos.x, barrelPos.y, barrelPos.z),
				Vector3(view.x, view.y, view.z),
				150,
				65,
				10
				));
			heatSystem += heatAmount;
			if (heatSystem > HEAT_LIMIT){
				isOverHeated = true;
			}
		}
		else if (readyToShoot < (float)(1.f / roundPerSecond)){
			readyToShoot += (float)(dt);
		}

		camera.position = seatPos - view*0.5f;
		camera.Update(dt);
	}

	if (readyToShoot > (float)(1.f / roundPerSecond)){//only cool down when not shooting
		if (heatSystem > 0){
			heatSystem -= (float)(((isOverHeated * 3) + 1.0f) / roundPerSecond);//cool downs 3 times faster if overheated
		}
		else{
			heatSystem = 0;
			isOverHeated = false;
		}
	}
}

float Turret::GetPitch()
{
	return forRotationPitch;
}

float Turret::GetYaw()
{
	return forRotationYaw;
}