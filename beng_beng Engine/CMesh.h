//--------------------------------------------------------------------------
//
//	27/11/2017
//
//	Mesh class which holds required handles for defining a "model"
//	Independent model which holds handle to:
//	- MeshData
//	- VertexData
//	- Shader
//	- Texture (Possibly)
//
//	Author: Matt © 2017
//
//--------------------------------------------------------------------------

#ifndef __CMESH_H__
#define __CMESH_H__

#include "GfxDefs.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"

class CMesh
{
public:
	CMesh();
	CMesh(const CMesh& other);
	~CMesh();

	ErrorId LoadMesh(MeshData* pData, const std::string& materialID);
	ErrorId LoadMesh(MeshData* pData);

	bool IsLoaded() const;
	const std::string& GetMaterialID();

	CVertexBuffer* GetVertexBuffer();
	CIndexBuffer* GetIndexBuffer();

	MeshData* GetMeshData();

	void UnloadBuffers();

	void CleanUp();

protected:
	std::string m_materialID;	// Shader ID (may be included in material)

	CVertexBuffer m_vertexBuffer;
	CIndexBuffer m_indexBuffer;

	MeshData* m_meshData;	// <--------- Reconsider this !

	bool m_bLoaded;
};

#endif
