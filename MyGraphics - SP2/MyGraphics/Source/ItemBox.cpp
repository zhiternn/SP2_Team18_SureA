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

	counter = 0;

	ItemInterval = 0;
	fly = 0;//item
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
		position.x + x,
		position.y + y,
		position.z + z
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
		counter = 0;
	}

	if (haveItem == true)
	{
<<<<<<< 307a8fcf3c21a0f84ea433b3229ee076b509c3fc
		rotateitem += (float(300 * dt));
=======
		rotateitem += (float(10 * dt));
>>>>>>> bd9c702d3df292aab4f2d10d95406523bd2211a8
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
		if (haveItem == false && ItemBoolInterval == false)
		{
			takeItem = true;
			ItemBoolInterval = true;
			ItemInterval = 0;
		}
		if (haveItem == true && ItemBoolInterval == false)
		{
			haveItem = false;
			dropItem = true;
			ItemBoolInterval = true;
			ItemInterval = 0;
		}
	}
}

void ItemObject::ItemDelay(double dt)
{
	if (ItemBoolInterval == true)
	{
		ItemInterval += (float)(50 * dt);
	}

	if (ItemInterval > 50)
	{
		ItemBoolInterval = false;
	}

}