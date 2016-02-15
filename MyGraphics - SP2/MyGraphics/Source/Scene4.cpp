#include "Scene4.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Application.h"
#include "MeshBuilder.h"


Scene4::Scene4()
{
}

Scene4::~Scene4()
{
}

void Scene4::Init()
{
	// Load vertex and fragment shaders
	m_programID = LoadShaders(
		"Shader//TransformVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader");
	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID,
		"MVP");
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

	camera.Init(Vector3(4, 3, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));

	//MESH GENERATORS
	meshList[GEO_AXES] =		MeshBuilder::GenerateAxes("axis", 1000, 1000, 1000);
	meshList[GEO_CUBE] =		MeshBuilder::GenerateCube("cube", 1, 1, 1, Color(1, 0, 0));
	meshList[GEO_QUAD] =		MeshBuilder::GenerateQuad("quad", 1, 1, Color(1, 0, 0));
	meshList[GEO_ELLIPSE] =		MeshBuilder::GenerateEllipse("ellipse", 1, 1, Color(1, 0, 0), 36);
	meshList[GEO_RING] =		MeshBuilder::GenerateRing("ellipse", 1, 1, 0.5f, 0.3f);
	meshList[GEO_SPHERE] =		MeshBuilder::GenerateSphere("sphere", 1, 1, 1, Color(1, 0, 0));
	meshList[GEO_HEMISPHERE] =	MeshBuilder::GenerateHemisphere("hemisphere", 1, 1, 1, Color(1, 0, 0));
	meshList[GEO_TORUS] =		MeshBuilder::GenerateTorus("torus", 2.5f, 0.5f, 1, 1, 1, Color(1, 0, 0));
	meshList[GEO_PLANET1] =		MeshBuilder::GenerateSphere("sphere", 1, 1, 1, Color(1, 0, 1));
	meshList[GEO_MOON1] =		MeshBuilder::GenerateSphere("sphere", 1, 1, 1, Color(1, 1, 1));
	meshList[GEO_SUN] =			MeshBuilder::GenerateSphere("sphere", 10, 10, 10, Color(1, 1, 0));
	meshList[GEO_PLANET2] =		MeshBuilder::GenerateSphere("sphere", 1.5f, 1.5f, 1.5f, Color(1, 1, 1));
	meshList[GEO_MOON2] =		MeshBuilder::GenerateSphere("sphere", 2, 2, 2, Color(1, 0, 0));
	meshList[GEO_MOON3] =		MeshBuilder::GenerateSphere("sphere", 2, 2, 2, Color(0, 1, 0));
	meshList[GEO_MOON4] =		MeshBuilder::GenerateSphere("sphere", 2, 2, 2, Color(0, 0, 1));

	//Initializing transforming matrices
	rotateAngle = 30.0f;
	translateX = 10.0f;
	scaleAll = 10.0f;
	planet1RevAngle = 0;
	planet1RotAngle = 0;
	moon1RotAngle = 0;
}

void Scene4::Update(double dt)
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

	if (Application::IsKeyPressed(VK_SPACE)){
		rotateAngle = 0;
	}
	else{
		rotateAngle += (float)(60 * dt);
	}
	planet1RevAngle += (float)(50 * dt);
	planet1RotAngle += (float)(50 * dt);
	moon1RotAngle += (float)(50 * dt);
}

void Scene4::Render()
{
	// Clear color & depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x,	camera.position.y,	camera.position.z,
		camera.target.x,	camera.target.y,	camera.target.z,
		camera.up.x,		camera.up.y,		camera.up.z
		);
	modelStack.LoadIdentity();

	modelStack.PushMatrix();
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_AXES]->Render();
	modelStack.PopMatrix();



	modelStack.PushMatrix();// FIRST LEVEL - SUN
	modelStack.Rotate(planet1RevAngle, 0, 1, 1);

	modelStack.PushMatrix();
	modelStack.Rotate(0.5*moon1RotAngle, 1, 0, 0);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_SUN]->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();// LEVEL2 - PLANET1
	modelStack.Rotate(planet1RotAngle, 0, 1, 0);
	modelStack.Translate(25, 0, 0);

	modelStack.PushMatrix();
	modelStack.Scale(5, 5, 5);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_PLANET1]->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(-3*moon1RotAngle, 0, 1, 0);
	modelStack.Scale(15, 15, 15);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_RING]->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();// LEVEL 3 - MOON1
	modelStack.Translate(5, 0, 0);

	modelStack.PushMatrix();
	modelStack.Rotate(moon1RotAngle, 1, 0, 0);
	modelStack.Translate(0, 10, 0);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_MOON1]->Render();
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PushMatrix();// LEVEL2 - PLANET2
	modelStack.Rotate(planet1RotAngle, 1, 0, 1);
	modelStack.Translate(0, 40, 0);

	modelStack.PushMatrix();
	modelStack.Scale(5, 5, 5);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_PLANET2]->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();// LEVEL3 - PLANET2's MOON
	modelStack.Rotate(moon1RotAngle*3, 0, 0, 1);

	modelStack.PushMatrix();
	modelStack.Translate(8, 8, 0);
	modelStack.Scale(1, 1, 1);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_MOON2]->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-8, 0, 8);
	modelStack.Scale(1, 1, 1);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_MOON3]->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(8, 0, -8);
	modelStack.Scale(1, 1, 1);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_MOON4]->Render();
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void Scene4::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}