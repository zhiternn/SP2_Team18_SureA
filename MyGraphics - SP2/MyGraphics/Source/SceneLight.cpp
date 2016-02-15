#include "SceneLight.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"


SceneLight::SceneLight()
{
}

SceneLight::~SceneLight()
{
}

void SceneLight::Init()
{
	// Load vertex and fragment shaders
	m_programID = LoadShaders(
		"Shader//Shading.vertexshader",
		"Shader//Shading.fragmentshader"
		);
	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID,
		"MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID,
		"MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID,
		"MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID,
		"material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID,
		"material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID,
		"material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID,
		"material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID,
		"lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID,
		"lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID,
		"lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID,
		"lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID,
		"lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID,
		"lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID,
		"lightEnabled");
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

	camera.Init(Vector3(0, 10, 20), Vector3(0, 0, 0), Vector3(0, 1, 0));

	//MESH GENERATORS
	meshList[GEO_AXES] =		MeshBuilder::GenerateAxes("axis", 1000, 1000, 1000);
	meshList[GEO_RING] =		MeshBuilder::GenerateRing("ellipse", 1, 1, 0.5f, 0.3f);
	meshList[GEO_TORUS] =		MeshBuilder::GenerateTorus("torus", 2, 1, 1, 1, 1, Color(0, 0, 0.5f));
	meshList[GEO_CUBE] =		MeshBuilder::GenerateCube("cube", 2, 2, 2, Color(0.5f, 0, 0.5f));
	meshList[GEO_HEMISPHERE] =	MeshBuilder::GenerateHemisphere("hemi", 2, 2, 2, Color(0.5f, 0, 0.5f));

	meshList[GEO_BALL1] = MeshBuilder::GenerateSphere("sphere", 3, 3, 3, Color(0.22f, 0.45f, 0.72f));
	meshList[GEO_BALL1]->material.kAmbient.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BALL1]->material.kDiffuse.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BALL1]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BALL1]->material.kShininess = 1.f;

	meshList[GEO_BALL2] = MeshBuilder::GenerateSphere("sphere", 3, 3, 3, Color(0.22f, 0.45f, 0.72f));
	meshList[GEO_BALL2]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BALL2]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BALL2]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BALL2]->material.kShininess = 1.f;

	meshList[GEO_BALL3] = MeshBuilder::GenerateSphere("sphere", 3, 3, 3, Color(0.22f, 0.45f, 0.72f));
	meshList[GEO_BALL3]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BALL3]->material.kDiffuse.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BALL3]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BALL3]->material.kShininess = 1.f;

	meshList[GEO_BALL4] = MeshBuilder::GenerateSphere("sphere", 3, 3, 3, Color(0.22f, 0.45f, 0.72f));
	meshList[GEO_BALL4]->material.kAmbient.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BALL4]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BALL4]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BALL4]->material.kShininess = 1.f;

	meshList[GEO_BALL5] = MeshBuilder::GenerateSphere("sphere", 3, 3, 3, Color(0.22f, 0.45f, 0.72f));
	meshList[GEO_BALL5]->material.kAmbient.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BALL5]->material.kDiffuse.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BALL5]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BALL5]->material.kShininess = 1.f;

	meshList[GEO_BALL6] = MeshBuilder::GenerateSphere("sphere", 3, 3, 3, Color(0.22f, 0.45f, 0.72f));
	meshList[GEO_BALL6]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BALL6]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BALL6]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BALL6]->material.kShininess = 1.f;

	meshList[GEO_BALL7] = MeshBuilder::GenerateSphere("sphere", 3, 3, 3, Color(0.22f, 0.45f, 0.72f));
	meshList[GEO_BALL7]->material.kAmbient.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BALL7]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BALL7]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BALL7]->material.kShininess = 1.f;

	meshList[GEO_BALL8] = MeshBuilder::GenerateSphere("sphere", 3, 3, 3, Color(0.22f, 0.45f, 0.72f));
	meshList[GEO_BALL8]->material.kAmbient.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_BALL8]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_BALL8]->material.kSpecular.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_BALL8]->material.kShininess = 1.f;

	meshList[GEO_BALL9] = MeshBuilder::GenerateSphere("sphere", 3, 3, 3, Color(0.22f, 0.45f, 0.72f));
	meshList[GEO_BALL9]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BALL9]->material.kDiffuse.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BALL9]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BALL9]->material.kShininess = 1.f;

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("sphere", 0.5f, 0.5f, 0.5f, Color(1, 1, 1));
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("floor", 1000, 1000, Color(0.3f, 0.3f, 0.3f));

	//setting up light object
	light[0].position.Set(0, 20, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	//pass uniform parameters ( MUST BE AFTER glUseProgram() )
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);

	//Initializing transforming matrices
	readyToUse = 2.f;
}

void SceneLight::RenderMesh(Mesh *mesh, bool enableLight)
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
	mesh->Render();
}

void SceneLight::Update(double dt)
{
	camera.Update(dt);
	if (Application::IsKeyPressed(0x31)){
		glEnable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed(0x32)){
		glDisable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed(0x33)){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (Application::IsKeyPressed(0x34)){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (Application::IsKeyPressed('I'))
		light[0].position.z -= (float)(10.f * dt);
	if (Application::IsKeyPressed('K'))
		light[0].position.z += (float)(10.f * dt);
	if (Application::IsKeyPressed('J'))
		light[0].position.x -= (float)(10.f * dt);
	if (Application::IsKeyPressed('L'))
		light[0].position.x += (float)(10.f * dt);
	if (Application::IsKeyPressed('U'))
		light[0].position.y -= (float)(10.f * dt);
	if (Application::IsKeyPressed('O'))
		light[0].position.y += (float)(10.f * dt);

	if (Application::IsKeyPressed(VK_SPACE) && readyToUse >= 2.f){
		readyToUse = 0.f;
		if (enableLight){
			enableLight = false;
		}
		else{
			enableLight = true;
		}
	}
	else{
		readyToUse += (float)(10 * dt);
	}
}

void SceneLight::Render()
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
	Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);

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
	modelStack.Translate(camera.target.x, camera.target.y, camera.target.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(-90, 1, 0, 0);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-6, 3, -6);
	RenderMesh(meshList[GEO_BALL1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 3, -6);
	RenderMesh(meshList[GEO_BALL2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(6, 3, -6);
	RenderMesh(meshList[GEO_BALL3], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-6, 3, 0);
	RenderMesh(meshList[GEO_BALL4], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 3, 0);
	RenderMesh(meshList[GEO_BALL5], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(6, 3, 0);
	RenderMesh(meshList[GEO_BALL6], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-6, 3, 6);
	RenderMesh(meshList[GEO_BALL7], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 3, 6);
	RenderMesh(meshList[GEO_BALL8], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(6, 3, 6);
	RenderMesh(meshList[GEO_BALL9], true);
	modelStack.PopMatrix();


}

void SceneLight::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}