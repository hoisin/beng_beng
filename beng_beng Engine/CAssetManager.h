//--------------------------------------------------------------------------
//
//	Scene manager
//	- Performs processing of scene to render
//	- Passed new objects handles by this (life time)
//
//--------------------------------------------------------------------------

#pragma once

#include <string>
#include "GfxDefs.h"

#include "CMeshDataManager.h"
#include "CMaterialManager.h"
#include "CModelManager.h"
#include "CTextureManager.h"
#include "CModelLoader.h"

#include "CFwdRender.h"

class CAssetManager
{
public:
	~CAssetManager();

	bool Initialise();

	static CAssetManager* GetInstance();

	void ShutDown();

	// Load shader
	// Only one at the moment. Potentially another if deferred
	ErrorId LoadTechnique(const std::string& vertexShaderFile,
		const std::string& fragmentShaderFile);

	// Material loading
	// - Involves loading texture
	// - Load/creating shader params + linking texture
	bool LoadTexture(const std::string& fileName, const std::string& textureID);
	CTexture2D* GetTexture(const std::string& textureID);

	bool AddMaterial(const CMaterial& material, const std::string& materialID);
	CMaterial* GetMaterial(const std::string& materialID);

	// Create models
	bool LoadModel(const std::string& fileDir, const std::string& fileName, const std::string& modelID);
	ErrorId CreateModelCube(int size, int subDiv, EVertexType vertType, const std::string& modelID, const std::string& materialID);
	ErrorId CreateModeSphere(int size, int subDiv, EVertexType vertType, const std::string& modelID, const std::string& materialID);
	ErrorId CreateModelPlane(int size, int subDiv, EVertexType vertType, const std::string& modelID, const std::string& materialID);

	// Generating/loading mesh data
	//	- Load/Generating mesh data CPU side
	//
	// These are to be replaced by model creation functions.
	// But keeping them here for now. Avoid using them directly
	bool CreateCubeMeshData(int size, int subDiv, EVertexType vertType, const std::string& meshDataID);
	bool CreateSphereMeshData(int size, int subDiv, EVertexType vertType, const std::string& meshDataID);
	bool CreatePlaneMeshData(int size, int subDiv, EVertexType vertType, const std::string& meshDataID);

	MeshData* GetMeshData(const std::string& meshDataID);

	CFwdRender* GetFwdRenderTech();

	// Create CMesh/Submesh linking clas objects
	bool CreateModel(const std::string& modelID);
	CModel* GetModel(const std::string& modelID);

	ErrorId AddMeshToModel(const std::string& modelID, const std::string& meshDataID,
		const std::string& meshMaterialID);

protected:
	CAssetManager();

protected:
	CMeshDataManager m_meshDataMgr;
	CModelManager m_modelMgr;
	CMaterialManager m_materialMgr;
	CTextureManager m_textureMgr;

	CFwdRender m_fwdRender;
	CModelLoader m_modelLoader;

	// Temproary light shader ID
	std::string m_lightShaderID;

	bool m_bInit;

private:
	static CAssetManager* m_pInstance;

};

#define ASSETMGR CAssetManager::GetInstance()