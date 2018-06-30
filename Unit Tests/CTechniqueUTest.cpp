#include "CTechniqueUTest.h"
#include "GfxDefs.h"
#include "CTechnique.h"

//--------------------------------------------------------------------------
// UTest class
//--------------------------------------------------------------------------

CTechniqueUTest::CTechniqueUTest()
{
	m_windowName = "CTechique test window";
	m_width = 800;
	m_height = 600;
	m_majorVer = 3;
	m_minorVer = 3;
}

CTechniqueUTest::~CTechniqueUTest()
{
}

void CTechniqueUTest::SetUp()
{
	m_testApp.Initialise(m_windowName, m_width, m_height);
}

void CTechniqueUTest::TearDown()
{
	m_testApp.ShutDown();
}


//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------

TEST_F(CTechniqueUTest, Initialise)
{
	bool result = m_testApp.IsInitialised();
	EXPECT_EQ(true, result) << "Failed to initialise test window";
	if (result)
	{
		result = m_testApp.InitOpenGL(m_majorVer, m_minorVer);
		EXPECT_EQ(true, result) << "Failed to initialise OpenGL";
		if (result)
		{
			CTechnique testShader;
			result = testShader.VInit();
			EXPECT_EQ(true, result) << "Failed to initialise";
		}
	}
}