//--------------------------------------------------------------------------
//
//	26/02/2015
//
//	Just manages the created mesh data (RAM/CPU data).
//	Include the geometry generator here for now. May make it seperate later.
//
//	Author: Matt © 2015
//
//--------------------------------------------------------------------------

#ifndef __CMESHDATAMANAGER_H__
#define __CMESHDATAMANAGER_H__

#include <map>
#include <vector>
#include "Errors.h"
#include "GfxDefs.h"
#include "CMeshDataGenerator.h"

class CMeshDataManager
{
public:
	CMeshDataManager(void);
	~CMeshDataManager(void);

	// Function allows mesh data to be added into manager.
	// For when adding loading mesh data from external file.
	// A interface will be required to generate the mesh data from reading a mesh data file of 'N' format.
	// This will create a copy of the passed in input
	ErrorId AddMeshData(MeshData* pNewMeshData, const std::string& meshDataID);

	// Procedurally generated mesh data
	ErrorId CreatePlane(const std::string& geometryID, float size, EVertexType type, unsigned int subDivisions = 1,
		const glm::vec4& colour = glm::vec4(0, 0, 0, 0));
	ErrorId CreateCube(const std::string& geometryID, float size, EVertexType type, unsigned int subDivisions = 1,
		const glm::vec4& colour = glm::vec4(0, 0, 0, 0));
	ErrorId CreateSphere(const std::string& geometryID, float size, EVertexType type, unsigned int subDivisions = 1,
		const glm::vec4& colour = glm::vec4(0, 0, 0, 0));

	MeshData* GetMeshData(const std::string& meshDataID);
	ErrorId RemoveMeshData(const std::string& meshDataID);

	int GetMeshCount() const;

	void CleanUp(void);

protected:
	void CalculateMinMaxBoundary(MeshData* pMeshData);

	bool ExistingMeshDataCheck(const std::string& meshID);

protected:
	CMeshDataGenerator m_meshDataGenerator;
	std::vector<MeshData> m_meshDataVec;             
};




#endif