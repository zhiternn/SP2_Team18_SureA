/****************************************************************************/
/*!
\file ItemBox.cpp
\author Bek Kunta
\par email: xiaobek\@gmail.com
\brief
A Class that is define for the ItemBox in the game
*/
/****************************************************************************/
#include "ItemBox.h"

std::vector<ItemObject*> ItemObject::ItemList;

/****************************************************************************/
/*!
\brief ItemObject()
Setting hitbox position , hitboxSize, variables, and push back
*/
/****************************************************************************/
ItemObject::ItemObject()
{
	position.Set(0, 0, 0);
	hitbox.SetSize(0.5f, 0.5f, 0.5f);

	takeItem = false;//item
	growItem = false;//item
	growingbool = false;
	cangrowItem = false;
	haveItem = false;//item
	putItem = false;
	ItemBoolInterval = false;
	dropItem = false;
	canPut = false;
	oneTimeThing = false;

	buttonCoverBool = false;
	buttonRiseBool = false;
	buttonPressBool = false;
	cbuttonRise = false;

	TextCheck = false;
	ShipGuardCheck = false;

	mazeCheck = 0;
	buttonCover = 0;
	buttonRise = 0;
	counter = 0;

	ItemInterval = 0;
	fly = 0.001;//item
	growing = 0;//item grows.
	rotateitem = 0;//item rotation

	ItemObject::ItemList.push_back(this);
}
/****************************************************************************/
/*!
\brief
ItemObject Destructor
*/
/****************************************************************************/
ItemObject::~ItemObject()
{
}
/****************************************************************************/
/*!
\brief
SetPosition
\param x
a float position that represent X
\param y
a float position that represent Y
\param z
a float position that represent Z
*/
/****************************************************************************/
void ItemObject::SetPosition(float x, float y, float z)
{
	position.Set(
		x,
		y,
		z
		);
	hitbox.SetPosition(Vector3(
		position.x,
		position.y,
		position.z
		));
}
/****************************************************************************/
/*!
\brief
PickUpAnimation
\param dt
a dt to run its animation. item will float to then grow then it will than be picked up and stay on screen till its been put at the teleporter.
*/
/****************************************************************************/
void ItemObject::PickUpAnimation(double dt)
{
	//////////////////
	//ITEM ANIMATION//
	//////////////////

	if (takeItem == true)
	{
		fly += (float(1 * dt));
	}
	if (putItem == true)
	{
		fly -= (float(1 * dt));
	}

	if (fly > 1)
	{
		takeItem = false;//Stop movingup
		cangrowItem = true;
	}
	if (fly < 0)
	{
		putItem = false;
		dropItem = false;
		oneTimeThing = true;
	}

	if (cangrowItem == true && takeItem == false || dropItem == true)//
	{
		growItem = true;
	}
	else
	{
		growItem = false;
	}

	if (growItem == true && growingbool == true)
	{
		growing -= (float(333 * dt));
	}
	if (growItem == true && growingbool == false)
	{
		growing += (float(333 * dt));
	}
	if (growing < -1)
	{
		growingbool = false;
		counter++;
	}

	if (growing > 30)
	{
		growingbool = true;
		counter++;
	}

	if (counter > 11)
	{
		cangrowItem = false;
		if (dropItem == true)
		{
			putItem = true;
			counter = 0;
		}
		else
			if (putItem == false)
			{
				haveItem = true;
				RotationBool = true;
				canPut = true;
				counter = 0;
			}
	}

	if (RotationBool == true)
	{
		rotateitem += (float(300 * dt));		
	}

	//////////////////
	//ITEM ANIMATION//
	//////////////////
}
/****************************************************************************/
/*!
\brief
Collider
\param hitbox
a Hitbox check if player and item is colliding with each other
*/
/****************************************************************************/
void ItemObject::Collider(Hitbox hitbox)
{
	if (Hitbox::CheckItems(this->hitbox, hitbox)){
	
		ShipGuardCheck = true;
		TextCheck = true;
		if (haveItem == true && ItemBoolInterval == false && oneTimeThing == false)
		{
			haveItem = false;
			dropItem = true;
			ItemBoolInterval = true;
			ItemInterval = 0;
		}
	}
	else
	{
		ShipGuardCheck = false;
		TextCheck = false;
	}
}
/****************************************************************************/
/*!
\brief
PickUp
\param hitbox
a Hitbox check if player and item is colliding with each other
*/
/****************************************************************************/
void ItemObject::PickUp(Hitbox hitbox)
{
	if (Hitbox::CheckItems(this->hitbox, hitbox))
	{
		if (haveItem == false && ItemBoolInterval == false && oneTimeThing == false)
		{
			takeItem = true;
			ItemBoolInterval = true;
			ItemInterval = 0;
		}

		buttonCoverBool = true;
	
		if (cbuttonRise == true)
		{
			if (mazeCounter == 1){
				mazeCheck = 1;
			}
			buttonPressBool = true;
		}
	}
}
/****************************************************************************/
/*!
\brief
ItemDelay
\param double
a dt just for checking interval
*/
/****************************************************************************/
void ItemObject::ItemDelay(double dt)
{
	if (ItemBoolInterval == true)
	{
		ItemInterval += (float(1 * dt));
	}

	if (ItemInterval > 5)
	{
		ItemBoolInterval = false;
	}
}
/****************************************************************************/
/*!
\brief
ShipButtonAnimation
\param dt
a dt to run its animation.
When press maze would run.
*/
/****************************************************************************/
void ItemObject::ShipButtonAnimation(double dt)
{
	if (buttonCoverBool == true && buttonCover < 90)
	{
		buttonCover += (float(50 * dt));
	}
	if (buttonCover > 90)
	{
		buttonCoverBool = false;
		buttonRiseBool = true;
	}
	if (buttonRiseBool == true && cbuttonRise == false)
	{
		buttonRise += (float(1 * dt));
	}
	if (buttonRise > 1)
	{
		buttonRiseBool = false;
		cbuttonRise = true;
	}
	if (cbuttonRise == true && buttonPressBool == true)
	{
		buttonRise -= (float(1 * dt));
	}
	if (buttonRise < 0)
	{
		buttonPressBool = false;
		mazeCheck = 1;
		buttonRise = 0.f;
	}
	
}