#include "CModel.h"

CModel::CModel(const std::string meshID) : m_ID(meshID)
{
}

CModel::~CModel(void)
{
}

//------------------------------------------------------------------
//
//	AddMesh(..)
//
//	Params:
//	pData		-	Pointer to mesh data
//	materialID	-	ID to material for mesh
//
//  Adds mesh data to model.
//	Model can contain a collection of meshes
//
//------------------------------------------------------------------
ErrorId CModel::AddMesh(MeshData* pData, const std::string& materialID)
{
	if (pData == nullptr)
		return ERRORID_GFX_MESH_NULL_MESHDATA;

	// Generate new mesh
	m_meshes.push_back(CMesh());

	int meshIdx = (int)m_meshes.size() - 1;
	CMesh* pNewMesh = &m_meshes[meshIdx];

	ErrorId error = pNewMesh->LoadMesh(pData, materialID);
	// If the mesh load fails, remove the new mesh from vector
	if (IsError(error))
	{
		pNewMesh = nullptr;
		m_meshes.pop_back();
		return error;
	}

	// Update bounding shape
	m_boundingShape.UpdateBoundary(pData->minVertex, pData->maxVertex);

	return error;
}

//------------------------------------------------------------------
//
//	GetMesh(..)
//
//	Params:
//	index		-	Index to mesh in array
//
//	Returns the specified mesh in element index
//
//------------------------------------------------------------------
CMesh* CModel::GetMesh(GLuint index)
{
	CMesh* pMesh = nullptr;

	if (index < m_meshes.size())
		pMesh = &m_meshes[index];

	return pMesh;
}

int CModel::GetMeshCount() const
{
	return (int)m_meshes.size();
}

const std::string & CModel::GetID() const
{
	return m_ID;
}

void CModel::SetCollisionShapeType(ECollisionShape type)
{
	m_boundingShape.SetType(type);
}

CCollisionShape* CModel::GetCollisionShape()
{
	return &m_boundingShape;
}

void CModel::CleanUp(void)
{
	// Clean up meshes
	auto it = m_meshes.begin();
	while (it != m_meshes.end())
	{
		it->CleanUp();
		++it;
	}
	m_meshes.clear();
	m_boundingShape.Reset();
}

