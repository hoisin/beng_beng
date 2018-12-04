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
	ErrorId error;

	// Test mesh data to add
	MeshData testMeshData(EVertexType::eVertexPNC, 8, 40);

	EXPECT_EQ(0, m_testManager.GetMeshCount()) << "Manager should be empty when no meshes";

	// Add mesh data test
	error = m_testManager.AddMeshData(&testMeshData, testAddMesh);
	++meshCount;
	EXPECT_EQ(ERRORID_NONE, error) << "Failed to add mesh data";
	EXPECT_EQ(meshCount, m_testManager.GetMeshCount()) << "Unexpected mesh count after AddMeshData";
	EXPECT_NE(nullptr, m_testManager.GetMeshData(testAddMesh)) << "Mesh should've been added";
	// Invalid tests
	//
	// Null ptr
	error = m_testManager.AddMeshData(nullptr, testAddMesh);
	EXPECT_EQ(ERRORID_MESHDATA_NULL_MESHDATA_PTR, error) << "Expected null mesh data ptr error";
	// Duplicate
	error = m_testManager.AddMeshData(&testMeshData, testAddMesh);
	EXPECT_EQ(ERRORID_MESHDATA_ID_DUPLICATE, error) << "Expected duplicate error";
	// Null ID string
	error = m_testManager.AddMeshData(&testMeshData, "");
	EXPECT_EQ(ERRORID_MESHDATA_ID_NULL, error) << "Expected null ID error";

	// Create plane tests
	error = m_testManager.CreatePlane(testPlane, 10, EVertexType::eVertexPNC);
	++meshCount;
	EXPECT_EQ(ERRORID_NONE, error) << "Failed to create plane";
	EXPECT_EQ(meshCount, m_testManager.GetMeshCount()) << "Unexpected mesh count after CreatePlane";
	EXPECT_NE(nullptr, m_testManager.GetMeshData(testPlane)) << "Plane mesh not created in manager";
	// Invalid tests
	//
	// Null id
	error = m_testManager.CreatePlane("", 10, EVertexType::eVertexPNC);
	EXPECT_EQ(ERRORID_MESHDATA_ID_NULL, error) << "Expected null id error";
	// Duplicate
	error = m_testManager.CreatePlane(testPlane, 10, EVertexType::eVertexPNC);
	EXPECT_EQ(ERRORID_MESHDATA_ID_DUPLICATE, error) << "Expected duplicate error";
	// size 0
	error = m_testManager.CreatePlane("MyPlane", 0, EVertexType::eVertexPNC);
	EXPECT_EQ(ERRORID_MESHDATA_SHAPE_GENERATE_SIZE_ZERO, error) << "Expected size 0 error";

	// Create cube tests
	error = m_testManager.CreateCube(testCube, 10, EVertexType::eVertexPNC);
	++meshCount;
	EXPECT_EQ(ERRORID_NONE, error) << "Failed to create cube";
	EXPECT_EQ(meshCount, m_testManager.GetMeshCount()) << "Unexpected mesh count after AddCube";
	EXPECT_NE(nullptr, m_testManager.GetMeshData(testCube)) << "Cube mesh not created in manager";
	// Invalid tests
	//
	// Null id
	error = m_testManager.CreatePlane("", 10, EVertexType::eVertexPNC);
	EXPECT_EQ(ERRORID_MESHDATA_ID_NULL, error) << "Expected null id error";
	// Duplicate
	error = m_testManager.CreateCube(testCube, 10, EVertexType::eVertexPNC);
	EXPECT_EQ(ERRORID_MESHDATA_ID_DUPLICATE, error) << "Expected duplicate error";
	// size 0
	error = m_testManager.CreateCube("MyCube", 0, EVertexType::eVertexPNC);
	EXPECT_EQ(ERRORID_MESHDATA_SHAPE_GENERATE_SIZE_ZERO, error) << "Expected size 0 error";

	// Create sphere tests
	error = m_testManager.CreateSphere(testSphere, 10, EVertexType::eVertexPNC);
	++meshCount;
	EXPECT_EQ(ERRORID_NONE, error) << "Failed to create sphere";
	EXPECT_EQ(meshCount, m_testManager.GetMeshCount()) << "Unexpected mesh count after AddSphere";
	EXPECT_NE(nullptr, m_testManager.GetMeshData(testSphere)) << "Sphere mesh not created in manager";
	// Invalid tests
	//
	// Null id
	error = m_testManager.CreateCube("", 10, EVertexType::eVertexPNC);
	EXPECT_EQ(ERRORID_MESHDATA_ID_NULL, error) << "Expected null id error";
	// Duplicate
	error = m_testManager.CreateSphere(testSphere, 10, EVertexType::eVertexPNC);
	EXPECT_EQ(ERRORID_MESHDATA_ID_DUPLICATE, error) << "Expected duplicate id error";
	// size 0
	error = m_testManager.CreateCube("MySphere", 0, EVertexType::eVertexPNC);
	EXPECT_EQ(ERRORID_MESHDATA_SHAPE_GENERATE_SIZE_ZERO, error) << "Expected size 0 error";

	m_testManager.CleanUp();
	EXPECT_EQ(0, m_testManager.GetMeshCount()) << "Manager should be empty after CleanUp";

}