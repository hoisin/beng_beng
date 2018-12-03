#include "CRendererUTest.h"
#include "CRenderer.h"

//--------------------------------------------------------------------------
// UTest class
//--------------------------------------------------------------------------

CRendererUTest::CRendererUTest()
{
	m_windowName = "CRenderer test window";
	m_width = 800;
	m_height = 600;
	m_majorVer = 3;
	m_minorVer = 3;
}

CRendererUTest::~CRendererUTest()
{
}

void CRendererUTest::SetUp()
{
	m_testApp.Initialise(m_windowName, m_width, m_height);
}

void CRendererUTest::TearDown()
{
	m_testApp.ShutDown();
}


//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------

TEST_F(CRendererUTest, BasicTest)
{
	bool result = m_testApp.IsInitialised();
	EXPECT_EQ(true, result) << "Failed to initialise test app";
	if (result)
	{
		// Test renderer part of the OpenGL test app due to the need for the callback function
		ErrorId error = m_testApp.InitRenderer(m_width, m_height);
		EXPECT_EQ(ERRORID_NONE, error) << "Failed to initialise the renderer";
		if (IsNoError(error))
		{
			int testWidth = m_testApp.m_renderer.GetScreenWidth();
			int testHeight = m_testApp.m_renderer.GetScreenHeight();

			EXPECT_EQ(m_width, testWidth) << "Unexpected set width in renderer";
			EXPECT_EQ(m_height, testHeight) << "Unexpected set height in renderer";
		}
	}
}
