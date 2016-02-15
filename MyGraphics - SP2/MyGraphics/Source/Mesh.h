#ifndef MESH_H
#define MESH_H

#include "Material.h"

#include <string>

/******************************************************************************/
/*!
		Class Mesh:
\brief	To store VBO (vertex & color buffer) and IBO (index buffer)
*/
/******************************************************************************/
class Mesh
{
public:
	enum DRAW_MODE
	{
		DRAW_TRIANGLES = 0, //default mode
		DRAW_TRIANGLE_STRIP,
		DRAW_LINES,

		DRAW_MODE_LAST,
	};
	Mesh(const std::string &meshName);
	~Mesh();
	void Render();
	void Render(unsigned offset, unsigned count);

	const std::string name;
	DRAW_MODE mode;
	unsigned vertexBuffer;
	unsigned colorBuffer;
	unsigned indexBuffer;
	unsigned textureID;
	unsigned indexSize;

	Material material;

};

#endif