//--------------------------------------------------------------------------
//
//	Model class representing a whole model consisting of meshes
//	All meshes should be positioned correctly in its local space.
//	e.g. A simple car model can contain as sub-meshes:
//		- the chassis
//		- 4 individual wheels
//	These will be positioned correctly in local space so when transformed,
//		they will be properly placed in world space.
//
//--------------------------------------------------------------------------

#ifndef __CMODEL_H__
#define __CMODEL_H__

#include <vector>
#include <glm\glm.hpp>
#include "GfxDefs.h"
#include "CMesh.h"

#include "CCollisionShape.h"

class CModel
{
public:
	CModel(const std::string meshID);
	~CModel(void);

	bool AddMesh(MeshData* pData, const std::string& materialID);

	CMesh* GetMesh(GLuint index);
	int GetMeshCount() const;
	const std::string& GetID() const;

	void SetCollisionShapeType(ECollisionShape type);
	CCollisionShape* GetCollisionShape();

	void CleanUp(void);

protected:
	std::string m_ID;
	std::vector<CMesh> m_meshes;

	CCollisionShape m_boundingShape;
};


#endif