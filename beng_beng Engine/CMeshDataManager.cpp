#include "CMeshDataManager.h"
#include "CMeshDataGenerator.h"
#include "GfxDefs.h"

#include <string>

CMeshDataManager::CMeshDataManager(void)
{
}



CMeshDataManager::~CMeshDataManager(void)
{
	CleanUp();
}

//-------------------------------------------------------------------------------------
//
//	AddMeshData(..)
//
//	Params:
//	pNewMeshData		-	Mesh to add to manager
//	meshDataID			-	ID of mesh
//
//	Description:
//	Adds mesh data to manager. Note this creates a copy of the passed in mesh data.
//	The user is responsible for the passed in mesh data if it was created on the heap
//
//-------------------------------------------------------------------------------------
ErrorId CMeshDataManager::AddMeshData(MeshData* pNewMeshData, const std::string& meshDataID)
{
	if (pNewMeshData == nullptr)
		return ERRORID_MESHDATA_NULL_MESHDATA_PTR;

	if (meshDataID == "")
		return ERRORID_MESHDATA_ID_NULL;

	// Already an entry with same ID, return false
	if (ExistingMeshDataCheck(meshDataID))
		return ERRORID_MESHDATA_ID_DUPLICATE;

	pNewMeshData->m_ID = meshDataID;

	CalculateMinMaxBoundary(pNewMeshData);
	m_meshDataVec.push_back(*pNewMeshData);
	return ERRORID_NONE;
}

//-------------------------------------------------------------------------------------
//
//	CreatePlane(..)
//
//	Params:
//	geometryID		-	Mesh to add to manager
//	size			-	ID of mesh
//	type			-	vertex type
//	subDivisions	-	sub-dvisions
//	colour			-	vertex color
//
//	Description:
//	Creates a plane mesh
//
//-------------------------------------------------------------------------------------
ErrorId CMeshDataManager::CreatePlane(const std::string& geometryID, float size, EVertexType type, unsigned int subDivisions,
	const glm::vec4& colour)
{
	if (geometryID == "")
		return ERRORID_MESHDATA_ID_NULL;

	if (ExistingMeshDataCheck(geometryID))
		return ERRORID_MESHDATA_ID_DUPLICATE;

	if (size <= 0)
		return ERRORID_MESHDATA_SHAPE_GENERATE_SIZE_ZERO;

	MeshData* pNewPlaneMesh = m_meshDataGenerator.CreatePlane(geometryID, size, type, subDivisions, colour);
	CalculateMinMaxBoundary(pNewPlaneMesh);
	m_meshDataVec.push_back(*pNewPlaneMesh);

	// Clean up 
	delete pNewPlaneMesh;

	return ERRORID_NONE;
}

//-------------------------------------------------------------------------------------
//
//	CreatePlane(..)
//
//	Params:
//	geometryID		-	Mesh to add to manager
//	size			-	ID of mesh
//	type			-	vertex type
//	subDivisions	-	sub-dvisions
//	colour			-	vertex color
//
//	Description:
//	Creates a cube mesh
//
//-------------------------------------------------------------------------------------
ErrorId CMeshDataManager::CreateCube(const std::string& geometryID, float size, EVertexType type, unsigned int subDivisions,
	const glm::vec4& colour)
{
	if (geometryID == "")
		return ERRORID_MESHDATA_ID_NULL;

	if (ExistingMeshDataCheck(geometryID))
		return ERRORID_MESHDATA_ID_DUPLICATE;

	if (size <= 0)
		return ERRORID_MESHDATA_SHAPE_GENERATE_SIZE_ZERO;

	MeshData* pNewCubeMesh = m_meshDataGenerator.CreateCube(geometryID, size, type, subDivisions, colour);
	CalculateMinMaxBoundary(pNewCubeMesh);
	m_meshDataVec.push_back(*pNewCubeMesh);

	// Clean up
	delete pNewCubeMesh;

	return ERRORID_NONE;
}

//-------------------------------------------------------------------------------------
//
//	CreatePlane(..)
//
//	Params:
//	geometryID		-	Mesh to add to manager
//	size			-	ID of mesh
//	type			-	vertex type
//	subDivisions	-	sub-dvisions
//	colour			-	vertex color
//
//	Description:
//	Creates a sphere mesh
//
//-------------------------------------------------------------------------------------
ErrorId CMeshDataManager::CreateSphere(const std::string& geometryID, float size, EVertexType type, unsigned int subDivisions,
		const glm::vec4& colour)
{
	if (geometryID == "")
		return ERRORID_MESHDATA_ID_NULL;

	if (ExistingMeshDataCheck(geometryID))
		return ERRORID_MESHDATA_ID_DUPLICATE;

	if (size <= 0)
		return ERRORID_MESHDATA_SHAPE_GENERATE_SIZE_ZERO;

	MeshData* pNewSphereMesh = m_meshDataGenerator.CreateSphere(geometryID, size, type, subDivisions, colour);
	CalculateMinMaxBoundary(pNewSphereMesh);
	m_meshDataVec.push_back(*pNewSphereMesh);

	delete pNewSphereMesh;

	return ERRORID_NONE;
}

//-------------------------------------------------------------------------------------
//
//	GetMeshData(..)
//
//	Params:
//	meshDataID		-	Mesh to return
//
//	Description:
//	Returns pointer of the mesh data
//
//-------------------------------------------------------------------------------------
MeshData* CMeshDataManager::GetMeshData(const std::string& meshDataID)
{
	for (int i = 0; i < (int)m_meshDataVec.size(); i++) {
		if(m_meshDataVec[i].m_ID == meshDataID)
			return &m_meshDataVec[i];
	}

	return nullptr;
}

//-------------------------------------------------------------------------------------
//
//	RemoveMeshData(..)
//
//	Params:
//	meshDataID		-	Mesh to remove
//
//	Description:
//	Remove mesh from array
//
//-------------------------------------------------------------------------------------
ErrorId CMeshDataManager::RemoveMeshData(const std::string& meshDataID)
{
	for (int i = 0; i < (int)m_meshDataVec.size(); i++) {
		if (m_meshDataVec[i].m_ID == meshDataID) {
			std::swap(m_meshDataVec[i], m_meshDataVec.back());
			m_meshDataVec.pop_back();
			return ERRORID_NONE;
		}
	}

	// else no such entry...
	return ERRORID_MESHDATA_REMOVE_DATA_FAILED;
}

int CMeshDataManager::GetMeshCount() const
{
	return (int)m_meshDataVec.size();
}


//-------------------------------------------------------------------------------------
//
//	CleanUp(..)
//
//	Description:
//	Cleans up
//
//-------------------------------------------------------------------------------------
void CMeshDataManager::CleanUp(void)
{
	m_meshDataVec.clear();
}

void CMeshDataManager::CalculateMinMaxBoundary(MeshData * pMeshData)
{
	glm::vec3 min(FLT_MAX, FLT_MAX, FLT_MAX);
	glm::vec3 max(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	SVertexType* pVert = pMeshData->pVertices;
	for (int i = 0; i < pMeshData->vertexCount; i++) {
		// Check max
		if (pVert[i].position.x > max.x) {
			max.x = pVert[i].position.x;
		}
		if (pVert[i].position.y > max.y) {
			max.y = pVert[i].position.y;
		}
		if (pVert[i].position.z > max.z) {
			max.z = pVert[i].position.z;
		}

		// Check min
		if (pVert[i].position.x < min.x) {
			min.x = pVert[i].position.x;
		}
		if (pVert[i].position.y < min.y) {
			min.y = pVert[i].position.y;
		}
		if (pVert[i].position.z < min.z) {
			min.z = pVert[i].position.z;
		}
	}

	pMeshData->minVertex = min;
	pMeshData->maxVertex = max;
}

bool CMeshDataManager::ExistingMeshDataCheck(const std::string & meshID)
{
	for (int i = 0; i < (int)m_meshDataVec.size(); i++) {
		if (m_meshDataVec[i].m_ID == meshID) 
			return true;
	}

	return false;
}


