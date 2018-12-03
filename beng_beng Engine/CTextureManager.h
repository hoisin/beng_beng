//--------------------------------------------------------------------------
//
//	Texture Manager. Handles texture loading from file.
//	Supports BMP, TGA, PNG
//
//--------------------------------------------------------------------------

#ifndef __CTEXTUREMANGER_H__
#define __CTEXTUREMANGER_H__

#include "CTextureLoader.h"
#include <map>
#include "Errors.h"

class CTexture2D;

class CTextureManager
{
public:
	CTextureManager(void);
	~CTextureManager(void);

	ErrorId LoadTexture(const std::string& textureID, const std::string& texureFile);
	
	CTexture2D* GetTexture(const std::string &textureID);

	void CleanUp();
	
protected:
	bool ExistingTextureCheck(const std::string& textureID);

private:
	std::vector<CTexture2D> m_textures;
	CTextureLoader m_pTextureLoader;
};

#endif