#include "COpenGLTestApp.h"

//--------------------------------------------------------------------------
// Test Application framework
//--------------------------------------------------------------------------
COpenGLTestApp::COpenGLTestApp()
{
}

COpenGLTestApp::~COpenGLTestApp()
{
}

void COpenGLTestApp::AppRun()
{
}

//--------------------------------------------------------------------------
//
// Test initialise function for unit test.
// Need callback and handle contexts, so written test function here.
//
//--------------------------------------------------------------------------
bool COpenGLTestApp::InitOpenGL(int majorVer, int minorVer)
{
	return m_openGL.InitOpenGL(m_hInstance, &m_hWnd, majorVer, minorVer,
		m_width, m_height, MsgHandlerMain);
}

bool COpenGLTestApp::InitRenderer(int windowWidth, int windowHeight)
{
	return m_renderer.Initialise(m_hInstance, &m_hWnd, windowWidth,
		windowHeight, MsgHandlerMain);
}
