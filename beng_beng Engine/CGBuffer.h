//--------------------------------------------------------------------------
//
//	01/01/2019
//
//	GBuffer Buffer
//
//	Author: Matt © 2019
//
//--------------------------------------------------------------------------
#pragma once

#include "GfxDefs.h"
#include "Errors.h"

class CGBuffer
{
public:
	CGBuffer();
	~CGBuffer();

	ErrorId Initialise(int width, int height);
	void UseBuffer();

	void ShutDown();

private:
	GLuint m_gBuffer;

	GLuint m_posBuffer;
	GLuint m_normBuffer;
	GLuint m_albedoSpecBuffer;
	GLuint m_posTex;
	GLuint m_normTex;
	GLuint m_albedoSpecTex;

	bool m_bInit;
};