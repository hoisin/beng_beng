//--------------------------------------------------------------------------
//
//	26/11/2017
//
//	OpenGL test app framework for unit tests as well as Base class test
//   since we cannot instantiate it.
//  This isn't a unit test
//	i.e. OpenGL initialisation to use OpenGL methods
//
//	Author: Matt © 2017
//
//--------------------------------------------------------------------------
#pragma once

#include "COpenGL.h"
#include "CRenderer.h"
#include "CBaseApp.h"

// Create test app framework for testing
class COpenGLTestApp : public CBaseApp
{
public:
	COpenGLTestApp();
	~COpenGLTestApp();

	void AppRun() override;

	// Test function
	ErrorId InitOpenGL(int majorVer, int minorVer);

	ErrorId InitRenderer(int windowWidth, int windowHeight);

public:
	COpenGL m_openGL;
	CRenderer m_renderer;
};