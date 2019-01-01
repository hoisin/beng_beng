#include "CGBuffer.h"

CGBuffer::CGBuffer()
{	
	m_gBuffer = 0;
	m_posBuffer = 0;
	m_normBuffer = 0;
	m_albedoSpecBuffer = 0;
	m_posTex = 0;
	m_normTex = 0;
	m_albedoSpecTex = 0;
	m_bInit = false;
}

CGBuffer::~CGBuffer()
{
}

ErrorId CGBuffer::Initialise(int width, int height)
{
	glGenFramebuffers(1, &m_gBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_gBuffer);

	// Position color buffer
	glGenTextures(1, &m_posTex);
	glBindTexture(GL_TEXTURE_2D, m_posTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_posTex, 0);

	// Normal buffer
	glGenTextures(1, &m_normTex);
	glBindTexture(GL_TEXTURE_2D, m_normTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_normTex, 0);

	// Color and specular buffer
	glGenTextures(1, &m_albedoSpecTex);
	glBindTexture(GL_TEXTURE_2D, m_albedoSpecTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, m_albedoSpecTex, 0);

	m_bInit = true;
	return ERRORID_NONE;
}

void CGBuffer::UseBuffer()
{
	if (m_bInit)
	{
		unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
		glDrawBuffers(3, attachments);
	}
}

void CGBuffer::ShutDown()
{
	if (m_bInit)
	{
		glDeleteFramebuffers(1, &m_posBuffer);
		glDeleteFramebuffers(1, &m_normBuffer);
		glDeleteFramebuffers(1, &m_albedoSpecBuffer);

		glDeleteTextures(1, &m_posTex);
		glDeleteTextures(1, &m_normTex);
		glDeleteTextures(1, &m_albedoSpecTex);

		glDeleteBuffers(1, &m_gBuffer);
	}
}
