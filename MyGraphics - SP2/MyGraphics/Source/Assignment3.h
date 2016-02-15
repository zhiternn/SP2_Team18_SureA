#ifndef ASSIGNMENT3_H
#define ASSIGNMENT3_H

#include <vector>

#include "Scene.h"
#include "Mtx44.h"
#include "Player.h"
#include "Camera_LockTarget.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Helicopter.h"
#include "Object.h"
#include "Projectile.h"
#include "Hitbox.h"

using std::vector;

class Assignment3 : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES = 0,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_LIGHTBALL,
		GEO_FLOOR,
		GEO_TEXT,
		
		GEO_HITBOX,
		
		GEO_VEHICLE_SPACE_AIR,
		GEO_VEHICLE_SPACE_AIR2,
		GEO_VEHICLE_SPACE_LAND,
		GEO_BOUNDARY,
		GEO_PORTAL_BODY,
		GEO_PORTAL_FRONT,
		GEO_PORTAL_BACK,
		GEO_LAMP,
		GEO_BOX,
		GEO_EXPLOSION,

		UI_DUAL_GUNS,

		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0, // MVP = MODEL VIEW PROJECTION
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,

		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,

		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_TYPE,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,

		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		U_TOTAL,
	};
	enum CONTROLLING
	{
		CONTROLLING_PLAYER,
		CONTROLLING_HELICOPTER,

		CONTROLLING_TOTAL,
	};

public:
	Assignment3();
	~Assignment3();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderSkybox();
	void ArrangeObjs(int sizeX, int sizeZ, int distanceBetweenObjs);
	void RenderObjs(Mesh* mesh, bool light);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x = 0.f, float y = 0.f);
	void RenderQuadOnScreen(Mesh* mesh, Color color, float sizeX, float sizeY, float moveX = 0.f, float moveY = 0.f);

	Object portal;
	void RenderPortal();
	void UpdatePortal(double dt);
	Object lamp;
	void RenderLamp();
	Object bigShip;
	void RenderBigShip();
	void RenderExplosion();

	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Mesh *meshList[NUM_GEOMETRY];

	vector<float> objArrangementData;
	vector<Projectile*> bulletsList;

	bool enableLight;
	bool showHitBox;
	bool lampLight;

	float readyToUse;
	float readyToInteract;
	float readyToUse_HITBOX;
	float readyToUse_SHOOT;
	float animation_rotatePortal;
	float animation_scalePortal;

	int screenX, screenY;

	short controlState;

	Player player;

	Helicopter helicopter;

	Mtx44 MVP;

	MS modelStack, viewStack, projectionStack;

	Light light[2];
};

#endif