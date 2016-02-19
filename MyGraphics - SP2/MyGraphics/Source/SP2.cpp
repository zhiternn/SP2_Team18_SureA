#include "SP2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "Camera.h"
#include "Effect_Explosion.h"
#include "ItemBox.h"
#include "Countdown.h"

SP2::SP2()
{
}

SP2::~SP2()
{
}

void SP2::Init()
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
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//orbital-element_ft.tga");
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1));
	meshList[GEO_BACK]->textureID = LoadTGA("Image//orbital-element_bk.tga");
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1));
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//orbital-element_rt.tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1));
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//orbital-element_lf.tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1));
	meshList[GEO_TOP]->textureID = LoadTGA("Image//orbital-element_up.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1));
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//orbital-element_dn.tga");
	
	meshList[GEO_FLOOR] = MeshBuilder::GenerateQuad("floor", Color(0.f, 0.f, 0.f), 4, 4);
	meshList[GEO_FLOOR]->material.kAmbient.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_FLOOR]->textureID = LoadTGA("Image//grass.tga");

	meshList[GEO_TRAPS] = MeshBuilder::GenerateCylinder("traps", Color(1.f, 0.f, 0.f), 1); //door

	meshList[GEO_SLIDEDOOR] = MeshBuilder::GenerateCube("sliding door", Color(1, 0, 0));

	//INTERNAL SKYBOX
	meshList[GEO_INTERNAL_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1));
	meshList[GEO_INTERNAL_FRONT]->textureID = LoadTGA("Image//sides.tga");
	meshList[GEO_INTERNAL_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1));
	meshList[GEO_INTERNAL_BACK]->textureID = LoadTGA("Image//sides.tga");
	meshList[GEO_INTERNAL_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1));
	meshList[GEO_INTERNAL_LEFT]->textureID = LoadTGA("Image//sides.tga");
	meshList[GEO_INTERNAL_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1));
	meshList[GEO_INTERNAL_RIGHT]->textureID = LoadTGA("Image//sides.tga");
	meshList[GEO_INTERNAL_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1));
	meshList[GEO_INTERNAL_TOP]->textureID = LoadTGA("Image//roofnew.tga");
	meshList[GEO_INTERNAL_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1));
	meshList[GEO_INTERNAL_BOTTOM]->textureID = LoadTGA("Image//floor.tga");

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("sphere", Color(1, 1, 1));
	meshList[GEO_HITBOX] = MeshBuilder::GenerateCube("hitbox", Color(1, 0, 0));
	meshList[GEO_HITBOX]->material.kAmbient.Set(0, 0, 0);

	meshList[GEO_PORTAL_BODY] = MeshBuilder::GenerateOBJ("model_air", "OBJ//portal.obj");
	meshList[GEO_PORTAL_BODY]->material.SetToChrome();
	meshList[GEO_PORTAL_BODY]->textureID = LoadTGA("Image//portal_Body.tga");
	meshList[GEO_PORTAL_FRONT] = MeshBuilder::GenerateQuad("portal_front", Color(1, 1, 1));
	meshList[GEO_PORTAL_FRONT]->textureID = LoadTGA("Image//portal_Front.tga");
	meshList[GEO_PORTAL_BACK] = MeshBuilder::GenerateQuad("portal_back", Color(1, 1, 1));
	meshList[GEO_PORTAL_BACK]->textureID = LoadTGA("Image//portal_Back.tga");
	meshList[GEO_EXPLOSION] = MeshBuilder::GenerateQuad("kaBoom", Color(1, 1, 1));
	meshList[GEO_EXPLOSION]->textureID = LoadTGA("Image//explosion.tga");

	meshList[GEO_Testitem1] = MeshBuilder::GenerateOBJ("Obj1", "OBJ//ItemObject1.obj");
	meshList[GEO_Testitem1]->textureID = LoadTGA("Image//walls3.tga");

	meshList[GEO_Testitem2] = MeshBuilder::GenerateOBJ("Obj2", "OBJ//ItemObject2.obj");
	meshList[GEO_Testitem2]->textureID = LoadTGA("Image//walls3.tga");

	meshList[GEO_Testitem3] = MeshBuilder::GenerateOBJ("Obj3", "OBJ//ItemObject3.obj");
	meshList[GEO_Testitem3]->textureID = LoadTGA("Image//walls3.tga");
<<<<<<< 7ac3d4cf3e0c29c50eae7b3a3bb54a67e659e0cd

	meshList[GEO_TestitemExtra] = MeshBuilder::GenerateOBJ("ObjExtra", "OBJ//ObjectExtra.obj");
	meshList[GEO_TestitemExtra]->textureID = LoadTGA("Image//walls3.tga");

	meshList[GEO_ShipButtonStand] = MeshBuilder::GenerateOBJ("ShipButtonStand", "OBJ//ShipButtonStand.obj");
	meshList[GEO_ShipButtonStand]->textureID = LoadTGA("Image//floor.tga");

	meshList[GEO_ShipButton] = MeshBuilder::GenerateOBJ("", "OBJ//ShipButton.obj");
	meshList[GEO_ShipButton]->textureID = LoadTGA("Image//walls3.tga");

	meshList[GEO_ShipButonCover] = MeshBuilder::GenerateOBJ("ShipButonCover", "OBJ//ShipButtonCover.obj");
	meshList[GEO_ShipButonCover]->textureID = LoadTGA("Image//portal_Front.tga");

=======

	meshList[GEO_TestitemExtra] = MeshBuilder::GenerateOBJ("ObjExtra", "OBJ//ObjectExtra.obj");
	meshList[GEO_TestitemExtra]->textureID = LoadTGA("Image//walls3.tga");
>>>>>>> 04a8203400287bdf32e1a92ac2d6732ec927be75

	meshList[GEO_TEST] = MeshBuilder::GenerateQuad("Test", Color(1, 1, 1));
	meshList[GEO_TEST]->textureID = LoadTGA("Image//mazeDesign.tga");

	meshList[GEO_BASECAMP] = MeshBuilder::GenerateOBJ("base camp", "OBJ//BaseBuilding.obj");
	meshList[GEO_BASECAMP]->textureID = LoadTGA("Image//baseUV.tga");

	meshList[GEO_ENEMYSHIP] = MeshBuilder::GenerateOBJ("enemyship", "OBJ//enemyShip.obj");
	meshList[GEO_ENEMYSHIP]->textureID = LoadTGA("Image//enemyTex.tga");

	meshList[GEO_TURRET_BASE] = MeshBuilder::GenerateOBJ("turret", "OBJ//turret_base.obj");
	meshList[GEO_TURRET_BASE]->textureID = LoadTGA("Image//turret.tga");
	meshList[GEO_TURRET_HEAD] = MeshBuilder::GenerateOBJ("turret", "OBJ//turret_head.obj");
	meshList[GEO_TURRET_HEAD]->textureID = LoadTGA("Image//turret.tga");

	meshList[GEO_ALLYSHIP] = MeshBuilder::GenerateOBJ("allyship", "OBJ//allyShip.obj");
	meshList[GEO_ALLYSHIP]->textureID = LoadTGA("Image//allyShip.tga");

	meshList[GEO_UIBAR] = MeshBuilder::GenerateOBJ("Bar", "OBJ//UIBar.obj");
	meshList[GEO_UIBAR]->textureID = LoadTGA("Image//enemyTex.tga");

	meshList[GEO_DOOR] = MeshBuilder::GenerateOBJ("Door", "OBJ//door.obj");
	meshList[GEO_DOOR]->textureID = LoadTGA("Image//door.tga");


	//Initializing transforming matrices
	Application::GetScreenSize(screenX, screenY);
	screenX /= 20;
	screenY /= 20;

	playerState = STATE_FPS;

	ArrangeObjs(65, 65, 30);

	readyToUse = 2.f;
	readyToUse_HITBOX = 2.f;
	readyToInteract = 2.f;

	enableLight = true;
	showHitBox = false;

	buttonCoverBool = false;
	buttonRiseBool = false;
	buttonPressBool = false;
	cbuttonRise = false;

	buttonCover = 0;
	buttonRise = 0;

	animation_rotatePortal = 0.f;
	animation_scalePortal = 0.f;

	player.Init(Vector3(-35, 5, 40), Vector3(0, 0, -1));

	enemy.Init(Vector3(0, 0, -3), 5.f);

	portal.hitbox.SetSize(4, 3, 1);
	portal.hitbox.SetPivot(0, 1.3f, 0);
	portal.SetPosition(0, 0, 48);

	laserTrap.hitbox.SetSize(0.1, 0.1, 5);
	laserTrap.SetPosition(9, 18, 0);
	//laserTrap.hitbox.SetPivot(0, 1.3f, 0);
	
	laserTrap1.hitbox.SetSize(0.1, 0.1, 5);
	laserTrap1.SetPosition(5, 18, 0);

	laserTrap2.hitbox.SetSize(0.1, 0.1, 5);
	laserTrap2.SetPosition(2, 18, 0);
	//front door
	frontDoor.hitbox.SetSize(0.2, 5.5, 3);
	frontDoor.SetPosition(-20.3, 2.8, 37.75);

	frontDoor2.hitbox.SetSize(0.2, 5.5, 3);
	frontDoor2.SetPosition(-20.3, 2.8, 40.75);
	//back door
	backDoor.hitbox.SetSize(0.2, 5.5, 3);
	backDoor.SetPosition(20.9, 2.8, 37.75);

	backDoor2.hitbox.SetSize(0.2, 5.5, 3);
	backDoor2.SetPosition(20.9, 2.8, 40.75);

	turret.hitbox.SetSize(3.f, 4, 3.f);
	turret.hitbox.SetPivot(0, 2.f, 0);
	turret.Init(Vector3(-46.f, 0, -20.f), Vector3(0, 0, 1), 5);

	//BOUNDARIES
	Object* floor = new Object();
	floor->hitbox.SetSize(100, 9.5f, 100);
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

	//Items
	ItemObject* item1 = new ItemObject();
	item1->hitbox.SetSize(2, 2, 2);
	item1->SetPosition(0, 0.5, 0);

	ItemObject* item2 = new ItemObject();
	item2->hitbox.SetSize(2, 2, 2);
	item2->SetPosition(-10, 0.7, 0);

	ItemObject* item3 = new ItemObject();
	item2->hitbox.SetSize(2, 2, 2);
	item3->SetPosition(-5, 0.5, 0);

	//INTERNAL SKYBOX BOUNDARIES
	Object* internalWall_Ground = new Object();
	internalWall_Ground->hitbox.SetSize(10.f, 1, 5);
	internalWall_Ground->SetPosition(8, 17.f, 0);

	trapdoor.hitbox.SetPivot(-2, 0, 0);
	trapdoor.hitbox.SetSize(5.5, 0.2, 5);
	trapdoor.SetPosition(2, 1, 0);

	Object* internalWall_Ground2 = new Object();
	internalWall_Ground2->hitbox.SetSize(10.5f, 1, 15);
	internalWall_Ground2->SetPosition(17.5, 17.f, 0);

	Object* internalWall_Right = new Object();
	internalWall_Right->hitbox.SetSize(15, 5, 1);
	internalWall_Right->SetPosition(5, 20.f, 3.f);

	Object* internalWall_Right2 = new Object();
	internalWall_Right2->hitbox.SetSize(10, 5, 1);
	internalWall_Right2->SetPosition(17.5f, 20.f, 8.f);

	Object* internalWall_Left = new Object();
	internalWall_Left->hitbox.SetSize(15, 5, 1);
	internalWall_Left->SetPosition(5, 20.f, -3.f);

	Object* internalWall_Left2 = new Object();
	internalWall_Left2->hitbox.SetSize(10, 5, 1);
	internalWall_Left2->SetPosition(17.5f, 20.f, -8.f);

	Object* internalWall_Back = new Object();
	internalWall_Back->hitbox.SetSize(1, 5, 5);
	internalWall_Back->SetPosition(-2.5f, 20.f, 0.f);

	Object* internalWall_Back2 = new Object();
	internalWall_Back2->hitbox.SetSize(1, 5, 5);
	internalWall_Back2->SetPosition(12.5f, 20.f, 5.f);

	Object* internalWall_Back3 = new Object();
	internalWall_Back3->hitbox.SetSize(1, 5, 5);
	internalWall_Back3->SetPosition(12.5f, 20.f, -5.f);

	Object* internalWall_Front = new Object();
	internalWall_Front->hitbox.SetSize(1, 5, 15);
	internalWall_Front->SetPosition(22.5f, 20.f, 0.f);

	//Base Camp
	Object* CampWall_Right = new Object();
	CampWall_Right->hitbox.SetSize(42, 10, 1);
	CampWall_Right->SetPosition(0, 5.f, 49.f);

	Object* CampWall_Left = new Object();
	CampWall_Left->hitbox.SetSize(42, 10, 1);
	CampWall_Left->SetPosition(0, 5.f, 29);

	Object* CampWall_Back = new Object();
	CampWall_Back->hitbox.SetSize(1, 5, 8);
	CampWall_Back->SetPosition(21.f, 2.5f, 33.f);

	Object* CampWall_Back2 = new Object();
	CampWall_Back2->hitbox.SetSize(1, 5, 8);
	CampWall_Back2->SetPosition(21.f, 2.5f, 45.5f);

	Object* CampWall_Front = new Object();
	CampWall_Front->hitbox.SetSize(1.5, 5, 8);
	CampWall_Front->SetPosition(-20.5f, 2.5f, 45.5f);

	Object* CampWall_Front2 = new Object();
	CampWall_Front2->hitbox.SetSize(1.5, 5, 8);
	CampWall_Front2->SetPosition(-20.5f, 2.5f, 33.f);

	Object* AllyShip = new Object();
	AllyShip->hitbox.SetSize(3.5, 2, 3.5);
	AllyShip->SetPosition(25.f, 1.f, -25.f);


	GenerateWaypoints(100, 100, 1, 4);
}

void SP2::RenderMesh(Mesh *mesh, bool enableLight)
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

void SP2::Update(double dt)
{
	if (playerState == STATE_FPS){
		player.Update(dt);
	}
	else if (playerState == STATE_INTERACTING_MAZE){
		MazeInteraction(dt);
	}
	else if (playerState == STATE_INTERACTING_TURRET){
		turret.Update(dt);
	}

	TrapsMovement(dt);
	DoorMovement(dt);
	Interval(dt);
	enemy.Update(dt);
	UpdatePortal(dt);
	UpdateDoor(dt);
	ShipButtonAnimation(dt);

	if (Application::IsKeyPressed('E') && readyToInteract >= 2.f){
		readyToInteract = 0.f;

		//PORTAL INTERACTION
		if ((player.position - portal.position).Length() < 2.f){
			player.position.Set(0, 25, 0);
		}
		//TURRET INTERACTION
		if (playerState != STATE_INTERACTING_TURRET && (player.position - turret.position).Length() < 4.f){
			playerState = STATE_INTERACTING_TURRET;
		}
		else if (playerState == STATE_INTERACTING_TURRET){
			playerState = STATE_FPS;
		}

		enemy.GoTo(player.position);
	}
	else if (readyToInteract < 2.f){
		readyToInteract += (float)(10.f * dt);
	}
	for (vector<Projectile*>::iterator it = Projectile::projectileList.begin(); it != Projectile::projectileList.end();){
		if ((*it)->Update(dt)){
			it = Projectile::projectileList.erase(it);
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
	if (Application::IsKeyPressed('F'))
	{
		PressButton();
		for (int i = 0; i < ItemObject::ItemList.size(); ++i){
			ItemObject::ItemList[i]->PickUp(player.hitbox);
		}
	}

	for (int i = 0; i < ItemObject::ItemList.size(); ++i){
		ItemObject::ItemList[i]->PickUpAnimation(dt);
	}

	for (int i = 0; i < ItemObject::ItemList.size(); ++i){
		ItemObject::ItemList[i]->ItemDelay(dt);
	}
	if (Hitbox::CheckItems(player.hitbox, laserTrap.hitbox) || Hitbox::CheckItems(player.hitbox, laserTrap1.hitbox) || Hitbox::CheckItems(player.hitbox, laserTrap2.hitbox))
	{
		player.position.Set(18, 19, 0);
	}


	if (Application::IsKeyPressed(0x31)){
		glEnable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed(0x32)){
		glDisable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed(0x35)){

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
		else if (readyToUse_HITBOX < 2.f){
			readyToUse_HITBOX += (float)(10 * dt);
		}
	}
}

void SP2::Render()
{
	// Clear color & depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Vector3 camPos, camTar, camUp;

	if (playerState == STATE_FPS){
		camPos = player.camera.position;
		camTar = player.camera.target;
		camUp = player.camera.up;
	}
	else if (playerState == STATE_INTERACTING_TURRET){
		camPos = turret.camera.position;
		camTar = turret.camera.target;
		camUp = turret.camera.up;
	}
	Vector3 camView = (camTar - camPos).Normalized();
	float towardsCameraYaw = (float)((camView.x / abs(camView.x)) * Math::RadianToDegree(acos(camView.Dot(Vector3(0, 0, -1)))));

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

	RenderBaseCamp();

	RenderEnemyShip();

	RenderAllyShip();

	modelStack.PushMatrix();
	modelStack.Translate(
		turret.position.x,
		turret.position.y,
		turret.position.z
		);
	RenderTurret();

	modelStack.PopMatrix();

	RenderTraps();

	RenderSlideDoor();

	RenderPickUpObj();

	RenderShipButton();

	modelStack.PushMatrix();
	modelStack.Translate(15, 17.5, 0);
	RenderInternalSkybox();
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	RenderDoor();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(100, 100, 100);
	RenderMesh(meshList[GEO_FLOOR], true);
	modelStack.PopMatrix();

	for (vector<Projectile*>::iterator it = Projectile::projectileList.begin(); it != Projectile::projectileList.end(); ++it){
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

	// OBJs Textures with transparency to be rendered Last
	modelStack.PushMatrix();
	modelStack.Translate(
		portal.position.x,
		portal.position.y,
		portal.position.z
		);
	RenderPortal();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(
		enemy.position.x,
		enemy.position.y + Waypoint::sizeV / 2,
		enemy.position.z
		);
	modelStack.Scale(
		Waypoint::sizeH,
		Waypoint::sizeV,
		Waypoint::sizeH
		);
	RenderMesh(meshList[GEO_HITBOX], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderExplosion();
	modelStack.PopMatrix();

	//for (int i = 0; i < Waypoint::waypointList.size(); ++i){
	//	if (Math::RadianToDegree(acos(Waypoint::waypointList[i]->position.Dot(player.view))) < 180.f){
	//		modelStack.PushMatrix();
	//		modelStack.Translate(
	//			Waypoint::waypointList[i]->position.x,
	//			Waypoint::waypointList[i]->position.y,
	//			Waypoint::waypointList[i]->position.z
	//			);
	//		modelStack.Scale(1, 1, 1);
	//		RenderMesh(meshList[GEO_HITBOX], true);
	//		modelStack.PopMatrix();
	//	}
	//}

	// HIT BOXES
	if (showHitBox){

		Vector3 viewy = player.view;
		viewy.y = 0;
		for (std::vector<Waypoint*>::iterator it = Waypoint::waypointList.begin(); it != Waypoint::waypointList.end(); ++it){
			modelStack.PushMatrix();
			modelStack.Translate(
				(*it)->position.x,
				(*it)->position.y,
				(*it)->position.z
				);
			modelStack.Scale(
				Waypoint::sizeH,
				Waypoint::sizeV,
				Waypoint::sizeH
				);
			RenderMesh(meshList[GEO_HITBOX], true);
			modelStack.PopMatrix();
		}

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
		for (std::vector<ItemObject*>::iterator it = ItemObject::ItemList.begin(); it < ItemObject::ItemList.end(); ++it){
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
	if ((player.position - portal.position).Length() < 2.f){
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to Enter Portal", Color(1, 1, 1), 4, -30.f, 25.f);
	}
	RenderTextOnScreen(meshList[GEO_TEXT], "Press 'Q' to Show/Hide Hitboxes", Color(1.f, 1.f, 1.f), 2, -55.f, -35.f);

	RenderTextOnScreen(meshList[GEO_TEXT], "Click on 'LMB' to Shoot", Color(1.f, 1.f, 1.f), 2, -55.f, -33.f);

	RenderTextOnScreen(meshList[GEO_TEXT], "Crouched: " + std::to_string(player.crouch), Color(1.f, 1.f, 1.f), 2, -55.f, -25.f);
	RenderTextOnScreen(meshList[GEO_TEXT], "POSITION Y: " + std::to_string(player.camera.position.y), Color(1.f, 1.f, 1.f), 2, -55.f, -27.f);
	RenderTextOnScreen(meshList[GEO_TEXT], "POSITION X: " + std::to_string(player.camera.position.x), Color(1.f, 1.f, 1.f), 2, -55.f, -31.f);
	RenderTextOnScreen(meshList[GEO_TEXT], "POSITION Z: " + std::to_string(player.camera.position.z), Color(1.f, 1.f, 1.f), 2, -55.f, -29.f);

	RenderTextOnScreen(meshList[GEO_TEXT], "pick Item " + std::to_string(Hitbox::CheckItems(ItemObject::ItemList[0]->hitbox, player.hitbox)), Color(1.f, 1.f, 1.f), 2, -55.f, -39.f);
	RenderTextOnScreen(meshList[GEO_TEXT], "haveItem  " + std::to_string(ItemObject::ItemList[0]->haveItem), Color(1.f, 1.f, 1.f), 2, -55.f, -41.f);
	RenderTextOnScreen(meshList[GEO_TEXT], "ItemBoolInterval  " + std::to_string(ItemObject::ItemList[0]->ItemBoolInterval), Color(1.f, 1.f, 1.f), 2, -55.f, -37.f);

	if (Application::state2D == true){
		modelStack.PushMatrix();
		RenderQuadOnScreen(meshList[GEO_TEST], (1, 1, 1), 100, 100, 1, 1);
		modelStack.PopMatrix();
	}


	//if (player.camera.position.x <= 2 && player.camera.position.x >= -2 && player.camera.position.z >= -2 && player.camera.position.z <= 2)
	//{
	//	RenderTextOnScreen(meshList[GEO_TEXT], "Press 'F' to pick up", Color(1.f, 1.f, 1.f), 2, -55.f, -37.f);
	RenderTextOnScreen(meshList[GEO_TEXT], "pick Item " + std::to_string(Hitbox::CheckItems(ItemObject::ItemList[0]->hitbox, player.hitbox)), Color(1.f, 1.f, 1.f), 2, -55.f, -39.f);
	RenderTextOnScreen(meshList[GEO_TEXT], "haveItem  " + std::to_string(ItemObject::ItemList[0]->haveItem), Color(1.f, 1.f, 1.f), 2, -55.f, -41.f);
	RenderTextOnScreen(meshList[GEO_TEXT], "ItemBoolInterval  " + std::to_string(ItemObject::ItemList[0]->ItemBoolInterval), Color(1.f, 1.f, 1.f), 2, -55.f, -37.f);

	//	
	//}
	if (Application::state2D == true){
		modelStack.PushMatrix();
		RenderQuadOnScreen(meshList[GEO_TEST], (1, 1, 1), 100, 100, 1, 1);
		modelStack.PopMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Time Left " + std::to_string(m_timer.GetTimeLeft()), Color(1.f, 1.f, 1.f), 2, -55.f, -29.f);
	}

	if (m_timer.GetTimeLeft() <= 0 && m_timer.isCountingDown == false && Application::state2D == true){
		Application::state2D = false;
		Application::SetMousePosition(0, 0);
	}



	modelStack.PushMatrix();
	//	RenderQuadOnScreen(meshList[GEO_UIBAR], (1, 1, 1), -player.sprint1 * 40 + 80, 7, -95, 48);
	modelStack.PopMatrix();

}

void SP2::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void SP2::RenderText(Mesh* mesh, std::string text, Color color)
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

void SP2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

void SP2::RenderQuadOnScreen(Mesh* mesh, Color color, float sizeX, float sizeY, float moveX, float moveY)
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

void SP2::RenderSkybox()
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

void SP2::RenderInternalSkybox(){

	modelStack.PushMatrix();
	modelStack.Translate(0, 2.f, 0);
	modelStack.Rotate(0, 1, 0, 0);
	modelStack.Scale(5, 5, 5);

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -1.5);
	RenderMesh(meshList[GEO_INTERNAL_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(1, 0, -1.5f);
	RenderMesh(meshList[GEO_INTERNAL_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1,0,-0.5);
	RenderMesh(meshList[GEO_INTERNAL_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-2, 0, -0.5f);
	RenderMesh(meshList[GEO_INTERNAL_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-3, 0, -0.5f);
	RenderMesh(meshList[GEO_INTERNAL_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	//back
	modelStack.PushMatrix();
	modelStack.Translate(0, 2, 0);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(5, 5, 5);

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -1.5f);
	RenderMesh(meshList[GEO_INTERNAL_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1, 0, -1.5f);
	RenderMesh(meshList[GEO_INTERNAL_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(1, 0, -0.5f);
	RenderMesh(meshList[GEO_INTERNAL_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(2,0,-0.5f);
	RenderMesh(meshList[GEO_INTERNAL_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(3,0,-0.5f);
	RenderMesh(meshList[GEO_INTERNAL_BACK], false);
	modelStack.PopMatrix();

	modelStack.PopMatrix();


	//left
	modelStack.PushMatrix();
	modelStack.Translate(0, 2, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(5, 5, 5);

	modelStack.PushMatrix();
	modelStack.Translate(0.f, 0, -3.5f);
	RenderMesh(meshList[GEO_INTERNAL_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(1.f, 0,-0.5f );
	RenderMesh(meshList[GEO_INTERNAL_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1.f, 0, -0.5f);
	RenderMesh(meshList[GEO_INTERNAL_LEFT], false);
	modelStack.PopMatrix();


	//right
	modelStack.PushMatrix();
	modelStack.Translate(0,0,1.5f);
	RenderMesh(meshList[GEO_INTERNAL_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(1.f, 0, 1.5f);
	RenderMesh(meshList[GEO_INTERNAL_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1.f, 0, 1.5f);
	RenderMesh(meshList[GEO_INTERNAL_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	//top
	modelStack.PushMatrix();
	modelStack.Translate(0, 4.5, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(5, 5, 5);

	modelStack.PushMatrix();
	modelStack.Translate(0, 0.f, 0);
	RenderMesh(meshList[GEO_INTERNAL_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0,1,0);
	RenderMesh(meshList[GEO_INTERNAL_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0,-3,0);
	RenderMesh(meshList[GEO_INTERNAL_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(1,0,0);
	RenderMesh(meshList[GEO_INTERNAL_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1,0,0);
	RenderMesh(meshList[GEO_INTERNAL_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(1,1,0);
	RenderMesh(meshList[GEO_INTERNAL_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1,1,0);
	RenderMesh(meshList[GEO_INTERNAL_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0,-1,0);
	RenderMesh(meshList[GEO_INTERNAL_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0,-2,0);
	RenderMesh(meshList[GEO_INTERNAL_TOP], false);
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	//bottom
	modelStack.PushMatrix();

	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(5, 5, 5);

	modelStack.PushMatrix();
	modelStack.Translate(0,1,0);
	RenderMesh(meshList[GEO_INTERNAL_BOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0,2,0);
	RenderMesh(meshList[GEO_INTERNAL_BOTTOM], false);
	modelStack.PopMatrix();

	//center
	modelStack.PushMatrix();
	modelStack.Translate(0.f,0.f, 0.f);
	RenderMesh(meshList[GEO_INTERNAL_BOTTOM], false);
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
	modelStack.Translate(1, 0.f, 0);
	RenderMesh(meshList[GEO_INTERNAL_BOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(1,-1,0);
	RenderMesh(meshList[GEO_INTERNAL_BOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0,-1,0);
	RenderMesh(meshList[GEO_INTERNAL_BOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1,0,0);
	RenderMesh(meshList[GEO_INTERNAL_BOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1,-1,0);
	RenderMesh(meshList[GEO_INTERNAL_BOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PopMatrix();

}

void SP2::ArrangeObjs(int sizeX, int sizeZ, int distanceBetweenObjs)
{
	int fromX = -sizeX*0.5;
	int toX = sizeX*0.5;
	int fromZ = -sizeZ*0.5;
	int toZ = sizeZ*0.5;

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

void SP2::RenderObjs(Mesh* mesh, bool light)
{
	for (int i = 0; i < objArrangementData.size(); i += 4){
		modelStack.PushMatrix();
		modelStack.Translate(objArrangementData[i + 2], objArrangementData[i + 1] / 2, objArrangementData[i + 3]);
		modelStack.Scale(objArrangementData[i + 0], objArrangementData[i + 1], objArrangementData[i + 0]);
		RenderMesh(mesh, light);
		modelStack.PopMatrix();
	}
}

void SP2::UpdatePortal(double dt)
{
	static int scaleDir = 1;

	animation_rotatePortal += (float)(10.f * dt);

	if (animation_scalePortal * scaleDir > 0.04f)
		scaleDir = -scaleDir;

	animation_scalePortal += (float)(scaleDir * 0.2f * dt);
}

void SP2::RenderPortal()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 0.f, 0);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_PORTAL_BODY], true);

	modelStack.PushMatrix();

	modelStack.Translate(0, 0.35f, 0);
	modelStack.Scale(0.9f, 0.9f, 0.9f);
	modelStack.Rotate(180, 1, 0, 0);

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

void SP2::UpdateDoor(double dt)
{
	if (Application::IsKeyPressed('F')){
		DoorMoveTrue = true;
	}
	if (DoorMoveTrue == true){
		animation_moveDoor += (float)(0.5f * dt);

		if (animation_moveDoor >= 5.2f){
			DoorMoveTrue = false;
			DoorReturn = true;
		}
	}
	if (DoorReturn == true){
		animation_moveDoor -= (float)(0.5f * dt);
		std::cout << animation_moveDoor << std::endl;
		if (animation_moveDoor <= 0){
			DoorReturn = false;
		}
	}
	trapdoor.SetPosition(
		2 - animation_moveDoor,
		17.5,
		0
		);
}

void SP2::RenderDoor(){

	modelStack.PushMatrix();
	modelStack.Translate(
		trapdoor.position.x,
		trapdoor.position.y,
		trapdoor.position.z
		);
	modelStack.Scale(0.43, 0.1, 0.43);
	modelStack.Rotate(90, 0, 0, 1);
	RenderMesh(meshList[GEO_DOOR], false);
	modelStack.PopMatrix();

}

void SP2::RenderExplosion()
{
	for (vector<Effect_Explosion*>::iterator it = Effect_Explosion::explosionList.begin(); it != Effect_Explosion::explosionList.end(); ++it){
		modelStack.PushMatrix();
		modelStack.Translate(
			(*it)->position.x,
			(*it)->position.y,
			(*it)->position.z
			);
		modelStack.Rotate(
			towardsCameraYaw,
			0,
			1,
			0
			);
		modelStack.Scale(
			(*it)->scale,
			(*it)->scale,
			(*it)->scale
			);
		modelStack.Scale(3, 3, 3);
		RenderMesh(meshList[GEO_EXPLOSION], false);
		modelStack.PopMatrix();
	}
}

void SP2::RenderPickUpObj()
{
	for (int i = 0; i < ItemObject::ItemList.size(); ++i){
		if (ItemObject::ItemList[0]->haveItem == false)
		{
			modelStack.PushMatrix();
			modelStack.Translate(0, ItemObject::ItemList[0]->fly, 0);
			modelStack.PushMatrix();
			modelStack.Translate(
				ItemObject::ItemList[0]->position.x,
				ItemObject::ItemList[0]->position.y,
				ItemObject::ItemList[0]->position.z
				);
			modelStack.Scale(ItemObject::ItemList[0]->growing / 150 + 1, ItemObject::ItemList[0]->growing / 150 + 1, ItemObject::ItemList[0]->growing / 150 + 1);
			RenderMesh(meshList[GEO_Testitem1], true);
			modelStack.PopMatrix();
			modelStack.PopMatrix();
		}
		if (ItemObject::ItemList[1]->haveItem == false)
		{
			modelStack.PushMatrix();
			modelStack.Translate(0, ItemObject::ItemList[1]->fly, 0);
			modelStack.PushMatrix();
			modelStack.Translate(
				ItemObject::ItemList[1]->position.x,
				ItemObject::ItemList[1]->position.y,
				ItemObject::ItemList[1]->position.z
				);
			modelStack.Scale(ItemObject::ItemList[1]->growing / 150 + 1, ItemObject::ItemList[1]->growing / 150 + 1, ItemObject::ItemList[1]->growing / 150 + 1);
			RenderMesh(meshList[GEO_Testitem2], true);
			modelStack.PopMatrix();
			modelStack.PopMatrix();
		}
		if (ItemObject::ItemList[2]->haveItem == false)
		{
			modelStack.PushMatrix();
			modelStack.Translate(0, ItemObject::ItemList[2]->fly, 0);
			modelStack.PushMatrix();
			modelStack.Translate(
				ItemObject::ItemList[2]->position.x,
				ItemObject::ItemList[2]->position.y,
				ItemObject::ItemList[2]->position.z
				);
			modelStack.Scale(ItemObject::ItemList[2]->growing / 150 + 1, ItemObject::ItemList[2]->growing / 150 + 1, ItemObject::ItemList[2]->growing / 150 + 1);
			RenderMesh(meshList[GEO_Testitem3], true);
			modelStack.PopMatrix();
			modelStack.PopMatrix();
		}
		if (ItemObject::ItemList[0]->haveItem == true)
		{
			modelStack.PushMatrix();
			modelStack.Translate(player.position.x + player.view.x, player.position.y + player.view.y, player.position.z + player.view.z);
			modelStack.Scale(0.1, 0.1, 0.1);
			modelStack.PushMatrix();
			modelStack.Translate(-player.right.x * 4.3, -player.right.y * 4.3, -player.right.z * 4.3);
			modelStack.PushMatrix();
			modelStack.Rotate(ItemObject::ItemList[0]->rotateitem, 1, 1, 0);
			RenderMesh(meshList[GEO_Testitem1], true);
			modelStack.PopMatrix();
			modelStack.PopMatrix();
			modelStack.PopMatrix();
		}
		if (ItemObject::ItemList[1]->haveItem == true)
		{
			modelStack.PushMatrix();
			modelStack.Translate(player.position.x + player.view.x, player.position.y + player.view.y, player.position.z + player.view.z);
			modelStack.Scale(0.1, 0.1, 0.1);
			modelStack.PushMatrix();
			modelStack.Translate(-player.right.x * 4.3, -player.right.y * 4.3, -player.right.z * 4.3);
			modelStack.PushMatrix();
			modelStack.Rotate(-ItemObject::ItemList[1]->rotateitem, 1, 1, 1);
			RenderMesh(meshList[GEO_Testitem2], true);
			modelStack.PopMatrix();
			modelStack.PopMatrix();
			modelStack.PopMatrix();
		}
		if (ItemObject::ItemList[2]->haveItem == true)
		{
			modelStack.PushMatrix();
			modelStack.Translate(player.position.x + player.view.x, player.position.y + player.view.y, player.position.z + player.view.z);
			modelStack.Scale(0.1, 0.1, 0.1);
			modelStack.PushMatrix();
			modelStack.Translate(-player.right.x * 4.3, -player.right.y * 4.3, -player.right.z * 4.3);
			modelStack.PushMatrix();
			modelStack.Rotate(-ItemObject::ItemList[2]->rotateitem, 0, 1, 0);
			RenderMesh(meshList[GEO_Testitem3], true);
			modelStack.PopMatrix();
			modelStack.PopMatrix();
			modelStack.PopMatrix();
		}
		if (ItemObject::ItemList[0]->haveItem == true && ItemObject::ItemList[1]->haveItem == true && ItemObject::ItemList[2]->haveItem == true)
		{
			modelStack.PushMatrix();
			modelStack.Translate(player.position.x + player.view.x, player.position.y + player.view.y, player.position.z + player.view.z);
			modelStack.Scale(0.1, 0.1, 0.1);
			modelStack.PushMatrix();
			modelStack.Translate(-player.right.x * 4.3, -player.right.y * 4.3, -player.right.z * 4.3);
			modelStack.PushMatrix();
			modelStack.Rotate(ItemObject::ItemList[1]->rotateitem, 0, 1, 0);
			RenderMesh(meshList[GEO_TestitemExtra], true);
			modelStack.PopMatrix();
			modelStack.PopMatrix();
			modelStack.PopMatrix();
		}
	}
}

void SP2::Interval(double dt)
{
	//if (intervalBool == true)
	//{
	//	interval += (float)(50 * dt);
	//}

	//if (interval > 50)
	//{
	//	intervalBool = false;
	//}
}

void SP2::MazeInteraction(double dt){
	bool stateChanged = false;
	if (Application::IsKeyPressed('O')){
		Application::state2D = true;
		stateChanged = true;
		m_timer.StartCountdown(15);
	}
	else if (Application::IsKeyPressed('P')){
		Application::state2D = false;
		stateChanged = true;
	}
	if (stateChanged && Application::state2D){
		Application::SetMousePosition(500, 950);
	}
	else{}

	if (Application::state2D == false){
		player.Update(dt);
		//std::cout << "testies" << std::endl;

	}
	else{
		double mouseX, mouseY;
		Application::GetMouseMovement(mouseX, mouseY);
		//std::cout << mouseX << "-----------|" << mouseY << std::endl;
		if (mouseX > 45 && mouseX<483 && mouseY >-461 && mouseY < -350){
			//std::cout << "test" << std::endl;
		}
		else if (mouseX>42 && mouseX< 149&& mouseY<-25 && mouseY>-351){
			//std::cout << "test2" << std::endl;
		}
		else if (mouseX > -190 && mouseX < 135 && mouseY>-95 && mouseY<-25){
			//std::cout << "test3" << std::endl;
		}
		else if (mouseX > -190 && mouseX <-159 && mouseY>-95 && mouseY < 320){
			//std::cout << "test4" << std::endl;
		}
		else if (mouseX > -500 && mouseX < -160 && mouseY < 320 && mouseY>291){
			//std::cout << "test5" << std::endl;
		}
		else if (mouseX > -500 && mouseX < -482 && mouseY < 498 && mouseY >290){
			//std::cout << "test6" << std::endl;
		}
		else{
			Application::state2D = false;
			Application::SetMousePosition(0,0);
			//std::cout << "die" << std::endl;
		}

	}
}

void SP2::RenderSlideDoor()
{
	//front door
	modelStack.PushMatrix();
	modelStack.Translate(
		frontDoor.position.x, 
		frontDoor.position.y, 
		frontDoor.position.z);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(3, 5.5, 0.2);
	RenderMesh(meshList[GEO_SLIDEDOOR], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(
		frontDoor2.position.x,
		frontDoor2.position.y,
		frontDoor2.position.z
		);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(3, 5.5, 0.2);
	RenderMesh(meshList[GEO_SLIDEDOOR], true);
	modelStack.PopMatrix();
	//back door
	modelStack.PushMatrix();
	modelStack.Translate(
		backDoor.position.x,
		backDoor.position.y,
		backDoor.position.z
		);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(3, 5.5, 0.2);
	RenderMesh(meshList[GEO_SLIDEDOOR], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(
		backDoor2.position.x,
		backDoor2.position.y,
		backDoor2.position.z
		);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(3, 5.5, 0.2);
	RenderMesh(meshList[GEO_SLIDEDOOR], true);
	modelStack.PopMatrix();

	
}

void SP2::DoorMovement(double dt)
{
	//front door
	if (player.position.x <= -21 && player.position.x >= -28 && player.position.z <= 42 && player.position.z >= 36 || player.position.x <= -12 && player.position.x >= -19 && player.position.z <= 42 && player.position.z >= 36)
	{
		if (DoorMove < 2.2)
		{
			Door = true;
		}
		doorChk = true;
		front = true;
		timer = 0;
	}
	
	//back door
	if (player.position.x <= 28 && player.position.x >= 21 && player.position.z <= 42 && player.position.z >= 36 || player.position.x <= 19 && player.position.x >= 12 && player.position.z <= 42 && player.position.z >= 36)
	{
		if (DoorMove2 < 2.2)
		{
			Door2 = true;
		}
		doorChk = true;
		back = true;
		timer = 0;
	}

	//door
	if (timer > 3)
	{
		timerBool = true;
		doorChk = false;
		timer = 0;
	}

	if (Door == true)
	{
		DoorMove += (float)(2 * dt);
		frontDoor.SetPosition(-20.3, 2.8, 37.75 - DoorMove);
		frontDoor2.SetPosition(-20.3, 2.8, 40.75 + DoorMove);
		if (DoorMove > 2.2)
		{
			Door = false;
		}

	}
	if (Door2 == true)
	{
		DoorMove2 += (float)(2 * dt);
		backDoor.SetPosition(20.9, 2.8, 37.75 - DoorMove2);
		backDoor2.SetPosition(20.9, 2.8, 40.75 + DoorMove2);
		if (DoorMove2 > 2.2)
		{
			Door2 = false;
		}

	}
	if (doorChk == true)
	{
		timer += (float)(1 * dt);
	}

	if (timerBool == true && front == true)
	{
		DoorMove -= (float)(2 * dt);
		frontDoor.SetPosition(-20.3, 2.8, 37.75 - DoorMove);
		frontDoor2.SetPosition(-20.3, 2.8, 40.75 + DoorMove);
		if (DoorMove < -0.2)
		{
			timerBool = false;
			Door = false;
			front = false;
		}
	}
	if (timerBool == true && back == true)
	{
		DoorMove2 -= (float)(2 * dt);
		backDoor.SetPosition(20.9, 2.8, 37.75 - DoorMove2);
		backDoor2.SetPosition(20.9, 2.8, 40.75 + DoorMove2);
		if (DoorMove2 < -0.2)
		{
			timerBool = false;
			Door2 = false;
			back = false;
		}
	}
}

void SP2::RenderTraps()
{
	//traps
	modelStack.PushMatrix();
	//modelStack.Translate(9, 18, 0);
	modelStack.Translate(
		laserTrap.position.x,
		laserTrap.position.y,
		laserTrap.position.z
		);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(0.1, 4.9, 0.1);
	RenderMesh(meshList[GEO_TRAPS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//modelStack.Translate(5, 18, 0);
	modelStack.Translate(
		laserTrap1.position.x,
		laserTrap1.position.y + 3,
		laserTrap1.position.z
		);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(0.1, 4.9, 0.1);
	RenderMesh(meshList[GEO_TRAPS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//modelStack.Translate(5, 19.75, 0);
	modelStack.Translate(
		laserTrap2.position.x,
		laserTrap2.position.y,
		laserTrap2.position.z
		);
	modelStack.Scale(0.1, 4.5, 0.1);
	RenderMesh(meshList[GEO_TRAPS], true);
	modelStack.PopMatrix();
}

void SP2::TrapsMovement(double dt)
{
	if (forth == true)
	{
		trapMove += (float)(2 * dt);
		laserTrap.SetPosition(9 - trapMove, 18, 0);
		//laserTrap1.SetPosition(10 - trapMove * 0.5, 21, 0);
		laserTrap2.SetPosition(12 - trapMove * 1.5, 19.75, 1);
		if (trapMove > 5)
		{
			forth = false;
			backN = true;
		}
	}
	if (backN == true)
	{
		trapMove -= (float)(2 * dt);
		laserTrap.SetPosition(9 - trapMove, 18, 0);
		//laserTrap1.SetPosition(10 - trapMove * 0.5, 21, 0);
		laserTrap2.SetPosition(12 - trapMove * 1.5, 19.75, 1);
		if (trapMove < 0)
		{
			forth = true;
			backN = false;
		}
	}
}

void SP2::RenderAllyShip()
{
	modelStack.PushMatrix();
	modelStack.Translate(25, 0, -25);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_ALLYSHIP], true);
	modelStack.PopMatrix();
}

void SP2::RenderEnemyShip()
{
	modelStack.PushMatrix();
	modelStack.Translate(20, 20, 35);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_ENEMYSHIP], true);
	modelStack.PopMatrix();
}

void SP2::RenderBaseCamp()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 40);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_BASECAMP], true);
	modelStack.PopMatrix();
}

void SP2::RenderTurret()
{
	modelStack.PushMatrix();
	modelStack.Rotate(turret.GetYaw(), 0, 1, 0);
	RenderMesh(meshList[GEO_TURRET_BASE], true);

	modelStack.PushMatrix();
	modelStack.Translate(0, 2.995f, 0);
	modelStack.Rotate(
		turret.GetPitch(),
		-1,
		0,
		0);
	RenderMesh(meshList[GEO_TURRET_HEAD], true);


	modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void SP2::RenderShipButton()
{
	modelStack.PushMatrix();
	modelStack.Translate(-40, 0, 40);//Edit this to move to your spaceship later.
		modelStack.PushMatrix();
		modelStack.Translate(0, 0, 0);
		modelStack.Scale(0.35, 0.35, 0.35);
		RenderMesh(meshList[GEO_ShipButtonStand], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, buttonRise/6 + 0.65, 0);
		modelStack.Scale(0.35, 0.35, 0.35);
		RenderMesh(meshList[GEO_ShipButton], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 0.93, -0.08);
		modelStack.Rotate(-buttonCover, 1, 0, 0);
		modelStack.Scale(0.35, 0.35, 0.35);
		RenderMesh(meshList[GEO_ShipButonCover], true);
		modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void SP2::PressButton()
{
	buttonCoverBool = true;
	if (cbuttonRise == true)
	{
		buttonPressBool = true;
	}
}

void SP2::ShipButtonAnimation(double dt)
{
	if (buttonCoverBool == true && buttonCover < 90)
	{
		buttonCover += (float(50 * dt));
	}
	if (buttonCover > 90)
	{
		buttonCoverBool = false;
		buttonRiseBool = true;
	}
	if (buttonRiseBool == true && cbuttonRise == false)
	{
		buttonRise += (float(1 * dt));
	}
	if (buttonRise > 1)
	{
		buttonRiseBool = false;
		cbuttonRise = true;
	}
	if (cbuttonRise == true && buttonPressBool == true)
	{
		buttonRise -= (float(1 * dt));
	}
	if (buttonRise < 0)
	{
		buttonPressBool = false;
	}
}
