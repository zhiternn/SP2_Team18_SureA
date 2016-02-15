#include "Assignment3.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "Camera.h"
#include "Effect_Explosion.h"

Assignment3::Assignment3()
{
}

Assignment3::~Assignment3()
{
}

void Assignment3::Init()
{

	// Load vertex and fragment shaders
	m_programID = LoadShaders(
		"Shader//Texture.vertexshader", 
		"Shader//Text.fragmentshader"
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
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");


	// Use our shader
	glUseProgram(m_programID);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Enable culling
	glEnable(GL_CULL_FACE);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	projectionStack.LoadMatrix(projection);

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);


	glUniform1i(m_parameters[U_NUMLIGHTS], 2);
	//setting up light object
	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(100.f, 60.f, -100.f);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1.5f;
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

	light[1].type = Light::LIGHT_SPOT;
	light[1].position.Set(0, 5, 0);
	light[1].color.Set(1, 1, 1);
	light[1].power = 0.f;
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

	//MESH GENERATORS
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//ExportedFont1.tga");
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("axis", 1000, 1000, 1000);

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1));
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//blood-valley_ft.tga");
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1));
	meshList[GEO_BACK]->textureID = LoadTGA("Image//blood-valley_bk.tga");
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1));
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//blood-valley_rt.tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1));
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//blood-valley_lf.tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1));
	meshList[GEO_TOP]->textureID = LoadTGA("Image//blood-valley_up.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1));
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//blood-valley_dn.tga");

	meshList[GEO_FLOOR] = MeshBuilder::GenerateQuad("floor", Color(0.f, 0.f, 0.f), 50);
	meshList[GEO_FLOOR]->material.kAmbient.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_FLOOR]->textureID = LoadTGA("Image//mars_floor.tga");

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("sphere", Color(1, 1, 1));
	meshList[GEO_HITBOX] = MeshBuilder::GenerateCube("hitbox", Color(1, 0, 0));

	meshList[GEO_VEHICLE_SPACE_AIR] = MeshBuilder::GenerateOBJ("model_air", "OBJ//vehicle_space_air.obj");
	meshList[GEO_VEHICLE_SPACE_AIR]->textureID = LoadTGA("Image//vehicle_space_air_UV.tga");
	meshList[GEO_VEHICLE_SPACE_AIR2] = MeshBuilder::GenerateOBJ("model_air", "OBJ//vehicle_space_air2.obj");
	meshList[GEO_VEHICLE_SPACE_AIR2]->textureID = LoadTGA("Image//vehicle_space_air2_UV.tga");
	meshList[GEO_BOUNDARY] = MeshBuilder::GenerateOBJ("boundary", "OBJ//boundary.obj");
	meshList[GEO_BOUNDARY]->textureID = LoadTGA("Image//mars_floor.tga");
	meshList[GEO_PORTAL_BODY] = MeshBuilder::GenerateOBJ("model_air", "OBJ//portal.obj");
	meshList[GEO_PORTAL_BODY]->material.SetToChrome();
	meshList[GEO_PORTAL_BODY]->textureID = LoadTGA("Image//portal_Body.tga");
	meshList[GEO_PORTAL_FRONT] = MeshBuilder::GenerateQuad("portal_front", Color(1, 1, 1));
	meshList[GEO_PORTAL_FRONT]->textureID = LoadTGA("Image//portal_Front.tga");
	meshList[GEO_PORTAL_BACK] = MeshBuilder::GenerateQuad("portal_back", Color(1, 1, 1));
	meshList[GEO_PORTAL_BACK]->textureID = LoadTGA("Image//portal_Back.tga");
	meshList[GEO_LAMP] = MeshBuilder::GenerateOBJ("lamp", "OBJ//lamp.obj");
	meshList[GEO_LAMP]->textureID = LoadTGA("Image//lamp.tga");
	meshList[GEO_BOX] = MeshBuilder::GenerateOBJ("model_land", "OBJ//Box.obj");
	meshList[GEO_BOX]->material.SetToPlastic();
	meshList[GEO_BOX]->textureID = LoadTGA("Image//Box.tga");
	meshList[GEO_EXPLOSION] = MeshBuilder::GenerateQuad("kaBoom", Color(1, 1, 1));
	meshList[GEO_EXPLOSION]->textureID = LoadTGA("Image//explosion.tga");

	meshList[UI_DUAL_GUNS] = MeshBuilder::GenerateQuad("dual_guns", Color(1, 1, 1));
	meshList[UI_DUAL_GUNS]->textureID = LoadTGA("Image//dual_berettas.tga");

	//Initializing transforming matrices
	Application::GetScreenSize(screenX, screenY);
	screenX /= 20;
	screenY /= 20;

	ArrangeObjs(65, 65, 20);

	readyToUse = 2.f;
	readyToUse_HITBOX = 2.f;
	readyToUse_SHOOT = 2.f;
	readyToInteract = 2.f;
	lampLight = false;
	enableLight = true;
	showHitBox = false;
	controlState = CONTROLLING_PLAYER;
	animation_rotatePortal = 0.f;
	animation_scalePortal = 0.f;

	helicopter.Init(Vector3(-10, 6, -10), Vector3(0, 0, 1));
	player.Init(Vector3(0, 5, 10), Vector3(0, 0, -1));

	portal.hitbox.SetSize(4, 3, 1);
	portal.hitbox.SetPivot(0, 1.3f, 0);
	portal.SetPosition(0, 0, -49);

	lamp.hitbox.SetSize(0.38f, 4.f, 0.38f);
	lamp.hitbox.SetPivot(0, 2.f, 0);
	lamp.SetPosition(10, 0, 0);
	light[1].position.Set(
		lamp.position.x,
		lamp.position.y + 5,
		lamp.position.z
		);

	bigShip.hitbox.SetSize(25, 5, 25);
	bigShip.hitbox.SetPivot(0, 0, -1);
	bigShip.SetPosition(0, 40, 0);
	

	//BOUNDARIES
	Object* floor = new Object();
	floor->hitbox.SetSize(100, 10, 100);
	floor->SetPosition(0, -5.f, 0);

	Object* frontWall = new Object();
	frontWall->hitbox.SetSize(100, 100, 10);
	frontWall->SetPosition(0, 50.f, -55.f);

	Object* backWall = new Object();
	backWall->hitbox.SetSize(100, 100, 10);
	backWall->SetPosition(0, 50.f, 55.f);

	Object* leftWall = new Object();
	leftWall->hitbox.SetSize(10, 100, 100);
	leftWall->SetPosition(-55.f, 50.f, 0);

	Object* rightWall = new Object();
	rightWall->hitbox.SetSize(10, 100, 100);
	rightWall->SetPosition(55.f, 50.f, 0);
}

void Assignment3::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();

	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);

	if (enableLight && this->enableLight){
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
	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}

	mesh->Render();


	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Assignment3::Update(double dt)
{
	if (controlState == CONTROLLING_PLAYER){
	player.Update(dt);
	}
	helicopter.Update(dt, controlState == CONTROLLING_HELICOPTER);

	UpdatePortal(dt);
	if (Application::IsKeyPressed('E') && readyToInteract >= 2.f){
		readyToInteract = 0.f;
		if ((player.position - helicopter.position).Length() < 2.5f){
			controlState = CONTROLLING_HELICOPTER;
		}
		else if (controlState == CONTROLLING_HELICOPTER){
			player.position = helicopter.position;
			player.position.y += 3.f;
			controlState = CONTROLLING_PLAYER;
		}
		if ((player.position - lamp.position).Length() < 2.f){
			if (light[1].power >= 1.f){
				light[1].power = 0.f;
				lampLight = false;
			}
			else{
				light[1].power = 1.f;
				lampLight = true;
			}
			glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
		}
		if ((player.position - portal.position).Length() < 2.f){
			player.position.Set(0, 50, 0);
		}
	}
	else if (readyToInteract < 2.f){
			readyToInteract += (float)(10.f * dt);
	}
	if (Application::IsKeyPressed('T') && readyToUse_SHOOT >= 2.f){
		readyToUse_SHOOT = 0.f;
		bulletsList.push_back(new Projectile(
			Vector3(player.position.x, player.position.y, player.position.z), 
			Vector3(player.view.x, player.view.y, player.view.z),
			30,
			50,
			5
			));
	}
	else if (readyToUse_SHOOT < 2.f){
		readyToUse_SHOOT += (float)(10.f * dt);
	}
	for (vector<Projectile*>::iterator it = bulletsList.begin(); it != bulletsList.end();){
		if((*it)->Update(dt)){
			it = bulletsList.erase(it);
		}
		else{
			it++;
		}
	}
	for (vector<Effect_Explosion*>::iterator it = Effect_Explosion::explosionList.begin(); it != Effect_Explosion::explosionList.end();){
		if ((*it)->Update(dt)){
			it = Effect_Explosion::explosionList.erase(it);
		}
		else{
			it++;
		}
	}

	if (Application::IsKeyPressed(0x31)){
		glEnable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed(0x32)){
		glDisable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed(0x35)){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (Application::IsKeyPressed(0x34)){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (Application::IsKeyPressed('Q') && readyToUse_HITBOX >= 2.f){
		readyToUse_HITBOX = 0.f;
		if (showHitBox){
			showHitBox = false;
		}
		else{
			showHitBox = true;
		}
	}
	else if(readyToUse_HITBOX < 2.f){
		readyToUse_HITBOX += (float)(10 * dt);
	}
}

void Assignment3::Render()
{
	// Clear color & depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Vector3 camPos, camTar, camUp;
	switch (controlState){
	case CONTROLLING_PLAYER:
		camPos = player.camera.position;
		camTar = player.camera.target;
		camUp = player.camera.up;
		break;
	case CONTROLLING_HELICOPTER:
		camPos = helicopter.camera.position;
		camTar = helicopter.camera.target;
		camUp = helicopter.camera.up;
		break;
	default:
		break;
	}

	viewStack.LoadIdentity();
	viewStack.LookAt(
		camPos.x, camPos.y, camPos.z,
		camTar.x, camTar.y, camTar.z,
		camUp.x, camUp.y, camUp.z
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

	if (light[1].type == Light::LIGHT_DIRECTIONAL){
		Vector3 lightDir(light[1].position.x, light[1].position.y, light[1].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[1].type == Light::LIGHT_SPOT){
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else{
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
	}

	//RENDER OBJECTS
	//RenderMesh(meshList[GEO_AXES], false);

	modelStack.PushMatrix();
	modelStack.Translate(player.position.x, player.position.y, player.position.z);
	RenderSkybox();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_BOUNDARY], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(100, 100, 100);
	RenderMesh(meshList[GEO_FLOOR], true);
	modelStack.PopMatrix();

	for (vector<Projectile*>::iterator it = bulletsList.begin(); it != bulletsList.end(); ++it){
		modelStack.PushMatrix();
		modelStack.Translate(
			(*it)->position.x,
			(*it)->position.y,
			(*it)->position.z
			);
		modelStack.Scale(0.1, 0.1, 0.1);
		RenderMesh(meshList[GEO_LIGHTBALL], false);
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	RenderObjs(meshList[GEO_BOX], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(
		helicopter.position.x,
		helicopter.position.y,
		helicopter.position.z
		);
	modelStack.Rotate(
		helicopter.rotateYaw,
		0,
		1,
		0
		);
	modelStack.Rotate(
		helicopter.rotateRoll,
		helicopter.defaultFront.x,
		helicopter.defaultFront.y,
		helicopter.defaultFront.z
		);
	modelStack.Rotate(
		helicopter.rotatePitch,
		helicopter.defaultRight.x,
		helicopter.defaultRight.y,
		helicopter.defaultRight.z
		);
	modelStack.Scale(0.3f, 0.3f, 0.3f);
	RenderMesh(meshList[GEO_VEHICLE_SPACE_AIR], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(
		bigShip.position.x,
		bigShip.position.y,
		bigShip.position.z
		);
	RenderBigShip();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(
		lamp.position.x,
		lamp.position.y,
		lamp.position.z
		);
	RenderLamp();
	modelStack.PopMatrix();

	// OBJs Textures with transparency to be rendered Last
	modelStack.PushMatrix();
	modelStack.Translate(
		portal.position.x,
		portal.position.y,
		portal.position.z
		);
	RenderPortal();
	modelStack.PopMatrix();

	float yawAngle = (float)(-player.view.x / abs(player.view.x) * Math::RadianToDegree(acos(player.view.Normalized().Dot(Vector3(0, 0, -1)))));
	for (vector<Effect_Explosion*>::iterator it = Effect_Explosion::explosionList.begin(); it != Effect_Explosion::explosionList.end(); ++it){
		modelStack.PushMatrix();
		modelStack.Translate(
			(*it)->position.x,
			(*it)->position.y,
			(*it)->position.z
			);
		modelStack.Rotate(
			yawAngle,
			0,
			1,
			0
			);
		modelStack.Scale(
			(*it)->scale,
			(*it)->scale,
			(*it)->scale
			);
		RenderExplosion();
		modelStack.PopMatrix();
	}
	// HIT BOXES
	if (showHitBox){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		for (std::vector<Object*>::iterator it = Object::objectList.begin(); it < Object::objectList.end(); ++it){
			modelStack.PushMatrix();
			modelStack.Translate(
				(*it)->hitbox.position.x + (*it)->hitbox.pivot.x,
				(*it)->hitbox.position.y + (*it)->hitbox.pivot.y,
				(*it)->hitbox.position.z + (*it)->hitbox.pivot.z
				);
			modelStack.Scale(
				(*it)->hitbox.sizeX,
				(*it)->hitbox.sizeY,
				(*it)->hitbox.sizeZ
				);
			RenderMesh(meshList[GEO_HITBOX], false);
			modelStack.PopMatrix();
		}
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	// UI STUFF HERE
	if ((player.position - helicopter.position).Length() < 2.5f && controlState == CONTROLLING_PLAYER){
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to board/exit", Color(1, 1, 1), 4, -30.f, 25.f);
	}
	if ((player.position - lamp.position).Length() < 2.f && controlState == CONTROLLING_PLAYER){
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' on/off light", Color(1, 1, 1), 4, -30.f, 25.f);
	}
	if ((player.position - portal.position).Length() < 2.f){
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to Enter Portal", Color(1, 1, 1), 4, -30.f, 25.f);
	}
	if (controlState == CONTROLLING_PLAYER){
		RenderQuadOnScreen(meshList[UI_DUAL_GUNS], Color(1, 1, 1), screenX * 2, screenY * 2);
		RenderTextOnScreen(meshList[GEO_TEXT], "+", Color(0, 1, 0), 4);
	}
	RenderTextOnScreen(meshList[GEO_TEXT], "Press 'Q' to Show/Hide Hitboxes", Color(1.f, 1.f, 1.f), 2, -55.f, -35.f);
	RenderTextOnScreen(meshList[GEO_TEXT], "Press 'T' to Shoot", Color(1.f, 1.f, 1.f), 2, -55.f, -33.f);
}

void Assignment3::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void Assignment3::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.5f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void Assignment3::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(-screenX, screenX, -screenY, screenY, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);

	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}

void Assignment3::RenderQuadOnScreen(Mesh* mesh, Color color, float sizeX, float sizeY, float moveX, float moveY)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(-screenX, screenX, -screenY, screenY, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Translate(moveX, moveY, 0);
	modelStack.Scale(sizeX, sizeY, 1);

	RenderMesh(mesh, false);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}

void Assignment3::RenderSkybox()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -499.f);
	modelStack.Rotate(0, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 499.f);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-499.f, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(499.f, 0, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 499.f, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -499.f, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();
}

void Assignment3::ArrangeObjs(int sizeX, int sizeZ, int distanceBetweenObjs)
{
	int fromX	= -sizeX*0.5;
	int toX		= sizeX*0.5;
	int fromZ	= -sizeZ*0.5;
	int toZ		= sizeZ*0.5;

	srand(time(NULL));
	for (int x = fromX; x < toX; x += distanceBetweenObjs){
		for (int z = fromZ; z < toZ; z += distanceBetweenObjs){

			float scaleH = ((rand() % 20) + 10) / 10;
			float scaleV = ((rand() % 20) + 10) / 10;
			float transX = x + rand() % distanceBetweenObjs;
			float transZ = z + rand() % distanceBetweenObjs;

			objArrangementData.push_back(scaleH);	// 0 - scale Horizontal
			objArrangementData.push_back(scaleV);	// 1 - scale Vertical
			objArrangementData.push_back(transX);	// 2 - X translation
			objArrangementData.push_back(transZ);	// 3 - Z translation

			Object* obj = new Object();
			obj->hitbox.SetSize(scaleH, scaleV, scaleH);
			obj->SetPosition(transX, scaleV / 2, transZ);
			obj->SetHealth(15);
		}
	}
}

void Assignment3::RenderObjs(Mesh* mesh, bool light)
{
	for (int i = 0; i < objArrangementData.size(); i += 4){
		modelStack.PushMatrix();
		modelStack.Translate(objArrangementData[i+2], objArrangementData[i+1]/2, objArrangementData[i+3]);
		modelStack.Scale(objArrangementData[i+0], objArrangementData[i+1], objArrangementData[i+0]);
		RenderMesh(mesh, light);
		modelStack.PopMatrix();
	}
}

void Assignment3::UpdatePortal(double dt)
{
	static int scaleDir = 1;
	animation_rotatePortal += (float)(10.f * dt);
	
	if (animation_scalePortal * scaleDir > 0.04f)
		scaleDir = -scaleDir;

	animation_scalePortal += (float)(scaleDir * 0.2f * dt);
}

void Assignment3::RenderPortal()
{
	modelStack.PushMatrix();
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_PORTAL_BODY], true);


	modelStack.PushMatrix();

	modelStack.Translate(0, 0.35f, 0);
	modelStack.Scale(0.9f, 0.9f, 0.9f);

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0.09f);
	modelStack.Rotate(animation_rotatePortal, 0, 0, 1);
	RenderMesh(meshList[GEO_PORTAL_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0.1f);
	modelStack.Rotate(-animation_rotatePortal, 0, 0, 1);
	modelStack.Scale(
		1.04f + animation_scalePortal, 
		1.04f + animation_scalePortal, 
		1.04f + animation_scalePortal);
	RenderMesh(meshList[GEO_PORTAL_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void Assignment3::RenderLamp()
{
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_LAMP], !lampLight);
	modelStack.PopMatrix();
}

void Assignment3::RenderBigShip()
{
	modelStack.PushMatrix();
	modelStack.Scale(30.f, 30.f, 30.f);
	RenderMesh(meshList[GEO_VEHICLE_SPACE_AIR2], true);
	modelStack.PopMatrix();
}

void Assignment3::RenderExplosion()
{
	modelStack.PushMatrix();
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_EXPLOSION], false);
	modelStack.PopMatrix();
}