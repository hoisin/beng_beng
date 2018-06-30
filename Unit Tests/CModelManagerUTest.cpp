#include "CModelManagerUTest.h"
#include "GfxDefs.h"
#include "CModelManager.h"
#include "CModel.h"
#include "CMesh.h"

//--------------------------------------------------------------------------
// UTest class
//--------------------------------------------------------------------------

CModelManagerUTest::CModelManagerUTest()
{
	m_windowName = "CModelManager Test Window";
	m_width = 800;
	m_height = 600;
	m_majorVer = 3;
	m_minorVer = 3;
}

CModelManagerUTest::~CModelManagerUTest()
{
}

void CModelManagerUTest::SetUp()
{
	m_testApp.Initialise(m_windowName, m_width, m_height);
}

void CModelManagerUTest::TearDown()
{
	m_testApp.ShutDown();
}


//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------

TEST_F(CModelManagerUTest, CreateModel)
{
	bool result = m_testApp.IsInitialised();
	EXPECT_EQ(true, result) << "Failed to initialise test app";
	if (result)
	{
		result = m_testApp.InitOpenGL(m_majorVer, m_minorVer);
		EXPECT_EQ(true, result) << "Failed to initialise OpenGL";
		if (result)
		{
			CModelManager modelMgr;
			CModel* newModel;

			EXPECT_EQ(0, modelMgr.GetModelCount()) << "Expect 0 models in Mgr before creating any models";

			std::string modelId = "testModel";
			newModel = modelMgr.CreateModel(modelId);
			EXPECT_EQ(1, modelMgr.GetModelCount()) << "Expecting 1 model in mgr after creating model";
			EXPECT_NE(nullptr, newModel) << "Failed to create model with Id: " + modelId;

			// Attempt to create model with same ID
			newModel = modelMgr.CreateModel(modelId);
			EXPECT_EQ(1, modelMgr.GetModelCount()) << "Expecting model count to be 1, CreateModel expected to fail with duplicate ID";
			EXPECT_EQ(nullptr, newModel) << "Expecting null ptr for CreateModel with duplicate ID";

			// Clean up
			modelMgr.CleanUp();
			EXPECT_EQ(0, modelMgr.GetModelCount()) << "Expecting model count to be 0 after clean up";

			// Attempt to re-add model with same ID after clean up
			newModel = modelMgr.CreateModel(modelId);
			EXPECT_NE(nullptr, newModel) << "Model should be created calling CreateModel after clean up";
			EXPECT_EQ(1, modelMgr.GetModelCount()) << "Expecting model count of 1 after Clean up and CreateModel";

			// Final clean up
			modelMgr.CleanUp();
		}
	}
}

TEST_F(CModelManagerUTest, GetTests)
{
	bool result = m_testApp.IsInitialised();
	EXPECT_EQ(true, result) << "Failed to initialise test app";
	if (result)
	{
		result = m_testApp.InitOpenGL(m_majorVer, m_minorVer);
		EXPECT_EQ(true, result) << "Failed to initialise OpenGL";
		if (result)
		{
			CModelManager modelMgr;
			CModel* newModel;

			// Create test models
			int totalModels = 6;
			std::vector<std::string> testModelIDs;
			for (int i = 0; i < totalModels; i++)
			{
				testModelIDs.push_back("TestModel_" + std::to_string(i + 1));
				newModel = modelMgr.CreateModel(testModelIDs[i]);
				EXPECT_NE(nullptr, newModel) << "Failed to create model test: " + testModelIDs[i];
			}

			// Test gets
			EXPECT_EQ(totalModels, modelMgr.GetModelCount()) << "Expected " + std::to_string(totalModels) + " total models in manager";

			for (int j = 0; j < totalModels; j++)
			{
				// Test Get via IDs
				newModel = modelMgr.GetModel(testModelIDs[j]);
				EXPECT_NE(nullptr, newModel) << "Failed to get model: " + testModelIDs[j] + " using Get via ID";

				// Test Get via index
				newModel = modelMgr.GetModel(j);
				EXPECT_NE(nullptr, newModel) << "Failed to get model: " + testModelIDs[j] + " using Get via index";
			}

			// Invalid tests
			newModel = modelMgr.GetModel("");
			EXPECT_EQ(nullptr, newModel) << "Expected null ptr on get with null string";

			newModel = modelMgr.GetModel("NotValidModelID");
			EXPECT_EQ(nullptr, newModel) << "Expected null ptr on get with invalid ID";

			newModel = modelMgr.GetModel(999);
			EXPECT_EQ(nullptr, newModel) << "Expected null ptr on get with invalid index";

			// End of tests
			modelMgr.CleanUp();
		}
	}
}