#include "CMeshUTest.h"
#include "GfxDefs.h"
#include "CMesh.h"

//--------------------------------------------------------------------------
// UTest class
//--------------------------------------------------------------------------

CMeshUTest::CMeshUTest()
{
	m_windowName = "CMesh Test Window";
	m_width = 800;
	m_height = 600;
	m_majorVer = 3;
	m_minorVer = 3;
}

CMeshUTest::~CMeshUTest()
{
}

void CMeshUTest::SetUp()
{
	m_testApp.Initialise(m_windowName, m_width, m_height);
}

void CMeshUTest::TearDown()
{
	m_testApp.ShutDown();
}


//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------

TEST_F(CMeshUTest, LoadMesh)
{
	bool bTestAppInit = m_testApp.IsInitialised();
	EXPECT_EQ(true, bTestAppInit) << "testApp failed to initialise!";
	if (bTestAppInit)
	{
		ErrorId error = m_testApp.InitOpenGL(m_majorVer, m_minorVer);
		EXPECT_EQ(ERRORID_NONE, error) << "Failed to initialise OpenGL";
		if (!IsError(error))
		{
			// Test mesh data, doesn't need to be anything
			MeshData testMeshData(eVertexPNT, 200, 300);
			std::string testMaterialID = "TestMaterial";
			CMesh mesh;
			EXPECT_EQ(false, mesh.IsLoaded()) << "Expected loaded to be false before loading!";
			EXPECT_EQ(nullptr, mesh.GetMeshData()) << "Expected null ptr for Mesh Data get before loading!";

			error = mesh.LoadMesh(&testMeshData, testMaterialID);
			EXPECT_EQ(ERRORID_NONE, error) << "Failed to load mesh data to CMesh";
			EXPECT_EQ(true, mesh.IsLoaded()) << "Expected loaded to be true after loading!";
			EXPECT_EQ(testMaterialID, mesh.GetMaterialID()) << "Unexpected materialID";
			EXPECT_NE(nullptr, mesh.GetMeshData()) << "Expected mesh data to not be null after loading!";
			EXPECT_NE(nullptr, mesh.GetVertexBuffer()) << "Vertex buffer should not be null after loading!";
			EXPECT_NE(nullptr, mesh.GetIndexBuffer()) << "Index buffer should not be null after loading";
			
			mesh.CleanUp();
			EXPECT_EQ(false, mesh.IsLoaded()) << "Expected loaded to be false after clean up";
			EXPECT_EQ(nullptr, mesh.GetMeshData()) << "Expected null ptr for mesh data after clean up";

			// Invalid test
			error = mesh.LoadMesh(nullptr, testMaterialID);
			EXPECT_EQ(ERRORID_GFX_MESH_NULL_MESHDATA, error) << "Expected load to fail with null data ptr";
		}
	}
}