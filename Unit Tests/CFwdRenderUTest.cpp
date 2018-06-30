#include "CFwdRenderUTest.h"
#include "GfxDefs.h"
#include "CFwdRender.h"

//--------------------------------------------------------------------------
// UTest class
//--------------------------------------------------------------------------

CFwdRenderUTest::CFwdRenderUTest()
{
	m_windowName = "CFwdRender test window";
	m_width = 800;
	m_height = 600;
	m_majorVer = 3;
	m_minorVer = 3;
}

CFwdRenderUTest::~CFwdRenderUTest()
{
}

void CFwdRenderUTest::SetUp()
{
	m_testApp.Initialise(m_windowName, m_width, m_height);
}

void CFwdRenderUTest::TearDown()
{
	m_testApp.ShutDown();
}


//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------

TEST_F(CFwdRenderUTest, Initialise)
{
	bool result = m_testApp.IsInitialised();
	EXPECT_EQ(true, result) << "Failed to initialise test window";
	if (result)
	{
		result = m_testApp.InitOpenGL(m_majorVer, m_minorVer);
		EXPECT_EQ(true, result) << "Failed to initialise OpenGL";
		if (result)
		{
			std::string vertexShaderPath = "..\\UTest Data\\Shaders\\texturePointVertexShader.vsh";
			std::string fragmentShaderPath = "..\\UTest Data\\Shaders\\texturePointFragmentShader.fsh";

			CFwdRender testShader(vertexShaderPath, fragmentShaderPath);
			result = testShader.VInit();
			EXPECT_EQ(true, result) << "Failed to initialise";

			// Invalid test
			CFwdRender invalidShader("", "");
			result = invalidShader.VInit();
			EXPECT_EQ(false, result) << "Expected invalid shader to fail";
		}
	}
}

TEST_F(CFwdRenderUTest, Constructors)
{
	// Testing operator and constructor tests
	//
	// Copy c'tor and = operator should only copy the vertex/fragment path directory.
	// User needs to call the VInit() to properly load the shader after.

	CFwdRender testRender;

	EXPECT_EQ("", testRender.GetVertexShaderPath()) << "Expected null string for vertex shader path on default c'tor";
	EXPECT_EQ("", testRender.GetFragmentShaderPath()) << "Expected null string for fragment shader path on default c'tor";

	std::string vertFile = "C:/TestDir/Test.vsh";
	std::string fragFile = "C:/TestDor/Test.fsh";
	testRender = CFwdRender(vertFile, fragFile);

	EXPECT_EQ(vertFile, testRender.GetVertexShaderPath()) << "Expected to match vertex file path on operator =";
	EXPECT_EQ(fragFile, testRender.GetFragmentShaderPath()) << "Expected to match fragment file path on operator =";
	EXPECT_EQ(false, testRender.IsInit()) << "Expected not to be initialised";

	CFwdRender copyTest(testRender);

	EXPECT_EQ(vertFile, copyTest.GetVertexShaderPath()) << "Expected to match vertex file path on copy c'tor";
	EXPECT_EQ(fragFile, copyTest.GetFragmentShaderPath()) << "Expected to match fragment file path on copy c'tor";
	EXPECT_EQ(false, copyTest.IsInit()) << "Expected not to be initialised";

}