#include "CModelUTest.h"
#include "GfxDefs.h"
#include "CModel.h"


//--------------------------------------------------------------------------
// UTest class
//--------------------------------------------------------------------------

CModelUTest::CModelUTest()
{
	m_windowName = "CModel Test window";
	m_width = 800;
	m_height = 600;
	m_majorVer = 3;
	m_minorVer = 3;
}

CModelUTest::~CModelUTest()
{
}

void CModelUTest::SetUp()
{
	m_testApp.Initialise(m_windowName, m_width, m_height);
}

void CModelUTest::TearDown()
{
	m_testApp.ShutDown();
}


//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------


TEST_F(CModelUTest, AddMesh)
{
	bool result = m_testApp.IsInitialised();
	EXPECT_EQ(true, result) << "Failed to initialise OpenGL test app";
	if (result)
	{
		ErrorId error = m_testApp.InitOpenGL(m_majorVer, m_minorVer);
		EXPECT_EQ(ERRORID_NONE, error) << "Failed to initialise OpenGL";
		if (!IsError(error))
		{
			// Test mesh data, doesn't matter what it is
			MeshData testMeshData_1(eVertexPNT, 200, 300);
			MeshData testMeshData_2(eVertexPNT, 200, 300);
			MeshData testMeshData_3(eVertexPNT, 200, 300);

			std::string materialID = "TestMaterial";
			std::string meshID = "TestMesh";
			std::string testMeshDataID_1 = "MeshData_1";
			std::string testMeshDataID_2 = "MeshData_2";
			std::string testMeshDataID_3 = "MeshData_3";

			// Assign IDs to test mesh data for testing
			testMeshData_1.m_ID = testMeshDataID_1;
			testMeshData_2.m_ID = testMeshDataID_2;
			testMeshData_3.m_ID = testMeshDataID_3;

			// Test retrieval of added mesh
			CModel model(meshID);
			EXPECT_EQ(meshID, model.GetID()) << "Unexpected model ID";
			EXPECT_EQ(0, model.GetMeshCount()) << "Expected mesh count to be 0 when nothing added!";
			EXPECT_EQ(nullptr, model.GetMesh(0)) << "Expected null ptr when attempting to get mesh when none in model";

			// Add single mesh
			error = model.AddMesh(&testMeshData_1, materialID);
			EXPECT_EQ(ERRORID_NONE, error) << "Failed to add mesh " + testMeshDataID_1 + " to model";

			EXPECT_EQ(1, model.GetMeshCount()) << "Expected mesh count of one after adding a single mesh data!";
			// Use mesh data ID to determine what the mesh is
			EXPECT_EQ(testMeshDataID_1, model.GetMesh(0)->GetMeshData()->m_ID) << "Unexpected mesh";

			// Add two meshes
			error = model.AddMesh(&testMeshData_2, materialID);
			EXPECT_EQ(ERRORID_NONE, error) << "Failed to add mesh " + testMeshDataID_2 + " to model";
			error = model.AddMesh(&testMeshData_3, materialID);
			EXPECT_EQ(ERRORID_NONE, error) << "Failed to add mesh " + testMeshDataID_3 + " to model";

			// Test Retrieval of last added mesh
			EXPECT_EQ(3, model.GetMeshCount()) << "Expected to have 3 meshes in model";
			if (model.GetMeshCount() == 3)
			{
				EXPECT_EQ(testMeshDataID_3, model.GetMesh(2)->GetMeshData()->m_ID) << "Unexpected mesh";
			}

			// Test retrieval of invalid mesh
			EXPECT_EQ(nullptr, model.GetMesh(100)) << "Expected null ptr when attempting to retrieve invalid mesh";

			// Try adding null data
			error = model.AddMesh(nullptr, materialID);
			EXPECT_EQ(ERRORID_GFX_MESH_NULL_MESHDATA, error) << "Expected null meshdata error";

			// Shut down
			model.CleanUp();
			EXPECT_EQ(0, model.GetMeshCount()) << "Expected mesh count of 0 after clean up";
		}
	}
}