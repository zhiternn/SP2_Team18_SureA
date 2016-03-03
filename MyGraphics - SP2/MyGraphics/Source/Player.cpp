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
	SprintDuration = 2.f;

	hitbox.SetSize(1.f, 3, 1.f);
	hitbox.SetPosition(pos);
}


void Player::Update(double dt)
{
	static const float CAMERA_SPEED = 5.f;
	static const float MOVEMENT_SPEED = 10.f;
	float SPRINT_MULTIPLIER = 1.f;

	Vector3 oldPos = position;

	//std::cout << SprintDuration << std::endl;

	// if not pressed, no speed increase

	if (Application::IsKeyPressed(VK_SHIFT) && tired == false && Application::IsKeyPressed('W')){
		SPRINT_MULTIPLIER = 2.5f;
		SprintDuration -= 0.5 * dt;
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

	if (SprintDuration < 0)
	{
		tired = true;
	}
	if (SprintDuration > 0)
	{
		tired = false;
	}
	if (SprintDuration < 2)
	{
		SprintDuration += 0.1 * dt;
	}
	if (SprintDuration > 2)
	{
		SprintDuration = 2;

	}



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

		bool xCollided = false;
		bool yCollided = false;
		bool zCollided = false;

		if (Hitbox::CheckHitBox(hitbox, oldPos, xCollided, yCollided, zCollided)){
			if (xCollided){
				position.x = oldPos.x;
			}
			if (yCollided){
				position.y = oldPos.y;
				vSpeed = 0;
			}
			if (zCollided){
				position.z = oldPos.z;
			}

			hitbox.SetPosition(position);
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
		Application::SetMousePosition();
}

