//--------------------------------------------------------------------------
//
//	Texture Manager. Handles texture loading from file.
//	Supports BMP, TGA, PNG
//
//--------------------------------------------------------------------------

#include "CTextureManager.h"
#include "CTexture2D.h"
#include "CTextureLoader.h"
#include <string>


CTextureManager::CTextureManager(void)
{
}


CTextureManager::~CTextureManager(void)
{
	CleanUp();
}

//------------------------------------------------------------------
//
//	LoadTexture(..)
//
//	Params:
//	textureId	-	Assigned textured ID
//	textureFile	-	Directory to texture
//
//	Loads texture from file, then uploaded to GPU creating a texture
//	instance
//
//------------------------------------------------------------------
ErrorId CTextureManager::LoadTexture(const std::string& textureID, const std::string& textureFile)
{
	if (textureID == "")
		return ERRORID_TEXTURE2D_ID_NULL;

	if (ExistingTextureCheck(textureID))
		return ERRORID_TEXTURE2D_ID_ALREADY_IN_USE;

	unsigned int width = 0, height = 0;
	unsigned char* pTextureData = 0;
	ETextureFormat eTexFormat = eTextureFormatNone;
	unsigned int bpp = 0;
	CTexture2D newTexture(textureID);

	ErrorId error = m_pTextureLoader.LoadFile(textureFile, width, height, eTexFormat, bpp, &pTextureData);

	// Try to load texture file into memory
	if (IsNoError(error)) 
	{
		// On success, upload loaded texture to OpenGL
		//
		// For now we assume bits per pixel only range from 1 and 3
		switch (eTexFormat)
		{
		case eTextureFormatBMP:
			if (bpp == 1) {
				error = newTexture.LoadTexture(width, height, GL_LUMINANCE, GL_RED, GL_UNSIGNED_BYTE, pTextureData);
			}
			else {
				error = newTexture.LoadTexture(width, height, GL_RGB, GL_BGR, GL_UNSIGNED_BYTE, pTextureData);
			}
			break;

		case eTextureFormatTGA:
			if (bpp == 1) {
				error = newTexture.LoadTexture(width, height, GL_LUMINANCE, GL_RED, GL_UNSIGNED_BYTE, pTextureData);
			}
			else {
				error = newTexture.LoadTexture(width, height, GL_RGB, GL_BGR, GL_UNSIGNED_BYTE, pTextureData);
			}
			break;

		case eTextureFormatPNG:
			if (bpp == 1) {
				error = newTexture.LoadTexture(width, height, GL_LUMINANCE, GL_RED, GL_UNSIGNED_BYTE, pTextureData);
			}
			else {
				error = newTexture.LoadTexture(width, height, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, pTextureData);
			}
			break;

		default:
			// Unsupported texture format
			error = ERRORID_TEXTURE2D_UNSUPPORTED_FORMAT;
			break;
		}

		// Check if supported format
		if (IsNoError(error)) {
			m_textures.push_back(newTexture);

			// Clean up loaded data
			if (pTextureData) {
				delete[] pTextureData;
				pTextureData = nullptr;
			}
		}
	}

	return error;
}

//------------------------------------------------------------------
//
//	GetTexture(..)
//
//	Params:
//	textureId	-	ID of texture to return
//
//	Gets specified texture, returns nullptr if failed
//
//------------------------------------------------------------------
CTexture2D* CTextureManager::GetTexture(const std::string& textureID)
{
	for (int i = 0; i < (int)m_textures.size(); i++) {
		if (m_textures[i].GetID() == textureID)
			return &m_textures[i];
	}

	return nullptr;
}

//------------------------------------------------------------------
//
//	CleanUp(..)
//
//	Free memory allocations
//
//------------------------------------------------------------------
void CTextureManager::CleanUp()
{
	// Free loaded textures
	for (int i = 0; i < (int)m_textures.size(); i++)
		m_textures[i].CleanUp();

	m_textures.clear();
}

//------------------------------------------------------------------
//
//	CleanUp(..)
//
//	Params:
//	textureID	-	 ID to check
//
//	Checks if already and entry with ID
//
//------------------------------------------------------------------
bool CTextureManager::ExistingTextureCheck(const std::string & textureID)
{
	for (int i = 0; i < (int)m_textures.size(); i++) {
		if (m_textures[i].GetID() == textureID)
			return true;
	}
	return false;
}
