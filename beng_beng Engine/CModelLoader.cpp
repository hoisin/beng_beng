#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>

#include "CModelLoader.h"

CModelLoader::CModelLoader() : m_bInit(false), m_pMeshDataMgr(nullptr), m_pTextureMgr(nullptr),
m_pMaterialMgr(nullptr)
{
}

CModelLoader::~CModelLoader()
{
	// Not this class's responsiblity to clean up these!
	m_pMeshDataMgr = nullptr;
	m_pTextureMgr = nullptr;
	m_pMaterialMgr = nullptr;
	m_pModelMgr = nullptr;
}

ErrorId CModelLoader::Initialise(CMeshDataManager * pMeshMgr, CTextureManager * pTextureMgr,
	CMaterialManager * pMaterialMgr, CModelManager* pModelMgr)
{
	// Don't init if already initialised
	if (!m_bInit)
	{
		m_pMeshDataMgr = pMeshMgr;
		m_pTextureMgr = pTextureMgr;
		m_pMaterialMgr = pMaterialMgr;
		m_pModelMgr = pModelMgr;
		m_bInit = true;
	}

	return ERRORID_NONE;
}

CModel * CModelLoader::Load(const std::string & fileDir, const std::string& fileName, const std::string modelID)
{
	CModel* pModel = nullptr;

	if (m_bInit) 
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(fileDir + "\\" + fileName, /*aiProcess_FlipUVs |*/ aiProcess_CalcTangentSpace | aiProcess_Triangulate /*| aiProcess_JoinIdenticalVertices*/
			| aiProcess_SortByPType | aiProcess_OptimizeMeshes | aiProcess_SplitLargeMeshes | aiProcess_FindDegenerates | aiProcess_FindInvalidData | aiProcess_ImproveCacheLocality);
		
		if (scene)
		{
			std::string meshName = modelID + "_";
			aiString texturePath, bumpTexturePath, ambTexturePath, displacementTexturePath;

			// Look for materials
			for (unsigned int mat = 0; mat < scene->mNumMaterials; mat++) {
				const struct aiMaterial* material = scene->mMaterials[mat];

				if (material) {
					material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);
					material->GetTexture(aiTextureType_HEIGHT, 0, &bumpTexturePath);					// HEIGHT is used to retrieve the bump in .obj files formats
					material->GetTexture(aiTextureType_AMBIENT, 0, &ambTexturePath);					// Does nothing
					material->GetTexture(aiTextureType_DISPLACEMENT, 0, &displacementTexturePath);		// Does nothing

					aiString materialName;
					material->Get(AI_MATKEY_NAME, materialName);

					CMaterial newMaterial;
					ErrorId error;
					// Diffuse texture
					if (texturePath.length != 0) 
					{
						error = m_pTextureMgr->LoadTexture(std::string(materialName.C_Str()) + "_diffuse", fileDir + "\\" + std::string(texturePath.C_Str()));
						if (IsNoError(error))
							newMaterial.SetDiffuseTextureID(std::string(materialName.C_Str()) + "_diffuse");
						else
							return nullptr;
					}

					// Normal map texture
					if (bumpTexturePath.length != 0) 
					{
						error = m_pTextureMgr->LoadTexture(std::string(materialName.C_Str()) + "_normal", fileDir + "\\" + std::string(bumpTexturePath.C_Str()));
						if(IsNoError(error))
							newMaterial.SetNormalMapTextureID(std::string(materialName.C_Str()) + "_normal");
						else
							return nullptr;
					}

					error = m_pMaterialMgr->AddMaterial(std::to_string(mat), newMaterial);
					if (IsError(error))
						return nullptr;
				}
			}

			// Create CModel for this
			pModel = m_pModelMgr->CreateModel(modelID);

			for (unsigned int meshNum = 0; meshNum < scene->mNumMeshes; meshNum++) {
				const struct aiMesh* mesh = scene->mMeshes[meshNum];

				unsigned int totalIndices = 0;
				for (glm::uint face = 0; face < (glm::uint)mesh->mNumFaces; face++)
					totalIndices += mesh->mFaces[face].mNumIndices;

				MeshData* pNewMeshData = new MeshData(EVertexType::eVertexPNT, mesh->mNumVertices, totalIndices);

				for (glm::uint vert = 0; vert < (glm::uint)pNewMeshData->vertexCount; vert++) {
					SVertexTypePNT* pVertex = (SVertexTypePNT*)pNewMeshData->pVertices;

					pVertex[vert].position = glm::vec3(mesh->mVertices[vert].x, mesh->mVertices[vert].y, mesh->mVertices[vert].z);
					pVertex[vert].normal = glm::vec3(mesh->mNormals[vert].x, mesh->mNormals[vert].y, mesh->mNormals[vert].z);
					//pVertex[vert].tangent = glm::vec3(mesh->mTangents[vert].x, mesh->mTangents[vert].y, mesh->mTangents[vert].z);
					pVertex[vert].textureCoord = glm::vec2(mesh->mTextureCoords[0][vert].x, mesh->mTextureCoords[0][vert].y);
				}

				unsigned int counter = 0;
				for (unsigned int face = 0; face < mesh->mNumFaces; face++) {
					for (unsigned int idx = 0; idx < mesh->mFaces[face].mNumIndices; idx++) {
						pNewMeshData->pIndices[counter] = mesh->mFaces[face].mIndices[idx];
						counter++;
					}
				}

				const std::string meshMatID = std::to_string(mesh->mMaterialIndex);

				if (mesh->mName.length == 0) {
					std::string meshStr = std::to_string((long double)meshNum);
					m_pMeshDataMgr->AddMeshData(pNewMeshData, meshName + meshStr);
					pModel->AddMesh(pNewMeshData, meshMatID);
					// Finished with meshdata, remove it from memory
					m_pMeshDataMgr->RemoveMeshData(meshName + meshStr);
				}
				else
				{
					m_pMeshDataMgr->AddMeshData(pNewMeshData, mesh->mName.C_Str());
					pModel->AddMesh(pNewMeshData, meshMatID);
					// Finished with meshdata, remove it from memory
					m_pMeshDataMgr->RemoveMeshData(mesh->mName.C_Str());
				}

				if (pNewMeshData)
				{
					delete pNewMeshData;
					pNewMeshData = nullptr;
				}
			}
		}	
	}

	return pModel;
}
