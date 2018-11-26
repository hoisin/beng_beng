#include "CTexture2D.h"

CTexture2D::CTexture2D(const std::string& textureID) : m_ID(textureID), m_textureHandle(0)
{
}

CTexture2D::CTexture2D(const CTexture2D & other)
{
	m_ID = other.m_ID;
	m_textureHandle = other.m_textureHandle;
}


CTexture2D::~CTexture2D()
{
}


//------------------------------------------------------------------------------
//
//	LoadTexture(..)
//
//	Params:
//	width			-	Width of the texture
//	height			-	Height of the texture
//	internalFormat	-	Format to use for OpenGL
//	texFormat		-	The format used in stored texture
//	dataType		-	Type of data for each pixel
//	pData			-	Pointer to texture data
//
//	Uses loaded texture in memory to create a texture handle in OpenGL.
//	Texture is loaded into GPU memory.
//
//------------------------------------------------------------------------------
ErrorId CTexture2D::LoadTexture(unsigned int width, unsigned int height, GLint internalFormat,
	GLint texFormat, GLenum dataType, unsigned char *pData)
{
	glGenTextures(1, &m_textureHandle);

	glBindTexture(GL_TEXTURE_2D, m_textureHandle);

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, texFormat, 
		dataType, pData);

	// Standard texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glGenerateMipmap(GL_TEXTURE_2D);

	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);*/

	glBindTexture(GL_TEXTURE_2D, 0);

	return ERRORID_NONE;
}

//------------------------------------------------------------------------------
//
//	UseTexture(..)
//
//	Sets this texture to be used currently
//
//------------------------------------------------------------------------------
void CTexture2D::UseTexture()
{
	// Release any previous textures
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, m_textureHandle);
}

GLuint CTexture2D::GetTexture() const
{
	return m_textureHandle;
}

//------------------------------------------------------------------------------
//
//	GetID(..)
//
//	Returns texture ID
//
//------------------------------------------------------------------------------
const std::string & CTexture2D::GetID() const
{
	return m_ID;
}

//------------------------------------------------------------------------------
//
//	LoadTexture(..)
//
//	Cleans up
//
//------------------------------------------------------------------------------
void CTexture2D::CleanUp()
{
	if(m_textureHandle) {
		glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteTextures(1, &m_textureHandle);
	}
}