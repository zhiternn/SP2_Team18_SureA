#include "Scene1.h"
#include "GL\glew.h"

#include "shader.hpp"


Scene1::Scene1()
{
}

Scene1::~Scene1()
{
}

void Scene1::Init()
{
	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Generate Buffers
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

	// FIRST TRIANGLE VERTEX
	// An array of 3 vectors which represents 3 vertices
	static const GLfloat vertex_buffer_data[] = {
		0.0f, 1.0f, 0.0f,
		-0.75f, 0.75f, 0.0f,
		0.75f, 0.75f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		-0.75f, -0.75f, 0.0f,
		0.75f, -0.75f, 0.0f,
		0.0f, -1.0f, 0.0f,
	};
	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

	// SECOND TRIANGLE VERTEX
	static const GLfloat vertex_buffer_data2[] = { 
		0.0f, 1.0f, -0.5f,
		-0.4f, -1.0f, -0.5f,
		0.15f, -0.1f, -0.5f,
		0.0f, 1.0f, -0.5f,
		0.4f, -1.0f, -0.5f,
		-0.15f, -0.1f, -0.5f,
		-0.8f, 0.2f, -0.5f, 
		0.8f, 0.2f, -0.5f,
		0.0f, -0.3f, -0.5f,
		/*0.0f, 1.0f, 0.5f,
		-0.4f, -1.0f, 0.5f,
		0.15f, -0.1f, 0.5f,
		0.0f, 1.0f, 0.5f,
		0.4f, -1.0f, 0.5f,
		-0.15f, -0.1f, 0.5f,
		-0.8f, 0.2f, 0.5f,
		0.8f, 0.2f, 0.5f,
		0.0f, -0.3f, 0.5f,*/
	};
	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data2), vertex_buffer_data2, GL_STATIC_DRAW);

	// FIRST TRIANGLE COLOR
	// An array of 3 vectors which represents the colors of the 3 vertices
	static const GLfloat color_buffer_data[] = {
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
	};
	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	// SECOND TRIANGLE COLOR
	// An array of 3 vectors which represents the colors of the 3 vertices
	static const GLfloat color_buffer_data2[] = {
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
	};
	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data2), color_buffer_data2, GL_STATIC_DRAW);

	// Load vertex and fragment shaders
	m_programID = LoadShaders(
		"Shader//SimpleVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader");
	// Use our shader
	glUseProgram(m_programID);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);		//I TEMPORARY COMMENTED THIS OFF AS IT PREVENTS ME FROM OVERLAPPING <-- idk why
}

void Scene1::Update(double dt)
{
}

void Scene1::Render()
{
	// Clear color & depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(0); // 1st attribute buffer: vertices
	glEnableVertexAttribArray(1); // 2nd attribute buffer : colors

	//DRAWING TRIANGLE 1
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(
		0,	// attribute 0. Must match the layout in the shader. Usually 0 is for vertex
		3,	// size
		GL_FLOAT,	// type
		GL_FALSE,	// normalized?
		0,	// stride
		0	// array buffer offset
		);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the triangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); // Starting from vertex 0. 3 vertices = 1 triangle

	// DRAWING TRIANGLE 2
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(
		0,	// attribute 0. Must match the layout in the shader. Usually 0 is for vertex
		3,	// size
		GL_FLOAT,	// type
		GL_FALSE,	// normalized?
		0,	// stride
		0	// array buffer offset
		);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the triangle
	glDrawArrays(GL_TRIANGLES, 0, 9); // Starting from vertex 0. 3 vertices = 1 triangle

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Scene1::Exit()
{
	// Cleanup VBO here

	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
