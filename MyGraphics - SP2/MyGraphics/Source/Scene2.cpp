#include "Scene2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Application.h"


Scene2::Scene2()
{
}

Scene2::~Scene2()
{
}

void Scene2::Init()
{
	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Generate Buffers
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

	//Initializing transforming matrices
	rotateAngle = 30.0f;
	translateX = 10.0f;
	scaleAll = 10.0f;

//======================================================================================
//TRIANGLE ONE - START
//======================================================================================
	// FIRST TRIANGLE VERTEX
	// An array of 3 vectors which represents 3 vertices
	static const GLfloat vertex_buffer_data[] = {
		0.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
	};
	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
	// FIRST TRIANGLE COLOR
	// An array of 3 vectors which represents the colors of the 3 vertices
	static const GLfloat color_buffer_data[] = {
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
	};
	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
//======================================================================================
//TRIANGLE ONE - END
//======================================================================================


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
}

void Scene2::Update(double dt)
{
	if (Application::IsKeyPressed(VK_SPACE)){
		rotateAngle += (float)(100 * dt);
		if (translateX >= 40){
			translateX = -40;
		}
		else{
			translateX += (float)(10 * dt);
		}
		if (scaleAll >= 40){
			scaleAll = 1;
		}
		else{
			scaleAll += (float)(10 * dt);
		}
	}
}

void Scene2::Render()
{
	// Clear color & depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//MVP MATRIXES
	Mtx44 translate, rotate, scale;
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;
	Mtx44 MVP;
	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();
	view.SetToIdentity(); //no need camera for now, set it at World's origin
	projection.SetToOrtho(-40, 40, -30, 30, -10, 10); //Our world is a cube defined by these boundaries

glEnableVertexAttribArray(0); // 1st attribute buffer: vertices
glEnableVertexAttribArray(1); // 2nd attribute buffer : colors

	scale.SetToScale(5, 5, 5);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	translate.SetToTranslation(15, 20, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	//DRAWING TRIANGLE 1
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(
		0,	// attribute 0. Must match the layout in the shader. Usually 0 is for vertex
		3,	// size
		GL_FLOAT,	// type
		GL_TRUE,	// normalized?
		0,	// stride
		0	// array buffer offset
		);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0. 3 vertices = 1 triangle

	scale.SetToScale(10, 10, 10);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX, 20, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	//DRAWING TRIANGLE 1
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(
		0,	// attribute 0. Must match the layout in the shader. Usually 0 is for vertex
		3,	// size
		GL_FLOAT,	// type
		GL_TRUE,	// normalized?
		0,	// stride
		0	// array buffer offset
		);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0. 3 vertices = 1 triangle

	scale.SetToScale(scaleAll, scaleAll, scaleAll);
	rotate.SetToRotation(30, 0, 0, 1);
	translate.SetToTranslation(0, 0, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	//DRAWING TRIANGLE 1
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(
		0,	// attribute 0. Must match the layout in the shader. Usually 0 is for vertex
		3,	// size
		GL_FLOAT,	// type
		GL_TRUE,	// normalized?
		0,	// stride
		0	// array buffer offset
		);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0. 3 vertices = 1 triangle

glDisableVertexAttribArray(0);
glDisableVertexAttribArray(1);
}

void Scene2::Exit()
{
	// Cleanup VBO here

	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
