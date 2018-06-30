#include "CAssetManager.h"
#include "CMaterial.h"
#include "CFwdRender.h"

CAssetManager* CAssetManager::m_pInstance = nullptr;


CAssetManager::CAssetManager() : m_lightShaderID("light_shader")
{
}

CAssetManager::~CAssetManager()
{
}

//------------------------------------------------------------------
//
//	Initialise(..)
//
//	Initialise stuff if needed
//
//------------------------------------------------------------------
bool CAssetManager::Initialise()
{
	m_modelLoader.Initialise(&m_meshDataMgr, &m_textureMgr, &m_materialMgr, &m_modelMgr);
	return true;
}

//------------------------------------------------------------------
//
//	GetInstance(..)
//
//	Returns instance of the asset manager
//
//------------------------------------------------------------------
CAssetManager* CAssetManager::GetInstance() 
{
	if (!m_pInstance) {
		m_pInstance = new CAssetManager;
	}

	return m_pInstance;
}

//------------------------------------------------------------------
//
//	ShutDown(..)
//
//	Closes everything
//
//------------------------------------------------------------------
void CAssetManager::ShutDown()
{
	if (m_pInstance) {
		m_materialMgr.CleanUp();
		m_meshDataMgr.CleanUp();
		m_textureMgr.CleanUp();

		delete m_pInstance;
		m_pInstance = nullptr;
	}
	
}

//------------------------------------------------------------------
//
//	LoadTechnique(..)
//
//	Params:
//	vertexShaderFile	-	Directory to vertex shader
//  fragmentShaderFile	-	Directory to fragment shader
//
//	Loads a single technique.
//	Supports only one currenty which is FwdRender
//
//------------------------------------------------------------------
bool CAssetManager::LoadTechnique(const std::string& vertexShaderFile,
	const std::string& fragmentShaderFile)
{
	m_fwdRender = CFwdRender(vertexShaderFile, fragmentShaderFile);
	if (!m_fwdRender.VInit())
		return false;

	return true;
}

//------------------------------------------------------------------
//
//	LoadTexture(..)
//
//	Params:
//	fileName	-	file directory to texture
//	textureID	-	ID to assign texture
//
//	Loads specified texture file 
//
//------------------------------------------------------------------
bool CAssetManager::LoadTexture(const std::string & fileName, const std::string & textureID)
{
	if (!m_textureMgr.LoadTexture(textureID, fileName)) {
		// Should report some error?
		return false;
	}

	return true;
}

//------------------------------------------------------------------
//
//	GetTexture(..)
//
//	Params:
//	textureID	-	ID of texture
//
//	Returns specified texture, returns nullptr if failed
//
//------------------------------------------------------------------
CTexture2D* CAssetManager::GetTexture(const std::string & textureID)
{
	return m_textureMgr.GetTexture(textureID);
}

//------------------------------------------------------------------
//
//	AddMaterial(..)
//
//	Params:
//	materialID	-	Assigned ID to material
//	material	-	material properties to add
//
//	Adds a material  
//
//------------------------------------------------------------------
bool CAssetManager::AddMaterial(const CMaterial& material, const std::string & materialID)
{
	m_materialMgr.AddMaterial(materialID, material);

	return true;
}

//------------------------------------------------------------------
//
//	GetMaterial(..)
//
//	Params:
//	textureID	-	ID to material 
//
//	Gets loaded material
//
//------------------------------------------------------------------
CMaterial* CAssetManager::GetMaterial(const std::string & materialID)
{
	return m_materialMgr.GetMaterial(materialID);
}

//------------------------------------------------------------------
//
//	LoadModel(..)
//
//	Params:
//	fileName		-	File directory to model
//	meshDataID		-	Assigned ID to model
//
//	Loads model data from file 
//
//------------------------------------------------------------------
bool CAssetManager::LoadModel(const std::string& fileDir, const std::string& fileName, const std::string& modelID)
{
	bool result = true;

	CModel* pModel = m_modelLoader.Load(fileDir, fileName, modelID);

	if (pModel == nullptr)
		result = false;

	return result;
}

bool CAssetManager::CreateModelCube(int size, int subDiv, EVertexType vertType, const std::string & modelID, const std::string& materialID)
{
	bool result = m_meshDataMgr.CreateCube(modelID, size, vertType, subDiv);

	if (result) 
	{
		CModel* pNewModel = m_modelMgr.CreateModel(modelID);
		if (pNewModel != nullptr) 
			result = pNewModel->AddMesh(m_meshDataMgr.GetMeshData(modelID), materialID);
		// Else Remove the created mesh data?
	}

	return result;
}

bool CAssetManager::CreateModeSphere(int size, int subDiv, EVertexType vertType, const std::string & modelID, const std::string& materialID)
{
	bool result = m_meshDataMgr.CreateSphere(modelID, size, vertType, subDiv);

	if (result)
	{
		CModel* pNewModel = m_modelMgr.CreateModel(modelID);
		if (pNewModel != nullptr)
			result = pNewModel->AddMesh(m_meshDataMgr.GetMeshData(modelID), materialID);
		// Else Remove the created mesh data?
	}

	return result;
}

bool CAssetManager::CreateModelPlane(int size, int subDiv, EVertexType vertType, const std::string & modelID, const std::string& materialID)
{
	bool result = m_meshDataMgr.CreatePlane(modelID, size, vertType, subDiv);

	if (result)
	{
		CModel* pNewModel = m_modelMgr.CreateModel(modelID);
		if (pNewModel != nullptr)
			result = pNewModel->AddMesh(m_meshDataMgr.GetMeshData(modelID), materialID);
		// Else Remove the created mesh data?
	}

	return result;
}

//------------------------------------------------------------------
//
//	CreateCubeMeshData(..)
//
//	Params:
//	size			-	Size of the cube
//  subDiv			-	Sub-divsion amount
//	vertType		-	Vertex type
//	meshDataID		-	Assigned ID to mesh data
//
//	Creates cube mesh data
//
//------------------------------------------------------------------
bool CAssetManager::CreateCubeMeshData(int size, int subDiv, EVertexType vertType, const std::string& meshDataID)
{
	return m_meshDataMgr.CreateCube(meshDataID, (float)size, vertType, subDiv);
}

//------------------------------------------------------------------
//
//	CreateSphereMeshData(..)
//
//	Params:
//	size			-	Size of the sphere
//  subDiv			-	Sub-divsion amount
//	vertType		-	Vertex type
//	meshDataID		-	Assigned ID to mesh data
//
//	Creates sphere mesh data
//
//------------------------------------------------------------------
bool CAssetManager::CreateSphereMeshData(int size, int subDiv, EVertexType vertType, const std::string& meshDataID)
{
	return m_meshDataMgr.CreateSphere(meshDataID, (float)size, vertType, subDiv);
}

//------------------------------------------------------------------
//
//	CreatePlaneMeshData(..)
//
//	Params:
//	size			-	Size of the sphere
//  subDiv			-	Sub-divsion amount
//	vertType		-	Vertex type
//	meshDataID		-	Assigned ID to mesh data
//
//	Creates plane mesh data
//
//------------------------------------------------------------------
bool CAssetManager::CreatePlaneMeshData(int size, int subDiv, EVertexType vertType, const std::string& meshDataID)
{
	return m_meshDataMgr.CreatePlane(meshDataID, (float)size, vertType, subDiv);
}

//------------------------------------------------------------------
//
//	CreateVertexBuffer(..)
//
//	Params:
//	meshDataID		-	ID of mesh to get
//
//	Gets specified mesh data
//
//------------------------------------------------------------------
MeshData* CAssetManager::GetMeshData(const std::string & meshDataID)
{
	return m_meshDataMgr.GetMeshData(meshDataID);
}

//------------------------------------------------------------------
//
//	GetFwdRenderTech(..)
//
//	Returns pointer to forward render shader/technique
//
//------------------------------------------------------------------
CFwdRender* CAssetManager::GetFwdRenderTech()
{
	// Return only if technique initialised
	if (m_fwdRender.IsInit())
		return &m_fwdRender;

	return nullptr;
}

//------------------------------------------------------------------
//
//	CreateModel(..)
//
//	Params:
//	modelID		-	model ID to assign new model with
//
//	Creates a new model entry
//
//------------------------------------------------------------------
bool CAssetManager::CreateModel(const std::string & modelID)
{
	if(m_modelMgr.CreateModel(modelID) == nullptr) 
		return false;

	return true;
}

//------------------------------------------------------------------
//
//	GetModel(..)
//
//	Params:
//	modelID		-	ID of model to return
//
//	Returns pointer to model of specified ID.
//	nullptr if not found
//
//------------------------------------------------------------------
CModel * CAssetManager::GetModel(const std::string & modelID)
{
	return m_modelMgr.GetModel(modelID);
}

//------------------------------------------------------------------
//
//	AddMeshToModel(..)
//
//	Params:
//	modelID			-	ID of model
//	meshDataID		-	ID of meshData to load/add to model
//	meshMaterialID	-	ID of material to assign created mesh	
//
//	Attemps to load specified MeshData and creates/adds a CMesh
//  to CModel. Material ID is assigned to the new CMesh.
//
//------------------------------------------------------------------
bool CAssetManager::AddMeshToModel(const std::string & modelID, const std::string & meshDataID,
	const std::string& meshMaterialID)
{
	CModel* pModel = m_modelMgr.GetModel(modelID);
	if (pModel != nullptr)
	{
		MeshData* pData = m_meshDataMgr.GetMeshData(meshDataID);
		if (pData != nullptr)
			return pModel->AddMesh(pData, meshMaterialID);
		
	}
	return false;
}

