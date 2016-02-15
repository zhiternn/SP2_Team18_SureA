#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"
#include "LoadOBJ.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string &meshName, Color color, float repeat = 1);
	static Mesh* GenerateCube(const std::string &meshName, Color color);
	static Mesh* GenerateEllipse(const std::string &meshName, Color color, unsigned numSlices = 36);
	static Mesh* GenerateCylinder(const std::string &meshName, Color color, float lengthX = 1.f, float lengthZ = 1.f, float height = 1.f, float lengthX2 = 0, float lengthZ2 = 0, unsigned numSlices = 36);
	static Mesh* GenerateCone(const std::string &meshName, Color color, unsigned numSlices = 36);
	static Mesh* GenerateRing(const std::string &meshName, float innerR, float outerR, float angle = 360);
	static Mesh* GenerateTorus(const std::string &meshName, Color color, float innerR = 1.f, float outerR = 0.4f, unsigned stack = 18, unsigned slice = 36);
	static Mesh* GenerateSphere(const std::string &meshName, Color color, unsigned numStacks = 18, unsigned numSlices = 36);
	static Mesh* GenerateSphere2(const std::string &meshName, Color color, unsigned numStacks = 18, unsigned numSlices = 36);
	static Mesh* GenerateHemisphere(const std::string &meshName, Color color, bool isHollow = false);
	static Mesh* GenerateOBJ(const std::string &meshName, const std::string &file_path);
	static Mesh* GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol);
};

#endif