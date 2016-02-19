#include "Player.h"
#include "Application.h"
#include "Mtx44.h"
#include "WorldValues.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(const Vector3& pos, const Vector3& view)
{
	this->position = defaultPosition = pos;
	this->view = view.Normalized();
	this->right = this->view.Cross(Vector3(0, 1, 0)).Normalized();

	camera.Init(this->position, this->position+this->view, Vector3(0, 1, 0));

	vSpeed = 0.f;

	hitbox.SetSize(1.f, 3, 1.f);
	hitbox.SetPosition(pos);
}


void Player::Update(double dt)
{
	static const float CAMERA_SPEED = 20.f;
	static const float MOVEMENT_SPEED = 10.f;
	float SPRINT_MULTIPLIER = 3.f;

	Vector3 oldPos = position;
	/*if (Application::IsKeyPressed('C'))
	{
		crouch = true;
	}
	else
	{
		crouch = false;
	}

	if (crouch == true)
	{
		position.y = 0.5;
		hitbox.SetSize(0.2f, 1.5, 0.2f);
		speedMultiplier = 0.5;
	}
	if (crouch == false)
	{
		position.y = 1.5;
		hitbox.SetSize(0.2f, 3, 0.2f);
		speedMultiplier = 2;
	}




	if (Application::IsKeyPressed(VK_SHIFT)){
		if (tired == false && crouch == false){
			speedMultiplier = 10;
		}
	}
	if (crouch == false)
	{
		position.y = 1.5;
		hitbox.SetSize(0.2f, 3, 0.2f);
		speedMultiplier = 2;
	}*/

	// if not pressed, no speed increase
	if (!Application::IsKeyPressed(VK_SHIFT)){
		SPRINT_MULTIPLIER = 1.f;
	}
	if (Application::IsKeyPressed('W'))
	{
		position.x += (view.x * MOVEMENT_SPEED * SPRINT_MULTIPLIER * dt);
		position.z += (view.z * MOVEMENT_SPEED * SPRINT_MULTIPLIER * dt);
	}
	if (Application::IsKeyPressed('S'))
	{
		position.x -= (view.x * MOVEMENT_SPEED * SPRINT_MULTIPLIER * dt);
		position.z -= (view.z * MOVEMENT_SPEED * SPRINT_MULTIPLIER * dt);
	}
	if (Application::IsKeyPressed('A'))
	{
		position.x -= (right.x * MOVEMENT_SPEED * SPRINT_MULTIPLIER * dt);
		position.z -= (right.z * MOVEMENT_SPEED * SPRINT_MULTIPLIER * dt);
	}
	if (Application::IsKeyPressed('D'))
	{
		position.x += (right.x * MOVEMENT_SPEED * SPRINT_MULTIPLIER * dt);
		position.z += (right.z * MOVEMENT_SPEED * SPRINT_MULTIPLIER * dt);
	}
	if (Application::IsKeyPressed(VK_SPACE))
	{
		if (vSpeed == 0.f){
			vSpeed = 6.f * dt;
		}
	}
	//if (sprint1 >= 0)
	//{
	//	sprint1 -= 0.3 * dt;
	//	tired = false;
	//}

	//Conflicts with crouching
	/*vSpeed -= (float)(WV_GRAVITY / 5 * dt);
	position.y += vSpeed;*/
	//if (Application::IsKeyPressed(VK_CONTROL))
	//{
	//	hitbox.sizeY = 2.5f;
	//}
	//else{
	//	hitbox.sizeY = 3.f;
	//}

	vSpeed -= (float)(WV_GRAVITY * dt);
	position.y += vSpeed;
	hitbox.SetPosition(position);
	if (Hitbox::CheckHitBox(hitbox, position, oldPos, &hitbox))
	{
		vSpeed = 0.f;
	}

	double mouseX, mouseY;
	Application::GetMouseMovement(mouseX, mouseY);
	float yaw = (float)(mouseX * CAMERA_SPEED * dt);
	Mtx44 rotate;
	rotate.SetToRotation(yaw, 0, 1, 0);
	view = rotate * view;
	right = rotate * right;
	camera.up = rotate * camera.up;


	if (view.y < 0.95 && mouseY > 0 || view.y > -0.95 && mouseY < 0){
		float pitch = (float)(mouseY * CAMERA_SPEED * dt);
		rotate.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotate * view;
		right = rotate * right;
		camera.up = rotate * camera.up;
	}

	view.Normalize();
	right.Normalized();
	camera.up.Normalize();
	camera.Update(position, view);
}
	