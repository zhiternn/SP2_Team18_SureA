#ifndef SCENE_4_H
#define SCENE_4_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera.h"
#include "Mesh.h"
#include "MatrixStack.h"

class Scene4 : public Scene
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
		GEO_SUN,
		GEO_PLANET1,
		GEO_MOON1,
		GEO_PLANET2,
		GEO_MOON2,
		GEO_MOON3,
		GEO_MOON4,

		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0, // MVP = MODEL VIEW PROJECTION

		U_TOTAL,
	};

public:
	Scene4();
	~Scene4();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_indexBuffer[NUM_GEOMETRY];
	Mesh *meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	float rotateAngle;
	float translateX;
	float scaleAll;
	float planet1RevAngle, planet1RotAngle, moon1RotAngle;

	Camera camera;

	Mtx44 MVP;

	MS modelStack, viewStack, projectionStack;
};

#endif