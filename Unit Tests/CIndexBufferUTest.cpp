#include "CIndexBufferUTest.h"
#include "CIndexBuffer.h"


//--------------------------------------------------------------------------
// UTest class
//--------------------------------------------------------------------------
CIndexBufferUTest::CIndexBufferUTest()
{
	m_windowName = "CIndexBuffer test window";
	m_width = 800;
	m_height = 600;
	m_majorVer = 3;
	m_minorVer = 3;
}


CIndexBufferUTest::~CIndexBufferUTest()
{
}

void CIndexBufferUTest::SetUp()
{
	m_testApp.Initialise(m_windowName, m_width, m_height);
}

void CIndexBufferUTest::TearDown()
{
	m_testApp.ShutDown();
}



//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------
TEST_F(CIndexBufferUTest, LoadBufferData)
{
	bool result = m_testApp.IsInitialised();
	EXPECT_EQ(true, result) << "Failed to initialise testApp setup";
	if (result)
	{
		result = m_testApp.InitOpenGL(m_majorVer, m_minorVer);
		EXPECT_EQ(true, result) << "Failed to initialise OpenGL";
		if (result)
		{
			glm::uint32 indexCount = 12;
			glm::uint32* pIdxBuffer = new glm::uint32[indexCount];
			memset(pIdxBuffer, 1, sizeof(glm::uint32) * indexCount);

			// Valid test
			std::string bufferID = "TestIdxBuffer";
			CIndexBuffer idxBuffer;
			EXPECT_EQ(false, idxBuffer.IsLoadedData()) << "Expected loaded data to be false before loading!";

			EXPECT_EQ(true, idxBuffer.LoadData(pIdxBuffer, indexCount)) << "Failed to load index buffer";
			EXPECT_EQ(true, idxBuffer.IsLoadedData()) << "Expected loaded data to be true after loading!";
			EXPECT_NE(0, idxBuffer.GetElementBuffer()) << "Element buffer ID 0 after loading!";
			EXPECT_NE(0, idxBuffer.GetIndexCount()) << "Index count 0 after loading!";

			// Unload test
			idxBuffer.ShutDown();
			EXPECT_EQ(0, idxBuffer.GetElementBuffer()) << "Expected element buffer to be 0 after unload";
			EXPECT_EQ(0, idxBuffer.GetIndexCount()) << "Expected index count to be 0 after unload";
			EXPECT_EQ(false, idxBuffer.IsLoadedData()) << "Expected loaded data to be false after unloading!";

			// Invalid load
			EXPECT_EQ(false, idxBuffer.LoadData(nullptr, indexCount)) << "Expected load fail on null pointer data";
			EXPECT_EQ(false, idxBuffer.LoadData(pIdxBuffer, 0)) << "Expected load fail on 0 index count";

			// Clean up
			delete[] pIdxBuffer;
			pIdxBuffer = nullptr;
		}
	}
}