#include "COpenGLUTest.h"

//--------------------------------------------------------------------------
// UTest class
//--------------------------------------------------------------------------
COpenGLUTest::COpenGLUTest()
{
	m_windowName = "OpenGL test window";
	m_width = 800;
	m_height = 600;
	m_majorVer = 3;
	m_minorVer = 3;
}

COpenGLUTest::~COpenGLUTest()
{
}

void COpenGLUTest::SetUp()
{

	m_testApp.Initialise(m_windowName, m_width, m_height);
}

void COpenGLUTest::TearDown()
{
	m_testApp.ShutDown();
}



//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------

TEST_F(COpenGLUTest, Initialise)
{
	// Invoke test function
	bool result = m_testApp.IsInitialised();
	EXPECT_EQ(true, result) << "Failed to initialise testApp setup";
	if (result)
	{
		ErrorId error = m_testApp.InitOpenGL(m_majorVer, m_minorVer);
		EXPECT_EQ(ERRORID_NONE, error) << "Failed to initialise OpenGL";
	}
}

TEST_F(COpenGLUTest, ResizeViewPort)
{
	bool result = m_testApp.IsInitialised();
	EXPECT_EQ(true, result) << "Failed to initialise testApp setup";
	if (result)
	{
		// Test invalid resize
		ErrorId error = m_testApp.m_openGL.ResizeOpenGLViewportFull();
		EXPECT_EQ(ERRORID_GFX_NULL_HWND, error) << "Expected error when resize without initialise";

		// Test resize of viewport
		error = m_testApp.InitOpenGL(m_majorVer, m_minorVer);
		EXPECT_EQ(ERRORID_NONE, error) << "Failed to initialise OpenGL";
		if (!IsError(error))
		{
			COpenGL* openGL = &m_testApp.m_openGL;
			error = openGL->ResizeOpenGLViewportFull();
			EXPECT_EQ(ERRORID_NONE, error) << "Failed to reisze viewport";
		}
	}
}

TEST_F(COpenGLUTest, GetTests)
{
	bool result = m_testApp.IsInitialised();
	EXPECT_EQ(true, result) << "Failed to initialise testApp setup";
	if (result)
	{
		// Initialise OpenGL
		ErrorId error = m_testApp.InitOpenGL(m_majorVer, m_minorVer);
		EXPECT_EQ(ERRORID_NONE, error) << "Failed to initialise OpenGL";
		if (!IsError(error))
		{
			COpenGL* openGL = &m_testApp.m_openGL;
			EXPECT_EQ(m_width, openGL->GetScreenWidth()) << "Unexpected screen width, expected: " + std::to_string(m_width) +
				" got: " + std::to_string(openGL->GetScreenWidth());
			EXPECT_EQ(m_height, openGL->GetScreenHeight()) << "Unexpected screen height, expected: " + std::to_string(m_height) +
				" got: " + std::to_string(openGL->GetScreenHeight());
		}
	}
}