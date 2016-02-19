#ifndef SP2_H
#define SP2_H

#include <vector>

#include "Scene.h"
#include "Mtx44.h"
#include "Player.h"
#include "Camera_LockTarget.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Object.h"
#include "Turret.h"
#include "Projectile.h"
#include "Hitbox.h"
#include "Enemy.h"
#include "Countdown.h"
#include "MazeInteraction.h"

using std::vector;

class SP2 : public Scene
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
		GEO_INTERNAL_TOP,
		GEO_INTERNAL_LEFT,
		GEO_INTERNAL_RIGHT,
		GEO_INTERNAL_BOTTOM,
		GEO_INTERNAL_BACK,
		GEO_INTERNAL_FRONT,
		GEO_TEST,

		GEO_HITBOX,
		GEO_BASECAMP,
		GEO_ENEMYSHIP,
		GEO_TURRET_BASE,
		GEO_TURRET_HEAD,
		GEO_ALLYSHIP,
		GEO_TRAPS,
		GEO_SLIDEDOOR,
		GEO_DOOR,

		GEO_EXPLOSION,
		GEO_PORTAL_BODY,
		GEO_PORTAL_FRONT,
		GEO_PORTAL_BACK,

		GEO_Testitem1,//Test for pick up.
		GEO_Testitem2,
		GEO_Testitem3,
		GEO_TestitemExtra,
		GEO_UIBAR,

		GEO_ShipButtonStand,
		GEO_ShipButton,
		GEO_ShipButonCover,

		NUM_GEOMETRY
	};
	enum PLAYER_STATE
	{
		STATE_FPS,
		STATE_INTERACTING_MAZE,
		STATE_INTERACTING_TURRET,

		STATE_END
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

		U_TOTAL
	};

public:
	SP2();
	~SP2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderSkybox();
	void RenderSlideDoor();
	void DoorMovement(double dt);
	void RenderTraps();
	void TrapsMovement(double dt);
	void RenderAllyShip();
	void RenderEnemyShip();
	void RenderTurrets();
	void RenderBaseCamp();
	void RenderDoor();
	void UpdateDoor(double dt);
	void RenderPickUpObj();
	void RenderInternalSkybox();
	void MazeInteraction(double dt);
	void ArrangeObjs(int sizeX, int sizeZ, int distanceBetweenObjs);
	void RenderObjs(Mesh* mesh, bool light);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x = 0.f, float y = 0.f);
	void RenderQuadOnScreen(Mesh* mesh, Color color, float sizeX, float sizeY, float moveX = 0.f, float moveY = 0.f);
	

	//door
	float DoorMove;
	float DoorMove2;
	float timer;
	bool timerBool;
	bool Door;
	bool Door2;
	bool doorChk;
	bool front;
	bool back;

	float trapMove;
	bool backN;
	bool forth = true;

	Object portal;
	Object laserTrap;
	Object laserTrap1;
	Object laserTrap2;
	Object frontDoor;
	Object frontDoor2;
	Object backDoor;
	Object backDoor2;

	Object trapdoor;

	void RenderPortal();
	void UpdatePortal(double dt);
	Turret turret;
	void RenderTurret();

	void RenderExplosion();

	void SP2::Interval(double dt);

	void PickUp();
	void PickUpAnimation(double dt);

	void RenderShipButton();
	void PressButton();
	void ShipButtonAnimation(double dt);

	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Mesh *meshList[NUM_GEOMETRY];
	Countdown m_timer;

	vector<float> objArrangementData;

	bool enableLight;
	bool showHitBox;
	bool DoorMoveTrue;
	bool DoorReturn;

	bool itemText;//item pickup

	bool intervalBool;//Interval for ... anything i guess.

	bool buttonCoverBool;
	bool buttonRiseBool;
	bool buttonPressBool;
	bool cbuttonRise;

	float buttonCover;
	float buttonRise;

	float readyToUse;
	float readyToInteract;
	float readyToUse_HITBOX;
	float animation_rotatePortal;
	float animation_scalePortal;
	float animation_moveDoor;

	float towardsCameraYaw;

	int screenX, screenY;
	int playerState;

	Player player;

	Maze mappy;
	void RenderMaze();

	Enemy enemy;

	Mtx44 MVP;

	MS modelStack, viewStack, projectionStack;

	Light light[2];
};

#endif