#include "CAssetManagerUTest.h"
#include "CAssetManager.h"
#include "CMaterial.h"

//--------------------------------------------------------------------------
// UTest class
//--------------------------------------------------------------------------
CAssetManagerUTest::CAssetManagerUTest()
{
	m_windowName = "AssetMgr test window";
	m_width = 800;
	m_height = 600;
	m_majorVer = 3;
	m_minorVer = 3;
}

CAssetManagerUTest::~CAssetManagerUTest()
{
}

void CAssetManagerUTest::SetUp()
{
	m_testApp.Initialise(m_windowName, m_width, m_height);
}

void CAssetManagerUTest::TearDown()
{
	m_testApp.ShutDown();
}


//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------

TEST_F(CAssetManagerUTest, ManagerTest)
{
	bool result = m_testApp.IsInitialised();
	EXPECT_EQ(true, result) << "Failed to initialise testApp setup";
	if (result)
	{
		ErrorId error = m_testApp.InitOpenGL(m_majorVer, m_minorVer);
		EXPECT_EQ(ERRORID_NONE, error) << "Failed to initialise OpenGL";
		if (!IsError(error))
		{
			// Initialise asset maanger
			result = ASSETMGR->Initialise();

			if (result)
			{
				// Test loading shader
				std::string vertexShaderPath = "..\\UTest Data\\Shaders\\texturePointVertexShader.vsh";
				std::string fragmentShaderPath = "..\\UTest Data\\Shaders\\texturePointFragmentShader.fsh";

				EXPECT_EQ(true, ASSETMGR->LoadTechnique(vertexShaderPath, fragmentShaderPath)) << "Failed to load technique";
				EXPECT_NE(nullptr, ASSETMGR->GetFwdRenderTech()) << "Should not return nullptr after successful LoadTechnique";

				// Test loading textures
				std::string testTexturePath = "..\\UTest Data\\Textures\\test.bmp";
				std::string textureID = "MyTexture";

				EXPECT_EQ(true, ASSETMGR->LoadTexture(testTexturePath, textureID)) << "Failed to load texture: " + testTexturePath;
				EXPECT_NE(nullptr, ASSETMGR->GetTexture(textureID)) << "Should not return nullptr after LoadTexture";

				// Test adding materials
				CMaterial testMaterial;
				std::string testMaterialID = "MyMaterial";
				EXPECT_EQ(true, ASSETMGR->AddMaterial(testMaterial, testMaterialID)) << "Failed to add material";
				EXPECT_NE(nullptr, ASSETMGR->GetMaterial(testMaterialID)) << "Should not return nullptr after AddMaterial";

				// Can't test LoadModelMeshData yet....

				// Test creating procedural meshdata
				std::string testMeshCube = "MyCube";
				std::string testMeshSphere = "MySphere";
				std::string testMeshPlane = "MyPlane";

				EXPECT_EQ(true, ASSETMGR->CreateCubeMeshData(10, 2, EVertexType::eVertexPNC, testMeshCube)) << "Failed to create cube mesh data";
				EXPECT_EQ(true, ASSETMGR->CreateSphereMeshData(10, 2, EVertexType::eVertexPNC, testMeshSphere)) << "Failed to create sphere mesh data";
				EXPECT_EQ(true, ASSETMGR->CreatePlaneMeshData(10, 2, EVertexType::eVertexPNC, testMeshPlane)) << "Failed to create plane mesh data";

				EXPECT_NE(nullptr, ASSETMGR->GetMeshData(testMeshCube)) << "Unexpected null ptr for Get test mesh data cube";
				EXPECT_NE(nullptr, ASSETMGR->GetMeshData(testMeshSphere)) << "Unexpected null ptr for Get test mesh data sphere";
				EXPECT_NE(nullptr, ASSETMGR->GetMeshData(testMeshPlane)) << "Unexpected null ptr for Get test mesh data plane";

				// Test model creation
				std::string testModelID = "MyModel";
				EXPECT_EQ(true, ASSETMGR->CreateModel(testModelID)) << "Failed to create model";
				EXPECT_NE(nullptr, ASSETMGR->GetModel(testModelID)) << "Unexpected null ptr on get model";

				// Atttempt to add mesh data to model to create a mesh for the model

				error = ASSETMGR->AddMeshToModel(testModelID, testMeshCube, testMaterialID);
				EXPECT_EQ(ERRORID_NONE, error) << "Failed to add mesh to model";
				error = ASSETMGR->AddMeshToModel(testModelID, testMeshPlane, testMaterialID);
				EXPECT_EQ(ERRORID_NONE, error) << "Failed to add mesh to model";

				// Test model creation methods.
				// Removes the need to create mesh data and then linking them to a model (does it all in one)
				std::string modelCustom = "Custom_Model";
				std::string modelCube = "Cube_Model";
				std::string modelSphere = "Sphere_Model";
				std::string modelPlane = "Plane_Model";

				std::string modelDir = "..\\UTest Data\\Models";
				std::string modelFile = "Rabbit.obj";

				EXPECT_EQ(true, ASSETMGR->LoadModel(modelDir, modelFile, modelCustom)) << "Failed to LoadModel()";
				error = ASSETMGR->CreateModelCube(10, 2, eVertexPNT, modelCube, testMaterialID);
				EXPECT_EQ(ERRORID_NONE, error) << "Failed to create Cube model";
				error = ASSETMGR->CreateModeSphere(10, 2, eVertexPNT, modelSphere, testMaterialID);
				EXPECT_EQ(ERRORID_NONE, error) << "Failed to create sphere model";
				error = ASSETMGR->CreateModelPlane(10, 2, eVertexPNT, modelPlane, testMaterialID);
				EXPECT_EQ(ERRORID_NONE, error) << "Failed to create plane model";
			}

			// Close the AssetMgr instance
			ASSETMGR->ShutDown();
		}
	}
}
