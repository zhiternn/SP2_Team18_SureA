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

	hitbox.SetSize(0.2f, 3, 0.2f);
	hitbox.SetPosition(pos);
}

void Player::Update(double dt)
{
	static const float CAMERA_SPEED = 10.f;
	static const float MOVEMENT_SPEED = 5.f;

	Vector3 oldPos = position;

	if (Application::IsKeyPressed('W'))
	{
		position.x += (view.x * MOVEMENT_SPEED * dt);
		position.z += (view.z * MOVEMENT_SPEED * dt);
	}
	if (Application::IsKeyPressed('S'))
	{
		position.x -= (view.x * MOVEMENT_SPEED * dt);
		position.z -= (view.z * MOVEMENT_SPEED * dt);
	}
	if (Application::IsKeyPressed('A'))
	{
		position.x -= (right.x * MOVEMENT_SPEED * dt);
		position.z -= (right.z * MOVEMENT_SPEED * dt);
	}
	if (Application::IsKeyPressed('D'))
	{
		position.x += (right.x * MOVEMENT_SPEED * dt);
		position.z += (right.z * MOVEMENT_SPEED * dt);
	}
	if (Application::IsKeyPressed(VK_SPACE))
	{
		vSpeed = MOVEMENT_SPEED * dt;
	}
	
	vSpeed -= (float)(WV_GRAVITY/5 * dt);
	position.y += vSpeed;
	hitbox.SetPosition(position);

	if (Hitbox::CheckHitBox(hitbox, position, oldPos)){
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