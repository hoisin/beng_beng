#include "CBaseAppUTest.h"
//--------------------------------------------------------------------------
// Local globals
//--------------------------------------------------------------------------
const std::string g_windowName = "Test Window";
int g_windowWidth = 800;
int g_windowHeight = 600;

CBaseAppUTest::CBaseAppUTest()
{
}

CBaseAppUTest::~CBaseAppUTest()
{
}

void CBaseAppUTest::SetUp()
{
	// Assumption of no failure
	m_testApp.Initialise(g_windowName, g_windowWidth, g_windowHeight);
}

void CBaseAppUTest::TearDown()
{
	m_testApp.ShutDown();
}

//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------

// Testing initialise
TEST(CBaseApp, Initialise)
{
	std::string windowName = "Local Test Window";
	int width = g_windowWidth;
	int height = g_windowHeight;
	COpenGLTestApp appTest;

	EXPECT_EQ(false, appTest.IsInitialised()) << "Expected IsInitialised() to return false when initialise has not yet ran!";

	ErrorId result = appTest.Initialise(windowName, width, height);
	EXPECT_EQ(ERRORID_NONE, result) << "Failed to initialise app";
	EXPECT_EQ(true, appTest.IsInitialised()) << "Expected IsInitialised() to return true after initialise has ran!";
	appTest.ShutDown();

	// Invalid tests
	result = appTest.Initialise("", width, height);
	std::string appWindowName = appTest.GetWindowName();
	appTest.ShutDown();
	EXPECT_EQ(ERRORID_NONE, result) << "Expected app to initialise even with empty window title";
	EXPECT_EQ(DEFAULT_WINDOW_TITLE, appWindowName) << "Expected app window name to be default window name when emtpy window title specified";

	result = appTest.Initialise(windowName, 0, height);
	EXPECT_EQ(ERRORID_APP_INIT_INVALID_WINDOW_WIDTH_HEIGHT, result) << "Expected error with width of 0";
	
	result = appTest.Initialise(windowName, width, 0);
	EXPECT_EQ(ERRORID_APP_INIT_INVALID_WINDOW_WIDTH_HEIGHT, result) << "Expected error with height of 0";
	
}

// Class fixture testing
TEST_F(CBaseAppUTest, GetTests)
{
	EXPECT_EQ(true, m_testApp.IsInitialised()) << "Expected IsInitialised() to return true after app has been initialised";

	EXPECT_EQ(g_windowName, m_testApp.GetWindowName())
		<< "Incorrect window name, expected: " + g_windowName + ", got: " + m_testApp.GetWindowName();

	std::string windowClassName = g_windowName + "App";
	EXPECT_EQ(windowClassName, m_testApp.GetWindowClassName())
		<< "Incorrect class name, expected: " + windowClassName + ", got: " + m_testApp.GetWindowClassName();

	EXPECT_EQ(g_windowWidth, m_testApp.GetWindowWidth())
		<< "Incorrect window width, expected: " + std::to_string(g_windowWidth) + ", got: " + std::to_string(m_testApp.GetWindowWidth());

	EXPECT_EQ(g_windowHeight, m_testApp.GetWindowHeight())
		<< "Incorrect window height, expected: " + std::to_string(g_windowHeight) + ", got:" + std::to_string(m_testApp.GetWindowHeight());

	EXPECT_EQ(nullptr, m_testApp.GetHInstance())
		<< "Expected null for app hInstance";

	EXPECT_NE(nullptr, m_testApp.GetMutex())
		<< "Unexpected null for app mutex";
}