#include "CModelLoaderUTest.h"

CModelLoaderUTest::CModelLoaderUTest()
{
	m_windowName = "CModelLoader test window";
	m_width = 800;
	m_height = 600;
	m_majorVer = 3;
	m_minorVer = 3;
}

CModelLoaderUTest::~CModelLoaderUTest()
{
}

void CModelLoaderUTest::SetUp()
{
	m_app.Initialise(m_windowName, m_width, m_height);
}

void CModelLoaderUTest::TearDown()
{
	m_app.ShutDown();
}

//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------

TEST_F(CModelLoaderUTest, ModelLoad)
{
	bool result = m_app.IsInitialised();
	EXPECT_EQ(result, true) << "Failed to initialise test app";
	if (result)
	{
		ErrorId error = m_app.InitOpenGL(m_majorVer, m_minorVer);
		EXPECT_EQ(ERRORID_NONE, error) << "Failed to initialise OpenGL";
		if (!IsError(error))
		{
			result = m_modelLoader.Initialise(&m_meshDataMgr, &m_textureMgr, &m_materialMgr, &m_modelMgr);
			EXPECT_EQ(result, true) << "Failed to initialise model loader";
			if (result)
			{
				std::string modelDir = "..\\UTest Data\\Models";
				std::string modelFile = "Rabbit.obj";
				std::string modelID = "MyModel";

				CModel* pNewModel = m_modelLoader.Load(modelDir, modelFile, modelID);
				EXPECT_NE(pNewModel, nullptr) << "Failed to load model: " + modelFile;
			}
		}
	}
}

