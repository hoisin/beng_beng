//--------------------------------------------------------------------------
//
//	14/04/2014
//
//	Texture class handling texture loading storing OpenGL handle to it.
//	Note: Does not store the actual image data.
//
//	TO DO: Add more texture operations such as more filter options, mip maps, etc..
//
//	Author: Matt © 2014
//
//--------------------------------------------------------------------------

#ifndef __CTEXTURE2D_H__
#define __CTEXTURE2D_H__


#include <gl/glew.h>
#include <gl/wglew.h>
#include <string>

class CTexture2D
{
public:
	CTexture2D(const std::string& textureID);
	CTexture2D(const CTexture2D& other);
	~CTexture2D();

	bool LoadTexture(unsigned int width, unsigned int height, GLint internalFormat,
		GLint texFormat, GLenum dataType, unsigned char *pData);

	void UseTexture();

	GLuint GetTexture() const;

	const std::string& GetID() const;

	void CleanUp();

private:
	std::string m_ID;
	GLuint m_textureHandle;
};


#endif