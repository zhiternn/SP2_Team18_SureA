#include "Scene5.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Application.h"
#include "MeshBuilder.h"


Scene5::Scene5()
{
}

Scene5::~Scene5()
{
}

void Scene5::Init()
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

	camera.Init(Vector3(40, 30, 30), Vector3(0, 0, 0), Vector3(0, 1, 0));

	//MESH GENERATORS
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("axis", 1000, 1000, 1000);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", 1, 1, 1, Color(1, 0, 0));
	meshList[GEO_CUBE2] = MeshBuilder::GenerateCube("cube", 1, 1, 1, Color(0, 0, 1));
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", 1, 1, Color(1, 1, 1));
	meshList[GEO_ELLIPSE] = MeshBuilder::GenerateEllipse("ellipse", 1, 1, Color(1, 0, 0), 36);
	meshList[GEO_RING] = MeshBuilder::GenerateRing("ellipse", 1, 1, 0.5f, 0.3f);
	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", 1, 1, 1, Color(1, 0, 0));
	meshList[GEO_HEMISPHERE] = MeshBuilder::GenerateHemisphere("hemisphere", 1, 1, 1, Color(1, 0, 0));
	meshList[GEO_TORUS] = MeshBuilder::GenerateTorus("torus", 2.5f, 0.5f, 1, 1, 1, Color(1, 0, 0));


	//Initializing transforming matrices
	rotateAngle = 30.0f;
	translateX = 10.0f;
	scaleAll = 10.0f;
	planet1RevAngle = 0;
	planet1RotAngle = 0;
	moon1RotAngle = 0;
}

void Scene5::Update(double dt)
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
		static int rotateDir = 1;
		if (rotateAngle * rotateDir > 30){
			rotateDir = -rotateDir;
		}
		rotateAngle += (float)(rotateDir * 60 * dt);
	}
}

void Scene5::Render()
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

	modelStack.PushMatrix();
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_AXES]->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(100, 100, 100);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_QUAD]->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	RenderRobot();
	modelStack.PopMatrix();

}

void Scene5::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void Scene5::RenderBody(){
	modelStack.PushMatrix();
	modelStack.Translate(0, -7.5, 0);
	modelStack.Scale(30, 25, 10);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_CUBE]->Render();
	modelStack.PopMatrix();
}

void Scene5::RenderLimb(){
	modelStack.PushMatrix();
	modelStack.Translate(0, -5, 0);
	modelStack.Scale(10, 20, 10);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_CUBE2]->Render();
	modelStack.PopMatrix();
}

void Scene5::RenderHead(){
	modelStack.PushMatrix();
	modelStack.Translate(0, 15, 0);
	modelStack.Scale(10, 10, 10);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_SPHERE]->Render();
	modelStack.PopMatrix();
}

void Scene5::RenderRobot(){
	modelStack.PushMatrix();
	RenderBody();
	RenderHead();
	for (int mirror = 1; mirror >= -1; mirror -= 2){
		modelStack.PushMatrix();
		modelStack.Translate(mirror * 20, 0, 0);
		modelStack.Rotate(-mirror*rotateAngle, 1, 0, 0);
		RenderLimb();
		modelStack.PushMatrix();
		modelStack.Translate(0, -20, 0);
		modelStack.Rotate(-mirror*(-30 + rotateAngle), 1, 0, 0);
		RenderLimb();
		modelStack.PopMatrix();
		modelStack.PopMatrix();
	}
	for (int mirror = 1; mirror >= -1; mirror -= 2){
		modelStack.PushMatrix();
		modelStack.Translate(mirror * 10, -25, 0);
		modelStack.Rotate(mirror*rotateAngle, 1, 0, 0);
		RenderLimb();
		modelStack.PushMatrix();
		modelStack.Translate(0, -20, 0);
		modelStack.Rotate(mirror*(-30+rotateAngle), 1, 0, 0);
		RenderLimb();
		modelStack.PopMatrix();
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();
}