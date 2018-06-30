#include "CMeshDataManagerUTest.h"


CMeshDataManagerUTest::CMeshDataManagerUTest()
{
}

CMeshDataManagerUTest::~CMeshDataManagerUTest()
{
}

void CMeshDataManagerUTest::SetUp()
{
}

void CMeshDataManagerUTest::TearDown()
{
}


//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------

TEST_F(CMeshDataManagerUTest, CreateTests)
{
	std::string testAddMesh = "TestMeshAdd";
	std::string testPlane = "TestPlaneAdd";
	std::string testCube = "TestCubeAdd";
	std::string testSphere = "TestSphereAdd";
	int meshCount = 0;

	// Test mesh data to add
	MeshData testMeshData(EVertexType::eVertexPNC, 8, 40);

	EXPECT_EQ(0, m_testManager.GetMeshCount()) << "Manager should be empty when no meshes";

	m_testManager.AddMeshData(&testMeshData, testAddMesh);
	++meshCount;
	EXPECT_EQ(meshCount, m_testManager.GetMeshCount()) << "Unexpected mesh count after AddMeshData";
	EXPECT_NE(nullptr, m_testManager.GetMeshData(testAddMesh)) << "Mesh should've been added";

	m_testManager.CreatePlane(testPlane, 10, EVertexType::eVertexPNC);
	++meshCount;
	EXPECT_EQ(meshCount, m_testManager.GetMeshCount()) << "Unexpected mesh count after CreatePlane";
	EXPECT_NE(nullptr, m_testManager.GetMeshData(testPlane)) << "Plane mesh not created in manager";

	m_testManager.CreateCube(testCube, 10, EVertexType::eVertexPNC);
	++meshCount;
	EXPECT_EQ(meshCount, m_testManager.GetMeshCount()) << "Unexpected mesh count after AddCube";
	EXPECT_NE(nullptr, m_testManager.GetMeshData(testCube)) << "Cube mesh not created in manager";

	m_testManager.CreateSphere(testSphere, 10, EVertexType::eVertexPNC);
	++meshCount;
	EXPECT_EQ(meshCount, m_testManager.GetMeshCount()) << "Unexpected mesh count after AddSphere";
	EXPECT_NE(nullptr, m_testManager.GetMeshData(testSphere)) << "Sphere mesh not created in manager";

	m_testManager.CleanUp();
	EXPECT_EQ(0, m_testManager.GetMeshCount()) << "Manager should be empty after CleanUp";

}