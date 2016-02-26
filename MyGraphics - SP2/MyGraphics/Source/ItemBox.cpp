#include "ItemBox.h"

std::vector<ItemObject*> ItemObject::ItemList;

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

ItemObject::~ItemObject()
{
}

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
			haveItem = true;
		RotationBool = true;
		canPut = true;
		counter = 0;
	}

	if (RotationBool == true)
	{
		rotateitem += (float(300 * dt));		
	}

	//////////////////
	//ITEM ANIMATION//
	//////////////////
}

void ItemObject::PickUp(Hitbox hitbox)
{
	if (Hitbox::CheckItems(this->hitbox, hitbox))
	{
		//std::cout << " TeSTTESTESTSEST " << std::endl;
		if (haveItem == false && ItemBoolInterval == false && oneTimeThing == false)
		{
			takeItem = true;
			ItemBoolInterval = true;
			ItemInterval = 0;
		}
		if (haveItem == true && ItemBoolInterval == false && oneTimeThing == false)
		{
			haveItem = false;
			dropItem = true;
			ItemBoolInterval = true;
			ItemInterval = 0;
		}
		buttonCoverBool = true;
		if (cbuttonRise == true)
		{
			buttonPressBool = true;
			mazeCheck = 1;
		}
	}
}

void ItemObject::ItemDelay(double dt)
{
	if (ItemBoolInterval == true)
	{
		ItemInterval += (float(1 * dt));
	}

	if (ItemInterval > 2)
	{
		ItemBoolInterval = false;
	}
}

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
	}
}