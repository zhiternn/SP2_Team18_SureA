#ifndef ASSIGNMENT_2_H
#define ASSIGNMENT_2_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera2.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"

#include <vector>

using std::vector;

class Assignment2 : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES = 0,
		GEO_QUAD,
		GEO_CUBE,
		GEO_ELLIPSE,
		GEO_TORUS,
		GEO_SPHERE,
		GEO_HEMISPHERE,
		GEO_RING,
		GEO_CYLINDER,
		GEO_CONE,

		GEO_LIGHTBALL,

		GEO_TREE_LEAVES,
		GEO_TREE_TRUNK,

		GEO_HEAD_CORE,
		GEO_HEAD_EYES1,
		GEO_HEAD_EYES2,
		GEO_HEAD_NOSE,
		GEO_HELMET_CORE,
		GEO_HELMET_FOREHEAD,
		GEO_HELMET_EARS,
		GEO_HELMET_EARS2,
		GEO_BODY_UPPER,
		GEO_BODY_LOWER,
		GEO_SHOULDER,
		GEO_ARM_UPPER,
		GEO_ARM_CANNON_CORE,
		GEO_ARM_CANNON_TIP,
		GEO_LEG_UPPER,
		GEO_LEG_JOINT,
		GEO_LEG_LOWER,
		GEO_LEG_FOOT,

		NUM_GEOMETRY
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
		U_TOTAL,
	};

public:
	Assignment2();
	~Assignment2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	void RenderMesh(Mesh *mesh, bool enableLight);

	void RenderTrees();
	void RenderHead();
	void RenderBody();
	void RenderUpperArm(int mirror);
	void RenderLowerArm(int mirror);
	void RenderUpperLeg(int mirror);
	void RenderLowerLeg(int mirror);

	void ArrangeTrees(int fromX, int toX, int fromZ, int toZ, int distanceBetweenTrees);

	void AnimateRun(double dt);
	void AnimateShoot(double dt);

	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	Mesh *meshList[NUM_GEOMETRY];

	float upperLegRunning, lowerLegRunning, lowerLegRunValue;
	int lowerLegDir, upperLegDir;

	float upperArmShooting, upperArmRunning, cannonShooting;
	bool isShootingAnimation, canShoot;

	bool onLights;

	vector<float> treeArrangementData;

	Camera camera;

	Vector3 megamanPosition, megamanDirection;
	
	Mtx44 MVP;

	MS modelStack, viewStack, projectionStack;

	Light light[2];
};

#endif