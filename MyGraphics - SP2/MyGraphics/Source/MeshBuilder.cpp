#include "MeshBuilder.h"
#include <GL\glew.h>
#include <vector>
#include "Vertex.h"
#include "MyMath.h"

/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;

	v.pos.Set(-lengthX, 0, 0);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, 0, 0);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, -lengthY, 0);	v.color.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, lengthY, 0);	v.color.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, -lengthZ);	v.color.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, lengthZ);	v.color.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

	for (size_t i = 0; i < 6; ++i){
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_LINES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, Color color, float repeat)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;

	v.pos.Set(-0.5f, 0.5f, 0);	v.color = color;	v.normal.Set(0, 0, 1);	v.texCoord.Set(0, 1 * repeat);			vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0);	v.color = color;	v.normal.Set(0, 0, 1);	v.texCoord.Set(0, 0);					vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0);	v.color = color;	v.normal.Set(0, 0, 1);	v.texCoord.Set(1 * repeat, 1 * repeat);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0);	v.color = color;	v.normal.Set(0, 0, 1);	v.texCoord.Set(1 * repeat, 0);			vertex_buffer_data.push_back(v);

	for (size_t i = 0; i < 4; ++i){
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color color)
{

	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;
	//TOP FACE
	v.pos.Set(0.5f, 0.5f, -0.5f);		v.color = color;	v.normal.Set(0, 1, 0);		vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, -0.5f);		v.color = color;	v.normal.Set(0, 1, 0);		vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);		v.color = color;	v.normal.Set(0, 1, 0);		vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.5f, -0.5f);		v.color = color;	v.normal.Set(0, 1, 0);		vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);		v.color = color;	v.normal.Set(0, 1, 0);		vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0.5f);		v.color = color;	v.normal.Set(0, 1, 0);		vertex_buffer_data.push_back(v);

	//BOTTOM FACE																
	v.pos.Set(0.5f, -0.5f, 0.5f);		v.color = color;	v.normal.Set(0, -1, 0);		vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f);		v.color = color;	v.normal.Set(0, -1, 0);		vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);		v.color = color;	v.normal.Set(0, -1, 0);		vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, -0.5f, 0.5f);		v.color = color;	v.normal.Set(0, -1, 0);		vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);		v.color = color;	v.normal.Set(0, -1, 0);		vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, -0.5f);		v.color = color;	v.normal.Set(0, -1, 0);		vertex_buffer_data.push_back(v);

	//FRONT FACE														
	v.pos.Set(0.5f, 0.5f, 0.5f);		v.color = color;	v.normal.Set(0, 0, 1);		vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);		v.color = color;	v.normal.Set(0, 0, 1);		vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f);		v.color = color;	v.normal.Set(0, 0, 1);		vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.5f, 0.5f);		v.color = color;	v.normal.Set(0, 0, 1);		vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f);		v.color = color;	v.normal.Set(0, 0, 1);		vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);		v.color = color;	v.normal.Set(0, 0, 1);		vertex_buffer_data.push_back(v);

	//BACK FACE																	
	v.pos.Set(-0.5f, 0.5f, -0.5f);		v.color = color;	v.normal.Set(0, 0, -1);		vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, -0.5f);		v.color = color;	v.normal.Set(0, 0, -1);		vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, -0.5f);		v.color = color;	v.normal.Set(0, 0, -1);		vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f, 0.5f, -0.5f);		v.color = color;	v.normal.Set(0, 0, -1);		vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, -0.5f);		v.color = color;	v.normal.Set(0, 0, -1);		vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);		v.color = color;	v.normal.Set(0, 0, -1);		vertex_buffer_data.push_back(v);

	//RIGHT FACE																
	v.pos.Set(0.5f, 0.5f, -0.5f);		v.color = color;	v.normal.Set(1, 0, 0);		vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0.5f);		v.color = color;	v.normal.Set(1, 0, 0);		vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);		v.color = color;	v.normal.Set(1, 0, 0);		vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.5f, -0.5f);		v.color = color;	v.normal.Set(1, 0, 0);		vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);		v.color = color;	v.normal.Set(1, 0, 0);		vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, -0.5f);		v.color = color;	v.normal.Set(1, 0, 0);		vertex_buffer_data.push_back(v);

	//LEFT FACE																			
	v.pos.Set(-0.5f, 0.5f, 0.5f);		v.color = color;	v.normal.Set(-1, 0, 0);		vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, -0.5f);		v.color = color;	v.normal.Set(-1, 0, 0);		vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);		v.color = color;	v.normal.Set(-1, 0, 0);		vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f, 0.5f, 0.5f);		v.color = color;	v.normal.Set(-1, 0, 0);		vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);		v.color = color;	v.normal.Set(-1, 0, 0);		vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f);		v.color = color;	v.normal.Set(-1, 0, 0);		vertex_buffer_data.push_back(v);

	for (size_t i = 0; i < 36; ++i){
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

float circle_H(float theta){
	return cos(Math::DegreeToRadian(theta));
}
float circle_V(float theta){
	return sin(Math::DegreeToRadian(theta));
}

Mesh* MeshBuilder::GenerateEllipse(const std::string &meshName, Color color, unsigned numSlices)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	float anglePerSlice = 360.f / numSlices;

	for (unsigned short slice = 0; slice <= numSlices; slice++){
		float theta = slice * anglePerSlice;

		v.pos.Set(0, 0, 0);
		v.normal.Set(0, 0, 1);
		v.color = color;  
		vertex_buffer_data.push_back(v);

		v.pos.Set(
			(circle_H(theta)),	// X
			(circle_V(theta)),	// Y
			0					// Z
		);
		v.color = color;
		v.normal.Set(0, 0, 1);
		vertex_buffer_data.push_back(v);
	}


	for (size_t i = 0; i < vertex_buffer_data.size(); ++i){
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateCylinder(const std::string &meshName, Color color, float lengthX, float lengthZ, float height, float lengthX2, float lengthZ2, unsigned numSlices)
{
	if (lengthX2 == 0){
		lengthX2 = lengthX;
	}
	if (lengthZ2 == 0){
		lengthZ2 = lengthZ;
	}
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	float anglePerSlice = 360.f / numSlices;

	//CYLINDER BOTTOM COVER
	for (unsigned short slice = 0; slice <= numSlices; slice++){
		float theta = slice * anglePerSlice;

		v.pos.Set(0, -height / 2, 0);
		v.color = color;
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);

		v.pos.Set(lengthX2*circle_H(theta), -height / 2, lengthZ2*circle_V(theta));
		v.color = color;
		v.normal.Set(circle_H(theta), -1, circle_V(theta));
		vertex_buffer_data.push_back(v);
	}
	// CYLINDER SIDES
	for (unsigned short slice = 0; slice <= numSlices; slice++){
		float theta = slice * anglePerSlice;

		v.pos.Set(lengthX2*circle_H(theta), -height / 2, lengthZ2*circle_V(theta));
		v.color = color;
		v.normal.Set(circle_H(theta), 0, circle_V(theta));
		vertex_buffer_data.push_back(v);

		v.pos.Set(lengthX*circle_H(theta), height / 2, lengthZ*circle_V(theta));
		v.color = color;
		v.normal.Set(circle_H(theta), 0, circle_V(theta));
		vertex_buffer_data.push_back(v);
	}
	// CYLINDER TOP COVER
	for (unsigned short slice = 0; slice <= numSlices; slice++){
		float theta = slice * anglePerSlice;

		v.pos.Set(lengthX*circle_H(theta), height / 2, lengthZ*circle_V(theta));
		v.color = color;
		v.normal.Set(circle_H(theta), 1, circle_V(theta));
		vertex_buffer_data.push_back(v);

		v.pos.Set(0, height / 2, 0);
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
	}

	for (size_t i = 0; i < vertex_buffer_data.size(); ++i){
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateCone(const std::string &meshName, Color color, unsigned numSlices)
{

	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	float anglePerSlice = 360.f / numSlices;

	//CONE BOTTOM COVER
	for (unsigned short slice = 0; slice <= numSlices; slice++){
		float theta = slice * anglePerSlice;

		v.pos.Set(0, 0, 0);
		v.color = color;
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);

		v.pos.Set(circle_H(theta), 0, circle_V(theta));
		v.color = color;
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);
	}
	// CONE
	for (unsigned short slice = 0; slice <= numSlices; slice++){
		float theta = slice * anglePerSlice;

		v.pos.Set(circle_H(theta), 0, circle_V(theta));
		v.color = color;
		v.normal.Set(circle_H(theta), 1, circle_V(theta));
		vertex_buffer_data.push_back(v);

		v.pos.Set(0, 1, 0);
		v.color = color;
		v.normal.Set(circle_H(theta), 1, circle_V(theta));
		vertex_buffer_data.push_back(v);
	}

	for (size_t i = 0; i < vertex_buffer_data.size(); ++i){
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateRing(const std::string &meshName, float innerR, float outerR, float angle){
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;

	for (size_t i = 0; i <= angle; i += 5){
		v.pos.Set(
			(float)(innerR*cos(Math::DegreeToRadian(i))),	// X
			0,														// Y
			(float)(innerR*sin(Math::DegreeToRadian(i)))	// Z
			);
		v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);

		v.pos.Set(
			(float)(outerR*cos(Math::DegreeToRadian(i))),	// X
			0,														// Y
			(float)(outerR*sin(Math::DegreeToRadian(i)))	// Z
			);
		v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	}
	for (size_t i = 0; i <= angle; i += 5){
		v.pos.Set(
			(float)(outerR*cos(Math::DegreeToRadian(i))),	// X
			0,														// Y
			(float)(outerR*sin(Math::DegreeToRadian(i)))	// Z
			);
		v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);

		v.pos.Set(
			(float)(innerR*cos(Math::DegreeToRadian(i))),	// X
			0,														// Y
			(float)(innerR*sin(Math::DegreeToRadian(i)))	// Z
			);
		v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	}


	for (size_t i = 0; i < vertex_buffer_data.size(); ++i){
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}


Mesh* MeshBuilder::GenerateTorus(const std::string &meshName, Color color, float innerR, float outerR, unsigned numStack, unsigned numSlice)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;

	float degreePerStack = 360.0f / numStack;
	float degreePerSlice = 360.0f / numSlice;
	float x1, z1; //y1 is always zero
	float y1 = 0;
	float x2, y2, z2;

	for (size_t stack = 0; stack <= numStack; stack++) {
		for (size_t slice = 0; slice <= numSlice; slice++) {
			z1 = innerR * cos(stack * Math::DegreeToRadian(degreePerStack));
			x1 = innerR * sin(stack * Math::DegreeToRadian(degreePerStack));
			z2 = (innerR + outerR * cos(slice * Math::DegreeToRadian(degreePerSlice))) * cos(stack * Math::DegreeToRadian(degreePerStack));
			y2 = outerR * sin(slice * Math::DegreeToRadian(degreePerSlice));
			x2 = (innerR + outerR * cos(slice * Math::DegreeToRadian(degreePerSlice))) * sin(stack * Math::DegreeToRadian(degreePerStack));
			
			v.pos.Set(x2, y2, z2); 
			v.color = color; 
			v.normal.Set(x2-x1, y2, z2-z1);
			vertex_buffer_data.push_back(v);

		}
	}

	for(unsigned stack = 0; stack < numStack; stack++) {
		for(unsigned slice = 0; slice <= numSlice; slice++) {
			index_buffer_data.push_back((numSlice + 1) * stack + slice);
			index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice);
		}
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

float sphereX(float phi, float theta){
	return (float)(cos(Math::DegreeToRadian(phi))*cos(Math::DegreeToRadian(theta)));
}
float sphereY(float phi, float theta){
	return (float)(sin(Math::DegreeToRadian(phi)));
}
float sphereZ(float phi, float theta){
	return (float)(cos(Math::DegreeToRadian(phi))*sin(Math::DegreeToRadian(theta)));
}
Mesh* MeshBuilder::GenerateSphere(const std::string &meshName, Color color, unsigned numStacks, unsigned numSlices)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;

	float anglePerStack = 180.f / numStacks;
	float anglePerSlice = 360.f / numSlices;

	for (unsigned stack = 0; stack <= numStacks; ++stack){
		float phi = -90 + (stack * anglePerStack);
		for (unsigned slice = 0; slice <= numSlices; ++slice){
			float theta = slice * anglePerSlice;

			v.pos.Set(sphereX(phi, theta), sphereY(phi, theta), sphereZ(phi, theta));
			v.color = color;
			v.normal.Set(sphereX(phi, theta), sphereY(phi, theta), sphereZ(phi, theta));
			vertex_buffer_data.push_back(v);
		}
	}

	for (unsigned stack = 0; stack < numStacks; ++stack){
		for (unsigned slice = 0; slice <= numSlices; ++slice){
			index_buffer_data.push_back(stack * (numSlices + 1) + slice);
			index_buffer_data.push_back((stack + 1) * (numSlices + 1) + slice);
		}
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}
Mesh* MeshBuilder::GenerateSphere2(const std::string &meshName, Color color, unsigned numStacks, unsigned numSlices)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;

	for (unsigned stack = 0; stack <= numStacks; ++stack){
		float phi = -90 + (stack * 10.f);
		for (unsigned slice = 0; slice <= numSlices; ++slice){
			float theta = slice * 10.f;

			v.pos.Set(sphereX(phi, theta), sphereY(phi, theta), sphereZ(phi, theta));
			v.color = color;
			v.normal.Set(sphereX(phi, theta), sphereY(phi, theta), sphereZ(phi, theta));
			vertex_buffer_data.push_back(v);
		}
	}

	for (unsigned stack = 0; stack < numStacks; ++stack){
		for (unsigned slice = 0; slice <= numSlices; ++slice){
			index_buffer_data.push_back(stack * (numSlices + 1) + slice);
			index_buffer_data.push_back((stack + 1) * (numSlices + 1) + slice);
		}
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateHemisphere(const std::string &meshName, Color color, bool isHollow)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;

	int numStacks = 18;
	int numSlices = 36;

	float anglePerStack = 90.f / numStacks;
	float anglePerSlice = 360.f / numSlices;

	for (unsigned stack = 0; stack <= numStacks; ++stack){
		float phi = -90.f + (stack * anglePerStack);
		for (unsigned slice = 0; slice <= numSlices; ++slice){
			float theta = slice * anglePerSlice;

			v.pos.Set(sphereX(phi, theta), sphereY(phi, theta), sphereZ(phi, theta));
			v.color = color;	
			v.normal.Set(sphereX(phi, theta), sphereY(phi, theta), sphereZ(phi, theta));
			vertex_buffer_data.push_back(v);
		}
	}
	if (!isHollow){
		for (unsigned short slice = 0; slice <= numSlices; slice++){
			float theta = slice * anglePerSlice;

			v.pos.Set(0, 0, 0);	 
			v.color = color;
			v.normal.Set(0, 1, 0);
			vertex_buffer_data.push_back(v);

			v.pos.Set(circle_H(theta), 0, circle_V(theta));
			v.color = color;	
			v.normal.Set(circle_H(theta), 1, circle_V(theta));
			vertex_buffer_data.push_back(v);
		}
	}

	for (unsigned stack = 0; stack < numStacks; ++stack){
		for (unsigned slice = 0; slice <= numSlices; ++slice){
			index_buffer_data.push_back(stack * (numSlices + 1) + slice);
			index_buffer_data.push_back((stack + 1) * (numSlices + 1) + slice);
		}
	}
	if (!isHollow){
		for (size_t i = (numStacks * (numSlices+3)); i <= vertex_buffer_data.size(); ++i){
			index_buffer_data.push_back(i);
		}
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateOBJ(const std::string &meshName, const std::string &file_path) {
	//Read vertices, texcoords & normals from OBJ
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);
	if(!success)
		return NULL;
	//Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);
	//Create the mesh and call glBindBuffer, glBufferData
	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	//Use triangle list and remember to set index size
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;

	float width = 1.f / numCol;
	float height = 1.f / numRow;
	int offset = 0;

	for (unsigned j = 0; j < numRow; ++j)
	{
		for (unsigned i = 0; i < numCol; ++i)
		{
			v.pos.Set(-0.5f, -0.5f, 0);	v.texCoord.Set(i * width,		1.f - (j + 1) * height);			v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
			v.pos.Set(0.5f, -0.5f, 0);	v.texCoord.Set((i + 1) * width, 1.f - (j + 1) * height);	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
			v.pos.Set(0.5f, 0.5f, 0);	v.texCoord.Set((i + 1) * width, 1.f - (j)* height);			v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
			v.pos.Set(-0.5f, 0.5f, 0);	v.texCoord.Set(i * width,		1.f - (j)* height);				v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 1);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 3);
			offset += 4;
		}
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}