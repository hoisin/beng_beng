#include "CTextureLoaderUTest.h"
#include "GfxDefs.h"
#include "CTextureLoader.h"

//--------------------------------------------------------------------------
// UTest class
//--------------------------------------------------------------------------

CTextureLoaderUTest::CTextureLoaderUTest()
{
	m_windowName = "CTextureLoader test window";
	m_width = 800;
	m_height = 600;
	m_majorVer = 3;
	m_minorVer = 3;
}

CTextureLoaderUTest::~CTextureLoaderUTest()
{
}

void CTextureLoaderUTest::SetUp()
{
	m_testApp.Initialise(m_windowName, m_width, m_height);
}

void CTextureLoaderUTest::TearDown()
{
	m_testApp.ShutDown();
}


//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------

TEST_F(CTextureLoaderUTest, LoadTexture)
{
	bool result = m_testApp.IsInitialised();
	EXPECT_EQ(true, result) << "Failed to initialise test window";
	if (result)
	{
		ErrorId error = m_testApp.InitOpenGL(m_majorVer, m_minorVer);
		EXPECT_EQ(ERRORID_NONE, error) << "Failed to initialise OpenGL";
		if (!IsError(error))
		{
			CTextureLoader textureLoader;
			std::string testFileBMP = "..\\UTest Data\\Textures\\test.bmp";
			std::string testFilePNG = "..\\UTest Data\\Textures\\test.png";
			std::string testFileTARGA = "..\\UTest Data\\Textures\\test.tga";
			int expectWidth = 400;
			int expectHeight = 400;

			unsigned char* pTextureBMP = nullptr;
			unsigned char* pTexturePNG = nullptr;
			unsigned char* pTextureTGA = nullptr;
			unsigned int textureWidth = 0;
			unsigned int textureHeight = 0;
			ETextureFormat textureFormat;
			unsigned int bytesPerPixel = 0;

			// Test load BMP
			error = textureLoader.LoadFile(testFileBMP, textureWidth, textureHeight, textureFormat,
				bytesPerPixel, &pTextureBMP);

			EXPECT_EQ(ERRORID_NONE, error) << "Failed to load BMP texture";
			if (!IsError(error)) 
			{
				EXPECT_EQ(expectWidth, textureWidth) << "Unexpected BMP texture width of " + std::to_string(textureWidth) + " instead of " + std::to_string(expectWidth);
				EXPECT_EQ(expectHeight, textureHeight) << "Unexpected BMP texture height of " + std::to_string(textureHeight) + " instead of " + std::to_string(expectHeight);
				EXPECT_EQ(eTextureFormatBMP, textureFormat) << "Unexpected BMP texture format for loaded BMP";
				EXPECT_EQ(3, bytesPerPixel) << "Unexpected bits per pixel in BMP texture, got " + std::to_string(bytesPerPixel);
			}

			// Reset vars
			textureWidth = 0;
			textureHeight = 0;
			textureFormat = eTextureFormatNone;
			bytesPerPixel = 0;

			// Test load PNG
			error = textureLoader.LoadFile(testFilePNG, textureWidth, textureHeight, textureFormat,
				bytesPerPixel, &pTexturePNG);
			EXPECT_EQ(ERRORID_NONE, error) << "Failed to load PNG texture";
			if (!IsError(error))
			{
				EXPECT_EQ(expectWidth, textureWidth) << "Unexpected PNG texture width of " + std::to_string(textureWidth) + " instead of " + std::to_string(expectWidth);
				EXPECT_EQ(expectHeight, textureHeight) << "Unexpected PNG texture height of " + std::to_string(textureHeight) + " instead of " + std::to_string(expectHeight);
				EXPECT_EQ(eTextureFormatPNG, textureFormat) << "Unexpected PNG texture format for loaded BMP";
				EXPECT_EQ(4, bytesPerPixel) << "Unexpected bits per pixel in PNG texture, got " + std::to_string(bytesPerPixel);
			}

			// Reset vars
			textureWidth = 0;
			textureHeight = 0;
			textureFormat = eTextureFormatNone;
			bytesPerPixel = 0;

			// Test load TGA
			error = textureLoader.LoadFile(testFileTARGA, textureWidth, textureHeight, textureFormat,
				bytesPerPixel, &pTextureTGA);
			EXPECT_EQ(ERRORID_NONE, error) << "Failed to load TGA texture";
			if (!IsError(error))
			{
				EXPECT_EQ(expectWidth, textureWidth) << "Unexpected TGA texture width of " + std::to_string(textureWidth) + " instead of " + std::to_string(expectWidth);
				EXPECT_EQ(expectHeight, textureHeight) << "Unexpected TGA texture height of " + std::to_string(textureHeight) + " instead of " + std::to_string(expectHeight);
				EXPECT_EQ(eTextureFormatTGA, textureFormat) << "Unexpected TGA texture format for loaded BMP";
				EXPECT_EQ(3, bytesPerPixel) << "Unexpected bits per pixel in TGA texture, got " + std::to_string(bytesPerPixel);
			}

			if (pTextureBMP)
			{
				delete[] pTextureBMP;
				pTextureBMP = nullptr;
			}

			if (pTexturePNG)
			{
				delete[] pTexturePNG;
				pTexturePNG = nullptr;
			}

			if (pTextureTGA)
			{
				delete[] pTextureTGA;
				pTextureTGA = nullptr;
			}

			// Test load invalid (null string)
			error = textureLoader.LoadFile("", textureWidth, textureHeight, textureFormat,
				bytesPerPixel, &pTextureTGA);
			EXPECT_EQ(ERRORID_GFX_TEXTURE_LOAD_UNKNOWN_FORMAT, error) << "Expected unknown format error on loading null string";
		}
	}
}