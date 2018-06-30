#include "CTexture2DUTest.h"
#include "GfxDefs.h"
#include "CTexture2D.h"
#include "CTextureLoader.h"

//--------------------------------------------------------------------------
// UTest class
//--------------------------------------------------------------------------

CTexture2DUTest::CTexture2DUTest()
{
	m_windowName = "CTexture2D test window";
	m_width = 800;
	m_height = 600;
	m_majorVer = 3;
	m_minorVer = 3;
}

CTexture2DUTest::~CTexture2DUTest()
{
}

void CTexture2DUTest::SetUp()
{
	m_testApp.Initialise(m_windowName, m_width, m_height);
}

void CTexture2DUTest::TearDown()
{
	m_testApp.ShutDown();
}


//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------

TEST_F(CTexture2DUTest, LoadTexture)
{
	bool result = m_testApp.IsInitialised();
	EXPECT_EQ(true, result) << "Failed to initialise test app";
	if (result)
	{
		result = m_testApp.InitOpenGL(m_majorVer, m_minorVer);
		EXPECT_EQ(true, result) << "Failed to initialise OpenGL";
		if(result)
		{
			std::string testTextureID = "TestTexture";
			std::string testFileBMP = "..\\UTest Data\\Textures\\test.bmp";
			unsigned int width;
			unsigned int height;
			unsigned int bytesPerPixel;
			ETextureFormat format;
			unsigned char* pTextureData = nullptr;

			CTextureLoader textureLoader;
			CTexture2D testTexture2D(testTextureID);

			// Attempt to load test image
			result = textureLoader.LoadFile(testFileBMP, width, height, format, bytesPerPixel, &pTextureData);
			EXPECT_EQ(true, result) << "Failed to load test BMP texture";
			if (result)
			{
				// Check image info.
				// Should not matter too much unless unsupported format
				EXPECT_EQ(400, width) << "Expected loaded image to have width of 400";
				EXPECT_EQ(400, height) << "Expected loaded image to have height of 400";
				EXPECT_EQ(3, bytesPerPixel) << "Expected loaded image to have 3 bytes per pixel";
				EXPECT_EQ(eTextureFormatBMP, format) << "Expected loaded image to be BMP";

				if (format != eTextureFormatNone)
				{
					result = testTexture2D.LoadTexture(width, height, GL_RGB, GL_BGR, GL_UNSIGNED_BYTE, pTextureData);
					EXPECT_EQ(true, result) << "Failed to load texture to GPU";
					if (result)
					{
						EXPECT_EQ(testTextureID, testTexture2D.GetID()) << "Unexpected ID";
						testTexture2D.CleanUp();
					}
				}

				delete[] pTextureData;
				pTextureData = nullptr;
			}
		}
	}
}