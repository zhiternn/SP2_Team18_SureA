#ifndef SceneSkybox_H
#define SceneSkybox_H

#include "Scene.h"
#include "Mtx44.h"
#include "Mesh.h"
#include "Camera2.h"
#include "MatrixStack.h"
#include "Light.h"

class SceneSkybox : public Scene
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

		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,

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
		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,

		U_TOTAL,
	};

public:
	SceneSkybox();
	~SceneSkybox();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderSkybox();

	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Mesh *meshList[NUM_GEOMETRY];

	bool enableLight;
	float readyToUse;

	Camera2 camera;

	Mtx44 MVP;

	MS modelStack, viewStack, projectionStack;

	Light light[1];
};

#endif