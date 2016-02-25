#ifndef PLAYER_H
#define PLAYER_H

#include "Vector3.h"
#include "Hitbox.h"
#include "Camera.h"

class Player
{
public:

	Vector3 defaultPosition;
	Vector3 defaultView;

	Vector3 position;
	Vector3 view;
	Vector3 right;

	Hitbox hitbox;
	Camera camera;

	float vSpeed;
	int sprintMeter = 0;

	bool isSprinting;
	float SprintDuration;
	bool tired;
	bool crouch = false;
	bool jump;

	Player();
	~Player();
	void Init(const Vector3& pos, const Vector3& view);
	void Update(double dt);
private:
};

#endif