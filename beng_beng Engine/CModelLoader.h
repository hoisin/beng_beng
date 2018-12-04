//--------------------------------------------------------------------------
//
//	13/01/2018
//
//  Class handling the loading of 3D model data and convert it to 
//		internal MeshData structure.
//
//	Author: Matt © 2018
//
//--------------------------------------------------------------------------

#pragma once

#include "GfxDefs.h"
#include "CTextureManager.h"
#include "CMaterialManager.h"
#include "CMeshDataManager.h"
#include "CModelManager.h"
#include "CModel.h"

#pragma comment(lib, "assimp.lib")

#ifdef _WIN64
#pragma comment(lib, "assimp-vc140-mt.lib")
#endif

class CModelLoader
{
public:
	CModelLoader();
	~CModelLoader();

	ErrorId Initialise(CMeshDataManager* pMeshMgr, CTextureManager* pTextureMgr, 
		CMaterialManager* pMaterialMgr, CModelManager* pModelMgr);

	CModel* Load(const std::string& fileDir, const std::string& fileName, const std::string modelID);

protected:
	bool m_bInit;

	CMeshDataManager* m_pMeshDataMgr;
	CTextureManager* m_pTextureMgr;
	CMaterialManager* m_pMaterialMgr;
	CModelManager* m_pModelMgr;
};

