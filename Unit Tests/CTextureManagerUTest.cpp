#include "CTextureManagerUTest.h"
#include "CTextureManager.h"

//--------------------------------------------------------------------------
// UTest class
//--------------------------------------------------------------------------

CTextureManagerUTest::CTextureManagerUTest()
{
	m_windowName = "CTextureManager test window";
	m_width = 800;
	m_height = 600;
	m_majorVer = 3;
	m_minorVer = 3;
}

CTextureManagerUTest::~CTextureManagerUTest()
{
}

void CTextureManagerUTest::SetUp()
{
	m_testApp.Initialise(m_windowName, m_width, m_height);
}

void CTextureManagerUTest::TearDown()
{
	m_testApp.ShutDown();
}


//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------

TEST_F(CTextureManagerUTest, LoadTextures)
{
	bool result = m_testApp.IsInitialised();
	EXPECT_EQ(true, result) << "Failed to initialise test app";
	if (result)
	{
		ErrorId error = m_testApp.InitOpenGL(m_majorVer, m_minorVer);
		EXPECT_EQ(ERRORID_NONE, error) << "Failed to initialise OpenGL";
		if (!IsError(error))
		{
			int totalTextures = 10;
			std::vector<std::string> textureIDs;
			std::string  textureFile = "..\\UTest Data\\Textures\\test.bmp";

			CTextureManager textureMgr;
			
			// Test loading 'totalTextures' number of textures into GPU
			for (int i = 0; i < totalTextures; i++)
			{
				textureIDs.push_back("texture_" + std::to_string(i + 1));
				result = textureMgr.LoadTexture(textureIDs[i], textureFile);
				EXPECT_EQ(true, result) << "Failed to load texture: " + textureIDs[i];
			}

			// If no failures in loading
			if (result) 
			{
				// Test creating duplicate
				result = textureMgr.LoadTexture(textureIDs[0], textureFile);
				EXPECT_EQ(false, result) << "Expected to fail on creating texture with the same ID";

				// Test invalid texture file location
				result = textureMgr.LoadTexture("TestTexture", "");
				EXPECT_EQ(false, result) << "Expected to fail on creating texture with invalid file";
			}

			textureMgr.CleanUp();
		}
	}
}


TEST_F(CTextureManagerUTest, GetTextures)
{
	bool result = m_testApp.IsInitialised();
	EXPECT_EQ(true, result) << "Failed to initialise test app";
	if (result)
	{
		ErrorId error = m_testApp.InitOpenGL(m_majorVer, m_minorVer);
		EXPECT_EQ(ERRORID_NONE, error) << "Failed to initialise OpenGL";
		if (!IsError(error))
		{
			CTextureManager textureMgr;
			int totalTextures = 20;
			std::string fileName = "..\\UTest Data\\Textures\\test.bmp";
			std::vector<std::string> textureIDs;

			for (int i = 0; i < totalTextures; i++)
			{
				textureIDs.push_back("texture_" + std::to_string(i + 1));
				result = textureMgr.LoadTexture(textureIDs[i], fileName);
				EXPECT_EQ(true, result) << "Failed to load texture: " + textureIDs[i];
			}

			// Test access
			for (int j = 0; j < totalTextures; j++)
			{
				CTexture2D* texture = textureMgr.GetTexture(textureIDs[j]);
				EXPECT_NE(nullptr, texture) << "Failed to find loaded texture: " + textureIDs[j];
			}

			textureMgr.CleanUp();
		}
	}
}