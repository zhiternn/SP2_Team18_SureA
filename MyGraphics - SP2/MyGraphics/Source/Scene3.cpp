#include "Scene3.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Application.h"
#include "MeshBuilder.h"


Scene3::Scene3()
{
}

Scene3::~Scene3()
{
}

void Scene3::Init()
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

	//Initializing transforming matrices
	rotateAngle = 30.0f;
	translateX = 10.0f;
	scaleAll = 10.0f;

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	camera.Init(Vector3(4, 3, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("axis", 1000, 1000, 1000);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", 1, 1, 1, Color(1, 0, 0));
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", 1, 1, Color(1, 0, 0));
	meshList[GEO_ELLIPSE] = MeshBuilder::GenerateEllipse("ellipse", 1, 1, Color(1, 0, 0), 60);
	meshList[GEO_RING] = MeshBuilder::GenerateRing("ellipse", 1, 1, 5, 3);
	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", 1, 1, 1, Color(1, 0, 0));
	meshList[GEO_HEMISPHERE] = MeshBuilder::GenerateHemisphere("hemisphere", 1, 1, 1, Color(1, 0, 0));
	meshList[GEO_TORUS] = MeshBuilder::GenerateTorus("torus", 2.5f, 0.5f, 1, 1, 1, Color(1, 0, 0));

}

void Scene3::Update(double dt)
{
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

	camera.Update(dt);
	if (Application::IsKeyPressed(VK_SPACE)){
		rotateAngle = 0;
	}
	else{
		rotateAngle += (float)(60 * dt);
	}
}

void Scene3::Render()
{
	// Clear color & depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();
	view.SetToIdentity(); //no need camera for now, set it at World's origin
	//projection.SetToOrtho(-40, 40, -30, 30, -10, 10); //Our world is a cube defined by these boundaries

	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f); // FOV, Aspect Ratio, Near plane, Far plane

	view.SetToLookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);

	model.SetToIdentity();
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_AXES]->Render();

	model.SetToIdentity();
	rotate.SetToRotation(rotateAngle, 1, 1, 0);
	translate.SetToTranslation(0, 1, 0);
	model = translate * rotate;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_CUBE]->Render();
}

void Scene3::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}