//--------------------------------------------------------------------------
//
//	24/03/2014
//
//	Generates mesh data from procedural generation or loaded from file.
//	
//	geometryID not needed in params since we are using maps for storage.
//
//	All shapes currently support upto PNT type vertex
//
//	Author: SeaFooD © 2014
//	
//--------------------------------------------------------------------------


#ifndef __CMESHDATAGENERATOR_H__
#define __CMESHDATAGENERATOR_H__

#include "GfxDefs.h"

class CMeshDataGenerator
{
public:
	CMeshDataGenerator();
	~CMeshDataGenerator();
	
	// Creates a single triangle
	MeshData* CreateTriangle(const std::string &geometryID, float size, EVertexType type,
		const glm::vec4 &colour = glm::vec4(0, 0, 0, 0));

	// 2D quad in XY facing towards screen
	MeshData* CreateQuad(const std::string &geometryID, float size, EVertexType type, 
		const glm::vec4 &colour = glm::vec4(0, 0, 0, 0));

	// Same as Quad but XZ facing up
	MeshData* CreatePlane(const std::string &geometryID, float size, EVertexType type, unsigned int numFaces = 1,
		const glm::vec4 &colour = glm::vec4(0, 0, 0, 0));

	// Creates a cube
	MeshData* CreateCube(const std::string &geometryID, float size, EVertexType type, unsigned int numFaces = 1,
		const glm::vec4 &colour = glm::vec4(0, 0, 0, 0));

	// Creates a sphere
	MeshData* CreateSphere(const std::string &geometryID, float size, EVertexType type, unsigned int subDivisions = 1,
		const glm::vec4 &colour = glm::vec4(0, 0, 0, 0));

private:
	void CalculateNormals(MeshData* pMeshData);
	void CalculateTangents(MeshData* pMeshData);
};



#endif