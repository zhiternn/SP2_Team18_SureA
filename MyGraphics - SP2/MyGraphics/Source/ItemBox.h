#ifndef ITEMBOX_H
#define ITEMBOX_H

#include "Vector3.h"
#include "Hitbox.h"

class ItemObject
{
public:
	ItemObject();
	~ItemObject();

	Vector3 position;
	Hitbox hitbox;

	static std::vector<ItemObject*> ItemList;

	void SetPosition(float x, float y, float z);

	void PickUp(Hitbox hitbox);
	void PickUpAnimation(double dt);
	void ItemDelay(double dt);

	bool takeItem;//item pickup (Trigger to get item)
	bool growingbool;//item pickup (Growing bigger or smaller)
	bool growItem;//item pickup(can grow) if not cannot
	bool cangrowItem;
	bool haveItem;//item pickup
	bool putItem;//Float downwards after growing
	bool RotationBool;
	bool dropItem;//This Triggers to drop item
	bool canPut;
	bool oneTimeThing; 

	bool ItemBoolInterval;
	float ItemInterval;

	int counter;//item pickup

	float fly;//item floats(pickup)
	float growing;//item grows.(pickup)
	float rotateitem;//itemRotation(pickup)
private:
};

#endif