#include "Assignment2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"


Assignment2::Assignment2()
{
}

Assignment2::~Assignment2()
{
}

void Assignment2::Init()
{
	// Load vertex and fragment shaders
	m_programID = LoadShaders(
		"Shader//Shading.vertexshader",
		"Shader//LightSource.fragmentshader"
		);
	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");

	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	// Use our shader
	glUseProgram(m_programID);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Enable culling
	glEnable(GL_CULL_FACE);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	projectionStack.LoadMatrix(projection);

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	camera.Init(Vector3(0, 10, 20), Vector3(0, 10, 0), Vector3(0, 1, 0));

	//MESH GENERATORS
	//meshList[GEO_QUAD] =		MeshBuilder::GenerateQuad("Quad", 1, 1, Color(1, 1, 1))
	//meshList[GEO_CUBE] =		MeshBuilder::GenerateCube
	//meshList[GEO_ELLIPSE] =		MeshBuilder::GenerateEllipse
	//meshList[GEO_TORUS] =		MeshBuilder::GenerateTorus
	//meshList[GEO_SPHERE] =		MeshBuilder::GenerateSphere
	//meshList[GEO_HEMISPHERE] =	MeshBuilder::GenerateHemisphere
	//meshList[GEO_RING] =		MeshBuilder::GenerateRing
	//meshList[GEO_CYLINDER] =	MeshBuilder::GenerateCylinder
	//meshList[GEO_CONE] =		MeshBuilder::GenerateCone

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("axis", 1000, 1000, 1000);
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("sphere", 0.5f, 0.5f, 0.5f, Color(1, 1, 1));
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("floor", 1000, 1000, Color(0.3f, 0.3f, 0.3f));

	meshList[GEO_TREE_LEAVES] = MeshBuilder::GenerateCone("Cone", 1, 1, 1, Color(0, 0.8f, 0));
	meshList[GEO_TREE_TRUNK] = MeshBuilder::GenerateCylinder("Cylinder", 1, 1, 1, Color(0.85f, 0.65f, 0.13f));

	meshList[GEO_HEAD_CORE] = MeshBuilder::GenerateSphere2("sphere", 3.4f, 3.4f, 3.4f, Color(1.f, 0.85f, 0.7f), 18, 27);
	meshList[GEO_HEAD_CORE]->material.kAmbient.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_HEAD_CORE]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_HEAD_CORE]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_HEAD_CORE]->material.kShininess = 1.f;
	meshList[GEO_HEAD_EYES1] = MeshBuilder::GenerateEllipse("Ellipse", 0.5f, 1.f, Color(1, 1, 1));
	meshList[GEO_HEAD_EYES2] = MeshBuilder::GenerateEllipse("Ellipse", 0.4f, 0.9f, Color(0, 0, 0.5f));
	meshList[GEO_HEAD_NOSE] = MeshBuilder::GenerateCone("Ellipse", 0.15f, 0.15f, 0.15f, Color(1.f, 0.85f, 0.7f));
	meshList[GEO_HELMET_CORE] = MeshBuilder::GenerateSphere2("Hemisphere", 3.5f, 3.5f, 3.5f, Color(0.22f, 0.45f, 0.72f), 13, 36);
	meshList[GEO_HELMET_FOREHEAD] = MeshBuilder::GenerateSphere2("sphere", 3.4f, 3.4f, 3.4f, Color(0.22f, 0.45f, 0.72f), 18, 9);
	meshList[GEO_HELMET_EARS] = MeshBuilder::GenerateTorus("Torus", 0.4f, 0.2f, 2.5f, 1.5f, 2.5f, Color(0.47f, 0.77f, 0.86f), 8, 4);
	meshList[GEO_HELMET_EARS2] = MeshBuilder::GenerateHemisphere("Hemisphere", 0.75f, 0.25f, 0.75f, Color(0.8f, 0, 0), true);
	meshList[GEO_HELMET_EARS2]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_HELMET_EARS2]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HELMET_EARS2]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_HELMET_EARS2]->material.kShininess = 1.f;

	meshList[GEO_BODY_UPPER] = MeshBuilder::GenerateCylinder("MM_BODY", 1.5f, 1.5f, 3.5f, Color(0.47f, 0.77f, 0.86f), 1.7f, 1.5f);
	meshList[GEO_BODY_LOWER] = MeshBuilder::GenerateHemisphere("MM_BODY", 1.7f, 1.5f, 1.5f, Color(0.22f, 0.45f, 0.72f), true);

	meshList[GEO_SHOULDER] = MeshBuilder::GenerateSphere("sphere", 0.5f, 0.5f, 0.5f, Color(0.47f, 0.77f, 0.86f));
	meshList[GEO_ARM_UPPER] = MeshBuilder::GenerateCylinder("cylinder", 0.5f, 0.5f, 2.5f, Color(0.47f, 0.77f, 0.86f));
	meshList[GEO_ARM_CANNON_CORE] = MeshBuilder::GenerateSphere("sphere", 1.7f, 1.3f, 1.3f, Color(0.22f, 0.45f, 0.72f));
	meshList[GEO_ARM_CANNON_TIP] = MeshBuilder::GenerateTorus("torus", 0.5f, 0.25f, 1.f, 1.f, 1.f, Color(0.22f, 0.45f, 0.72f));


	meshList[GEO_LEG_UPPER] = MeshBuilder::GenerateCylinder("cylinder", 0.5f, 0.5f, 2.f, Color(0.47f, 0.77f, 0.86f), 0.55, 0.55);
	meshList[GEO_LEG_JOINT] = MeshBuilder::GenerateSphere("sphere", 0.55f, 0.55f, 0.55f, Color(0.47f, 0.77f, 0.86f));
	meshList[GEO_LEG_LOWER] = MeshBuilder::GenerateCylinder("cylinder", 0.6f, 0.6f, 2.f, Color(0.22f, 0.45f, 0.72f), 0.9f, 0.9f);
	meshList[GEO_LEG_FOOT] = MeshBuilder::GenerateHemisphere("hemisphere", 0.9f, 1, 1.3f, Color(0.22f, 0.45f, 0.72f));

	glUniform1i(m_parameters[U_NUMLIGHTS], 2);
	//setting up light object
	light[0].type = Light::LIGHT_POINT;
	light[0].position.Set(0, 20, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);
	//pass uniform parameters ( MUST BE AFTER glUseProgram() )
	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

	//SECOND LIGHT
	//setting up light object
	light[1].type = Light::LIGHT_POINT;
	light[1].position.Set(0, 10, 0);
	light[1].color.Set(1, 1, 1);
	light[1].power = 1;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f);
	//pass uniform parameters ( MUST BE AFTER glUseProgram() )
	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);
	

	//Initializing transforming matrices
	ArrangeTrees(-300, 300, -300, 300, 100);

	megamanPosition.Set(0, 6.75, 0);// position where we translated megaman's body core
	megamanDirection.Set(0, 0, 1);// megaman default facing direction is the Z axis

	onLights = true;

	upperLegRunning = lowerLegRunning = lowerLegRunValue = 0.f;
	lowerLegDir = upperLegDir = 1;

	upperArmShooting = cannonShooting = upperArmRunning = 0.f;
	isShootingAnimation = false;
	canShoot = false;
}

void Assignment2::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();

	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);

	if (enableLight && onLights){
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();

		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE,
			&modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	mesh->Render();
}

void Assignment2::Update(double dt)
{
	camera.Update(dt);
	if (Application::IsKeyPressed(0x31))
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed(0x32))
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed(0x33))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (Application::IsKeyPressed(0x34))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (Application::IsKeyPressed('I'))
		light[0].position.z -= (float)(50.f * dt);
	if (Application::IsKeyPressed('K'))
		light[0].position.z += (float)(50.f * dt);
	if (Application::IsKeyPressed('J'))
		light[0].position.x -= (float)(50.f * dt);
	if (Application::IsKeyPressed('L'))
		light[0].position.x += (float)(50.f * dt);
	if (Application::IsKeyPressed('U'))
		light[0].position.y -= (float)(50.f * dt);
	if (Application::IsKeyPressed('O'))
		light[0].position.y += (float)(50.f * dt);
	if (Application::IsKeyPressed('Q')){
		if (onLights){
			onLights = false;
		}
		else{
			onLights = true;
		}
	}
	if (Application::IsKeyPressed('B')){
		light[0].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	if (Application::IsKeyPressed('N')){
		light[0].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	if (Application::IsKeyPressed('M')){
		light[0].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}

	if (Application::IsKeyPressed('T')){
		isShootingAnimation = true;

		if (upperArmRunning == 0)//Makes sure arm is in proper position
			AnimateShoot(dt);
	}
	else{
		canShoot = false;
		isShootingAnimation = false;
		if (upperArmShooting < 0.f)// puts arms back into normal position
			upperArmShooting += (float)(180 * dt);
		if (cannonShooting > 0.f)// puts cannon back into normal position
			cannonShooting -= (float)(180 * dt);

		if (upperArmShooting > -5.f && upperArmShooting < 5.f){
			upperArmShooting = 0.f;
		}
	}
	if (Application::IsKeyPressed('R')){
		AnimateRun(dt);
	}
	else{
		/* UPPER LEG RUNNING */
		if (upperLegRunning > 0)
			upperLegRunning -= (float)(180 * dt);
		else if (upperLegRunning < 0)
			upperLegRunning += (float)(180 * dt);

		/* LOWER LEG RUNNING */
		if (lowerLegRunning > 0)
			lowerLegRunning -= (float)(180 * dt);
		else if (lowerLegRunning < 0)
			lowerLegRunning += (float)(180 * dt);

		/* LOWER LEG VALUE */
		if (lowerLegRunValue > 0.f)
			lowerLegRunValue -= (float)(180 * dt);

		//SET TO ZERO IF NEAR ZERO
		if (upperLegRunning > -5.f && upperLegRunning < 5.f){
			upperLegRunning = 0.f;
		}
		if (lowerLegRunning > -5.f && lowerLegRunning < 5.f){
			lowerLegRunning = 0.f;

		/* UPPER ARM RUNNING */
		upperArmRunning = upperLegRunning;
		}
	}
}

void Assignment2::Render()
{
	// Clear color & depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);
	modelStack.LoadIdentity();

	if (light[0].type == Light::LIGHT_DIRECTIONAL){
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[0].type == Light::LIGHT_SPOT){
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}
	if (canShoot){
		light[1].color.Set(1, 1, 1);
		glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	}
	else{
		light[1].color.Set(0, 0, 0);
		glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	}
	Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
	glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);

	RenderMesh(meshList[GEO_AXES], false);

	modelStack.PushMatrix();
	modelStack.Translate(
		light[0].position.x,
		light[0].position.y,
		light[0].position.z
		);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(-90, 1, 0, 0);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();

	/*******************************************************************************/
	// LEVEL 1 - BODY - START
	modelStack.PushMatrix();
	modelStack.Translate(0, 6.75f, 0);
	/*******************************************************************************/

	RenderBody();

	/*******************************************************************************/
	// LEVEL 2 - HEAD - START
	modelStack.PushMatrix();
	/*******************************************************************************/

	RenderHead();

	/*******************************************************************************/
	// LEVEL 2 - HEAD - END
	modelStack.PopMatrix();
	/*******************************************************************************/

	/*******************************************************************************/
	//LEVEL 2 - JOINT AND UPPER ARM - START
	for (int mirror = 1; mirror >= -1; mirror -= 2){
		modelStack.PushMatrix();
		modelStack.Translate(mirror*(-1.5f), 1.2f, 0);
		modelStack.Rotate(mirror*-upperArmRunning + upperArmShooting, 1, 0, 0);
		modelStack.Rotate(mirror*60, 0, 0, 1);
	/*******************************************************************************/
		
		RenderUpperArm(mirror);

	/*******************************************************************************/
	// LEVEL 3 - CANNON - START
		modelStack.PushMatrix();
		modelStack.Translate(mirror*(-3.5f), 0, 0);
		modelStack.Rotate(mirror*cannonShooting, 0, 0, 1);
	/*******************************************************************************/

		RenderLowerArm(mirror);

	/*******************************************************************************/
	// LEVEL 3 - CANNON - END
		modelStack.PopMatrix();
	/*******************************************************************************/

	/*******************************************************************************/
	// LEVEL 2 - JOINT AND UPPER ARM - END
		modelStack.PopMatrix();
	}
	/*******************************************************************************/

	/*******************************************************************************/
	// LEVEL 2 - UPPER LEG AND JOINT - START
	for (int mirror = 1; mirror >= -1; mirror -= 2){
		modelStack.PushMatrix();
		modelStack.RotateFromPivot(0, -1.75, 0, mirror*upperLegRunning, 1, 0, 0);
		modelStack.Translate(mirror*-0.9f, -3.5f, 0);
		/*******************************************************************************/

		RenderUpperLeg(mirror);

		/*******************************************************************************/
		// LEVEL 3 - LOWER LEG AND FOOT - START
		modelStack.PushMatrix();
		modelStack.Translate(0, -2, 0);
		modelStack.RotateFromPivot(0, 1, 0, mirror*lowerLegRunning + lowerLegRunValue, 1, 0, 0);
		/*******************************************************************************/

		RenderLowerLeg(mirror);

		/*******************************************************************************/
		// LEVEL 3 - LOWER LEG AND FOOT - END
		modelStack.PopMatrix();
		/*******************************************************************************/

		/*******************************************************************************/
		// LEVEL 2 - UPPER LEG AND JOINT - END
		modelStack.PopMatrix();
	}
	/*******************************************************************************/

	/*******************************************************************************/
	// LEVEL 1 - BODY - END
	modelStack.PopMatrix();
	/*******************************************************************************/

	RenderTrees();
}

void Assignment2::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void Assignment2::RenderTrees()
{
	for (int i = 0; i < treeArrangementData.size(); i += 5){
		modelStack.PushMatrix();
		modelStack.Translate(treeArrangementData[i], treeArrangementData[1 + i], treeArrangementData[2 + i]);

		modelStack.PushMatrix();
		modelStack.Scale(1.3f + treeArrangementData[4 + i], 6 + treeArrangementData[3 + i], 1.3f + treeArrangementData[4 + i]);
		RenderMesh(meshList[GEO_TREE_TRUNK], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, treeArrangementData[1 + i], 0);
		modelStack.Scale(3 + treeArrangementData[4 + i], 10 + treeArrangementData[3 + i], 3 + treeArrangementData[4 + i]);
		RenderMesh(meshList[GEO_TREE_LEAVES], true);
		modelStack.PopMatrix();

		modelStack.PopMatrix();
	}
}

void Assignment2::RenderHead()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 5.1f, 0);

	modelStack.PushMatrix();
	modelStack.Rotate(-135, 0, 1, 0);
	RenderMesh(meshList[GEO_HEAD_CORE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -1.5f, 2.25f);
	modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(meshList[GEO_HEAD_NOSE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(110, 1, 0, 0);
	RenderMesh(meshList[GEO_HELMET_CORE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(-45, 0, 1, 0);
	RenderMesh(meshList[GEO_HELMET_FOREHEAD], true);
	modelStack.PopMatrix();

	for (int mirror = 1; mirror >= -1; mirror -= 2){
		modelStack.PushMatrix();
		modelStack.Translate(mirror*-3.35f, 0, 0);
		modelStack.Rotate(mirror*-90, 0, 0, 1);
		RenderMesh(meshList[GEO_HELMET_EARS], true);
		RenderMesh(meshList[GEO_HELMET_EARS2], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(mirror*-1.f, -0.3f, 2.45f);
		RenderMesh(meshList[GEO_HEAD_EYES1], false);

		modelStack.PushMatrix();
		modelStack.Translate(mirror*0.2f, 0, 0.01f);
		RenderMesh(meshList[GEO_HEAD_EYES2], true);
		modelStack.PopMatrix();

		modelStack.PopMatrix();
	}
	
	modelStack.PopMatrix();
	
}
void Assignment2::RenderBody()
{
	RenderMesh(meshList[GEO_BODY_UPPER], true);

	modelStack.PushMatrix();
	modelStack.Translate(0, -1.75f, 0);
	RenderMesh(meshList[GEO_BODY_LOWER], true);
	modelStack.PopMatrix();
}
void Assignment2::RenderUpperArm(int mirror)
{
	RenderMesh(meshList[GEO_SHOULDER], true);

	modelStack.PushMatrix();
	modelStack.Translate(mirror*(-1.25), 0, 0);
	modelStack.Rotate(mirror*(-90), 0, 0, 1);
	RenderMesh(meshList[GEO_ARM_UPPER], true);
	modelStack.PopMatrix();
}
void Assignment2::RenderLowerArm(int mirror)
{
	RenderMesh(meshList[GEO_ARM_CANNON_CORE], true);

	modelStack.PushMatrix();
	modelStack.Translate(mirror*-1.6f, 0, 0);
	modelStack.Rotate(90, 0, 0, 1);
	RenderMesh(meshList[GEO_ARM_CANNON_TIP], true);
	modelStack.PopMatrix();
}
void Assignment2::RenderUpperLeg(int mirror)
{
	RenderMesh(meshList[GEO_LEG_UPPER], true);

	modelStack.PushMatrix();
	modelStack.Translate(0, -1, 0);
	RenderMesh(meshList[GEO_LEG_JOINT], true);
	modelStack.PopMatrix();
}
void Assignment2::RenderLowerLeg(int mirror)
{
	RenderMesh(meshList[GEO_LEG_LOWER], true);

	modelStack.PushMatrix();
	modelStack.Translate(0, -1.01f, 0.5f);
	modelStack.Rotate(180, 0, 0, 1);
	RenderMesh(meshList[GEO_LEG_FOOT], true);
	modelStack.PopMatrix();
}

void Assignment2::ArrangeTrees(int fromX, int toX, int fromZ, int toZ, int distanceBetweenTrees)
{
	srand(time(NULL));
	for (int x = fromX; x < toX; x += distanceBetweenTrees){
		for (int z = fromZ; z < toZ; z += distanceBetweenTrees){
			float sV = rand()%5;
			float sH = rand()%4;
			treeArrangementData.push_back(x + rand() % distanceBetweenTrees);	// translate X
			treeArrangementData.push_back((sV+6) / 2);							// translate Y
			treeArrangementData.push_back(z + rand() % distanceBetweenTrees);	// translate Z
			treeArrangementData.push_back(sV);									// SCALE Y
			treeArrangementData.push_back(sH);									// SCALE X && Z
		}
	}
}

void Assignment2::AnimateRun(double dt)
{
	// upper legs degree = -60 - 60
	// lower legs degree = -30 - 30
	lowerLegRunValue = 30.f;

	if (upperLegRunning * upperLegDir > 60){
		upperLegDir = -upperLegDir;
		lowerLegDir = -lowerLegDir;
	}
	upperLegRunning += (float)(upperLegDir * 180 * dt);

	if (lowerLegRunning * lowerLegDir < 30.f){
		lowerLegRunning += (float)(lowerLegDir * 180 * dt);
	}
	if (upperArmShooting >= 0.f){
		if (!isShootingAnimation){ // RUN ANIMATION FOR UPPER ARMS
			if (upperArmRunning > upperLegRunning - 3.f && upperArmRunning < upperLegRunning + 3.f){
				upperArmRunning = upperLegRunning;
			}
			else{
				if (upperArmRunning < upperLegRunning)
					upperArmRunning += (float)(200 * dt);
				else if (upperArmRunning > upperLegRunning)
					upperArmRunning -= (float)(200 * dt);
			}
		}
		else{ // ELSE PUT UPPER ARM BACK INTO POSITION
			if (upperArmRunning > 0)
				upperArmRunning -= (float)(180 * dt);
			else if (upperArmRunning < 0)
				upperArmRunning += (float)(180 * dt);

			if (upperArmRunning > -5.f && upperArmRunning < 5.f)
				upperArmRunning = 0.f;
		}
	}
}

void Assignment2::AnimateShoot(double dt)
{
	upperArmRunning = 0.f;
	if (upperArmShooting > -90.f)
		upperArmShooting -= (float)(180 * dt);
	if (cannonShooting < 30.f)
		cannonShooting += (float)(90 * dt);
	if (upperArmShooting <= -90.f && cannonShooting >= 30.f){
		canShoot = true;
	}
}