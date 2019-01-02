#include "CMesh.h"


CMesh::CMesh() : m_bLoaded(false), m_meshData(nullptr)
{
}

CMesh::CMesh(const CMesh & other)
{
	m_materialID = other.m_materialID;
	m_vertexBuffer = other.m_vertexBuffer;
	m_indexBuffer = other.m_indexBuffer;
	m_meshData = other.m_meshData;
	m_bLoaded = other.m_bLoaded;
}

CMesh::~CMesh()
{
}

//------------------------------------------------------------------
//
//	LoadMesh(..)
//
//	Params:
//	pData		-	Pointer to mesh data
//	materialID	-	ID to material
//
//  Loads mesh data to vertex and index buffers
//
//------------------------------------------------------------------
ErrorId CMesh::LoadMesh(MeshData* pData, const std::string& materialID)
{
	if (pData == nullptr)
		return ERRORID_GFX_MESH_NULL_MESHDATA;

	// Reference mesh data pointer
	m_meshData = pData;
	m_materialID = materialID;

	// Load vertex data to buffer
	ErrorId error = m_vertexBuffer.LoadData(m_meshData->pVertices, m_meshData->vertexCount, m_meshData->vertexType);
	if (IsNoError(error))
	{
		error = m_indexBuffer.LoadData(m_meshData->pIndices, m_meshData->indexCount);
		// If failed to load data to index buffer, unload the vertex buffer
		if (IsError(error))
			m_vertexBuffer.ShutDown();
		else   // No errors, vertex and index buffer loads successful
			m_bLoaded = true;
	}

	return error;
}

//------------------------------------------------------------------
//
//	LoadMesh(..)
//
//	Params:
//	pData		-	Pointer to mesh data
//
//  Loads mesh data to vertex and index buffers.
//	For required rebuilding of mesh and resubmission
//
//------------------------------------------------------------------
ErrorId CMesh::LoadMesh(MeshData * pData)
{
	if (pData == nullptr)
		return ERRORID_GFX_MESH_NULL_MESHDATA;

	// Reference mesh data pointer
	m_meshData = pData;

	// Load vertex data to buffer
	ErrorId error = m_vertexBuffer.LoadData(m_meshData->pVertices, m_meshData->vertexCount, m_meshData->vertexType);
	if (IsNoError(error))
	{
		error = m_indexBuffer.LoadData(m_meshData->pIndices, m_meshData->indexCount);
		// If failed to load data to index buffer, unload the vertex buffer
		if (IsError(error))
			m_vertexBuffer.ShutDown();
		else   // No errors, vertex and index buffer loads successful
			m_bLoaded = true;
	}

	return error;
}

bool CMesh::IsLoaded() const
{
	return m_bLoaded;
}

const std::string & CMesh::GetMaterialID()
{
	return m_materialID;
}

CVertexBuffer* CMesh::GetVertexBuffer()
{
	return &m_vertexBuffer;
}

CIndexBuffer* CMesh::GetIndexBuffer()
{
	return &m_indexBuffer;
}

MeshData * CMesh::GetMeshData()
{
	return m_meshData;
}

void CMesh::UnloadBuffers()
{
	if (IsLoaded())
	{
		m_meshData = nullptr;			// Don't delete, handled by mesh mgr
		m_vertexBuffer.ShutDown();
		m_indexBuffer.ShutDown();
		m_bLoaded = false;
	}
}

//------------------------------------------------------------------
//
//	CleanUp(..)
//
//  Cleans up data
//
//------------------------------------------------------------------
void CMesh::CleanUp()
{
	// We don't delete the mesh pointer.
	// Handled by the mesh manager
	m_meshData = nullptr;
	m_materialID.clear();
	m_indexBuffer.ShutDown();
	m_vertexBuffer.ShutDown();
	m_bLoaded = false;
}
