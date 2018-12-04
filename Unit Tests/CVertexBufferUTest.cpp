#include "CVertexBufferUTest.h"
#include "GfxDefs.h"
#include "CVertexBuffer.h"

//--------------------------------------------------------------------------
// UTest class
//--------------------------------------------------------------------------

CVertexBufferUTest::CVertexBufferUTest()
{
	m_windowName = "Vertex Buffer Test Window";
	m_width = 800;
	m_height = 600;
	m_majorVer = 3;
	m_minorVer = 3;
}

CVertexBufferUTest::~CVertexBufferUTest()
{
}

void CVertexBufferUTest::SetUp()
{
	m_testApp.Initialise(m_windowName, m_width, m_height);
}

void CVertexBufferUTest::TearDown()
{
	m_testApp.ShutDown();
}


//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------

TEST_F(CVertexBufferUTest, LoadBufferData)
{
	bool result = m_testApp.IsInitialised();
	EXPECT_EQ(true, result) << "Failed to initialise testApp setup";
	if (result)
	{
		ErrorId error = m_testApp.InitOpenGL(m_majorVer, m_minorVer);
		EXPECT_EQ(ERRORID_NONE, error) << "Failed to initialise OpenGL";
		if (!IsError(error))
		{
			int vertexCount = 9;
			SVertexTypePNT* pVerts = new SVertexTypePNT[vertexCount];

			std::string bufferID = "TestBuffer";
			CVertexBuffer vertexBuffer;

			EXPECT_EQ(false, vertexBuffer.IsLoadedData()) << "Expected loaded data to be false when not loaded yet!";

			ErrorId error = vertexBuffer.LoadData(pVerts, vertexCount, eVertexPNT);
			EXPECT_EQ(ERRORID_NONE, error) << "Failed to load vertex data";
			EXPECT_EQ(true, vertexBuffer.IsLoadedData()) << "Expected loaded data to be true after loading!";

			EXPECT_EQ(vertexCount, vertexBuffer.GetVertexCount()) << "Unexpected vertex count";
			EXPECT_EQ(3, vertexBuffer.GetVertexBufferObjCount()) << "Expected 3 buffer objects";

			vertexBuffer.ShutDown();
			EXPECT_EQ(false, vertexBuffer.IsLoadedData()) << "Expected loaded data to be false after unloading";
			EXPECT_EQ(0, vertexBuffer.GetVertexArray()) << "Expected VAO handle to be 0";
			EXPECT_EQ(0, vertexBuffer.GetVertexCount()) << "Expected vertex count to be 0 after unload";
			EXPECT_EQ(0, vertexBuffer.GetVertexBufferObjCount()) << "Expected buffer object count to be 0 after unload";

			// Invalid load
			error = vertexBuffer.LoadData(nullptr, vertexCount, eVertexPNT);
			EXPECT_EQ(ERRORID_GFX_VERTEX_BUFFER_NULL_DATA, error) << "Expected load to fail with null data pointer";
			error = vertexBuffer.LoadData(pVerts, 0, eVertexPNT);
			EXPECT_EQ(ERRORID_GFX_VERTEX_BUFFER_ZERO_VERTEX_COUNT, error) << "Expected load to fail on 0 vertex count";
			error = vertexBuffer.LoadData(pVerts, vertexCount, eVertexUnknown);
			EXPECT_EQ(ERRORID_GFX_VERTEX_BUFFER_UNKNOWN_VERTEXTYPE, error) << "Expected load to fail on unknown vertex type";

			delete[] pVerts;
			pVerts = nullptr;
		}
	}
}