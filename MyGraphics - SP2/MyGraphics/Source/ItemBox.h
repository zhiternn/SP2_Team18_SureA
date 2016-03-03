/****************************************************************************/
/*!
\file ItemBox.h
\author Bek Kunta
\par email: xiaobek\@gmail.com
\brief
A Class that is define for the ItemBox in the game
*/
/****************************************************************************/
#ifndef ITEMBOX_H
#define ITEMBOX_H

#include "Vector3.h"
#include "Hitbox.h"
/****************************************************************************/
/*!
Class ItemObject:
\brief Defines ItemObject and its methods,functions and variables used.
*/
/****************************************************************************/

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
	void Collider(Hitbox hitbox);
	void PickUpAnimation(double dt);
	void ItemDelay(double dt);
	void PressButton();
	void ShipButtonAnimation(double dt);

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
	bool buttonCoverBool;
	bool buttonRiseBool;
	bool buttonPressBool;
	bool cbuttonRise;
	bool TextCheck;
	bool ShipGuardCheck;

	int mazeCheck;
	int mazeCounter;

	bool ItemBoolInterval;
	float ItemInterval;

	int counter;//item pickup

	float buttonCover;
	float buttonRise;

	float fly;//item floats(pickup)
	float growing;//item grows.(pickup)
	float rotateitem;//itemRotation(pickup)
private:
};

#endif