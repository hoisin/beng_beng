#include "CMeshDataGeneratorUTest.h"

CMeshDataGeneratorUTest::CMeshDataGeneratorUTest()
{
}


CMeshDataGeneratorUTest::~CMeshDataGeneratorUTest()
{
}

void CMeshDataGeneratorUTest::SetUp()
{
}

void CMeshDataGeneratorUTest::TearDown()
{
}


//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------


// ========= Triangle mesh generation tests =========
std::string g_triangleID = "MyTriangle";
float		g_triangleSize = 0;
EVertexType g_triangleVertexType = eVertexUnknown;

// Invalid input tests
TEST_F(CMeshDataGeneratorUTest, CreateTriangleInvalid)
{
	g_triangleSize = 4;
	g_triangleVertexType = eVertexPC;

	MeshData* invalidTriangle = m_testGenerator.CreateTriangle(
		"", g_triangleSize, g_triangleVertexType);

	EXPECT_EQ(invalidTriangle, nullptr) << "Expected NULL with generation using NULL geometryID";

	invalidTriangle = m_testGenerator.CreateTriangle(
		g_triangleID, 0, g_triangleVertexType);

	EXPECT_EQ(invalidTriangle, nullptr) << "Expected NULL with generation using invalid size";

	invalidTriangle = m_testGenerator.CreateTriangle(
		g_triangleID, g_triangleSize, eVertexUnknown);

	EXPECT_EQ(invalidTriangle, nullptr) << "Expected NULL with generation using unknown vertex type";
}

// Type position/colour test
TEST_F(CMeshDataGeneratorUTest, CreateTrianglePC)
{
	g_triangleSize = 4;
	g_triangleVertexType = eVertexPC;

	MeshData* testTriangle = m_testGenerator.CreateTriangle(g_triangleID,
		g_triangleSize, g_triangleVertexType);

	EXPECT_NE(testTriangle, nullptr) << "Failed to generate triangle mesh data";
	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
	if (testTriangle)
	{
		// Check generated triangle data
		glm::vec3 pointCheck[3];
		pointCheck[0] = glm::vec3(0, 2, 0);
		pointCheck[1] = glm::vec3(-2, -2, 0);
		pointCheck[2] = glm::vec3(2, -2, 0);

		glm::vec3 colourCheck(0, 0, 0);

		// Test vertex data
		SVertexTypePC* pVertex = static_cast<SVertexTypePC*>(testTriangle->pVertices);

		EXPECT_EQ(3, testTriangle->vertexCount) << "Incorrect number of vertices";
		EXPECT_EQ(3, testTriangle->indexCount) << "Incorrect number of indices";

		EXPECT_EQ(pointCheck[0], pVertex[0].position) << "Incorrect vertex pos @ 1";
		EXPECT_EQ(pointCheck[1], pVertex[1].position) << "Incorrect vertex pos @ 2";
		EXPECT_EQ(pointCheck[2], pVertex[2].position) << "Incorrect vertex pos @ 3";

		EXPECT_EQ(colourCheck, pVertex[0].colour) << "Incorrect colour @ 1";
		EXPECT_EQ(colourCheck, pVertex[1].colour) << "Incorrect colour @ 2";
		EXPECT_EQ(colourCheck, pVertex[2].colour) << "Incorrect colour @ 3";

		EXPECT_EQ(g_triangleID, testTriangle->m_ID) <<
			"Incorrect ID, expected: " + g_triangleID + " got: " + testTriangle->m_ID;

		EXPECT_EQ(g_triangleVertexType, testTriangle->vertexType) << "Incorrect vertex type";

		// Test index data
		int indexCheck[3];
		indexCheck[0] = 0;
		indexCheck[1] = 1;
		indexCheck[2] = 2;

		EXPECT_EQ(indexCheck[0], testTriangle->pIndices[0]) << "Incorrect index @ 1";
		EXPECT_EQ(indexCheck[1], testTriangle->pIndices[1]) << "Incorrect index @ 2";
		EXPECT_EQ(indexCheck[2], testTriangle->pIndices[2]) << "Incorrect index @ 3";

		delete testTriangle;
		testTriangle = nullptr;
	}
}

// Type position/texcoord test
TEST_F(CMeshDataGeneratorUTest, CreateTrianglePT)
{
	g_triangleSize = 4;
	g_triangleVertexType = eVertexPT;

	MeshData* testTriangle = m_testGenerator.CreateTriangle(g_triangleID,
		g_triangleSize, g_triangleVertexType);

	EXPECT_NE(testTriangle, nullptr) << "Failed to generate triangle mesh data";

	if (testTriangle)
	{
		// Check generated triangle data
		glm::vec3 pointCheck[3];
		pointCheck[0] = glm::vec3(0, 2, 0);
		pointCheck[1] = glm::vec3(-2, -2, 0);
		pointCheck[2] = glm::vec3(2, -2, 0);

		// Test vertex data
		SVertexTypePT* pVertex = static_cast<SVertexTypePT*>(testTriangle->pVertices);

		EXPECT_EQ(3, testTriangle->vertexCount) << "Incorrect number of vertices";
		EXPECT_EQ(3, testTriangle->indexCount) << "Incorrect number of indices";

		EXPECT_EQ(pointCheck[0], pVertex[0].position) << "Incorrect vertex pos @ 1";
		EXPECT_EQ(pointCheck[1], pVertex[1].position) << "Incorrect vertex pos @ 2";
		EXPECT_EQ(pointCheck[2], pVertex[2].position) << "Incorrect vertex pos @ 3";

		// Test texture coordinates
		glm::vec2 texCoordCheck[3];
		texCoordCheck[0] = glm::vec2(0.5, 1);
		texCoordCheck[1] = glm::vec2(0, 0);
		texCoordCheck[2] = glm::vec2(1, 0);
		EXPECT_EQ(texCoordCheck[0], pVertex[0].textureCoord) << "Incorrect texture coordinate @ 1";
		EXPECT_EQ(texCoordCheck[1], pVertex[1].textureCoord) << "Incorrect texture coordinate @ 2";
		EXPECT_EQ(texCoordCheck[2], pVertex[2].textureCoord) << "Incorrect texture coordinate @ 3";

		EXPECT_EQ(g_triangleID, testTriangle->m_ID) <<
			"Incorrect ID, expected: " + g_triangleID + " got: " + testTriangle->m_ID;

		EXPECT_EQ(g_triangleVertexType, testTriangle->vertexType) << "Incorrect vertex type";

		// Test index data
		int indexCheck[3];
		indexCheck[0] = 0;
		indexCheck[1] = 1;
		indexCheck[2] = 2;

		EXPECT_EQ(indexCheck[0], testTriangle->pIndices[0]) << "Incorrect index @ 1";
		EXPECT_EQ(indexCheck[1], testTriangle->pIndices[1]) << "Incorrect index @ 2";
		EXPECT_EQ(indexCheck[2], testTriangle->pIndices[2]) << "Incorrect index @ 3";

		delete testTriangle;
		testTriangle = nullptr;
	}
}

// Type position/normal/colour test
TEST_F(CMeshDataGeneratorUTest, CreateTrianglePNC)
{
	g_triangleSize = 4;
	g_triangleVertexType = eVertexPNC;

	MeshData* testTriangle = m_testGenerator.CreateTriangle(g_triangleID,
		g_triangleSize, g_triangleVertexType);

	EXPECT_NE(testTriangle, nullptr) << "Failed to generate triangle mesh data";

	if (testTriangle)
	{
		// Check generated triangle data
		glm::vec3 pointCheck[3];
		pointCheck[0] = glm::vec3(0, 2, 0);
		pointCheck[1] = glm::vec3(-2, -2, 0);
		pointCheck[2] = glm::vec3(2, -2, 0);

		glm::vec4 colourCheck(0, 0, 0, 0);
		// All vertex normals should be the same for triangle
		glm::vec3 normalCheck(0, 0, 1);

		// Test vertex data
		SVertexTypePNC* pVertex = static_cast<SVertexTypePNC*>(testTriangle->pVertices);

		EXPECT_EQ(3, testTriangle->vertexCount) << "Incorrect number of vertices";
		EXPECT_EQ(3, testTriangle->indexCount) << "Incorrect number of indices";

		EXPECT_EQ(pointCheck[0], pVertex[0].position) << "Incorrect vertex pos @ 1";
		EXPECT_EQ(pointCheck[1], pVertex[1].position) << "Incorrect vertex pos @ 2";
		EXPECT_EQ(pointCheck[2], pVertex[2].position) << "Incorrect vertex pos @ 3";

		EXPECT_EQ(colourCheck, pVertex[0].colour) << "Incorrect colour @ 1";
		EXPECT_EQ(colourCheck, pVertex[1].colour) << "Incorrect colour @ 2";
		EXPECT_EQ(colourCheck, pVertex[2].colour) << "Incorrect colour @ 3";

		EXPECT_EQ(normalCheck, pVertex[0].normal) << "Incorrect normal @ 1";
		EXPECT_EQ(normalCheck, pVertex[1].normal) << "Incorrect normal @ 2";
		EXPECT_EQ(normalCheck, pVertex[2].normal) << "Incorrect normal @ 3";

		EXPECT_EQ(g_triangleID, testTriangle->m_ID) <<
			"Incorrect ID, expected: " + g_triangleID + " got: " + testTriangle->m_ID;

		EXPECT_EQ(g_triangleVertexType, testTriangle->vertexType) << "Incorrect vertex type";

		// Test index data
		int indexCheck[3];
		indexCheck[0] = 0;
		indexCheck[1] = 1;
		indexCheck[2] = 2;

		EXPECT_EQ(indexCheck[0], testTriangle->pIndices[0]) << "Incorrect index @ 1";
		EXPECT_EQ(indexCheck[1], testTriangle->pIndices[1]) << "Incorrect index @ 2";
		EXPECT_EQ(indexCheck[2], testTriangle->pIndices[2]) << "Incorrect index @ 3";

		delete testTriangle;
		testTriangle = nullptr;
	}
}

// Type position/texcoord test
TEST_F(CMeshDataGeneratorUTest, CreateTrianglePNT)
{
	g_triangleSize = 4;
	g_triangleVertexType = eVertexPNT;

	MeshData* testTriangle = m_testGenerator.CreateTriangle(g_triangleID,
		g_triangleSize, g_triangleVertexType);

	EXPECT_NE(testTriangle, nullptr) << "Failed to generate triangle mesh data";

	if (testTriangle)
	{
		// Check generated triangle data
		glm::vec3 pointCheck[3];
		pointCheck[0] = glm::vec3(0, 2, 0);
		pointCheck[1] = glm::vec3(-2, -2, 0);
		pointCheck[2] = glm::vec3(2, -2, 0);
		
		// All vertex normals should be the same for triangle
		glm::vec3 normalCheck(0, 0, 1);

		// Test vertex data
		SVertexTypePNT* pVertex = static_cast<SVertexTypePNT*>(testTriangle->pVertices);

		EXPECT_EQ(3, testTriangle->vertexCount) << "Incorrect number of vertices";
		EXPECT_EQ(3, testTriangle->indexCount) << "Incorrect number of indices";

		EXPECT_EQ(pointCheck[0], pVertex[0].position) << "Incorrect vertex pos @ 1";
		EXPECT_EQ(pointCheck[1], pVertex[1].position) << "Incorrect vertex pos @ 2";
		EXPECT_EQ(pointCheck[2], pVertex[2].position) << "Incorrect vertex pos @ 3";

		EXPECT_EQ(normalCheck, pVertex[0].normal) << "Incorrect normal @ 1";
		EXPECT_EQ(normalCheck, pVertex[1].normal) << "Incorrect normal @ 2";
		EXPECT_EQ(normalCheck, pVertex[2].normal) << "Incorrect normal @ 3";

		// Test texture coordinates
		glm::vec2 texCoordCheck[3];
		texCoordCheck[0] = glm::vec2(0.5, 1);
		texCoordCheck[1] = glm::vec2(0, 0);
		texCoordCheck[2] = glm::vec2(1, 0);
 		EXPECT_EQ(texCoordCheck[0], pVertex[0].textureCoord) << "Incorrect texture coordinate @ 1";
		EXPECT_EQ(texCoordCheck[1], pVertex[1].textureCoord) << "Incorrect texture coordinate @ 2";
		EXPECT_EQ(texCoordCheck[2], pVertex[2].textureCoord) << "Incorrect texture coordinate @ 3";

		EXPECT_EQ(g_triangleID, testTriangle->m_ID) <<
			"Incorrect ID, expected: " + g_triangleID + " got: " + testTriangle->m_ID;

		EXPECT_EQ(g_triangleVertexType, testTriangle->vertexType) << "Incorrect vertex type";

		// Test index data
		int indexCheck[3];
		indexCheck[0] = 0;
		indexCheck[1] = 1;
		indexCheck[2] = 2;

		EXPECT_EQ(indexCheck[0], testTriangle->pIndices[0]) << "Incorrect index @ 1";
		EXPECT_EQ(indexCheck[1], testTriangle->pIndices[1]) << "Incorrect index @ 2";
		EXPECT_EQ(indexCheck[2], testTriangle->pIndices[2]) << "Incorrect index @ 3";

		delete testTriangle;
		testTriangle = nullptr;
	}
}

// ========= EOF triangle mesh generation tests =========



// ========= Quad mesh generation tests =========
std::string g_quadID = "TestQuad";
float g_quadSize = 0;
EVertexType g_quadVertexType = eVertexUnknown;

TEST_F(CMeshDataGeneratorUTest, CreateQuadInvalid)
{
	g_quadSize = 6;
	g_quadVertexType = eVertexPC;

	MeshData* invalidQuad = m_testGenerator.CreateQuad(
		"", g_quadSize, g_quadVertexType);

	EXPECT_EQ(invalidQuad, nullptr) << "Expected NULL with generation using NULL geometryID";

	invalidQuad = m_testGenerator.CreateQuad(
		g_quadID, 0, g_quadVertexType);

	EXPECT_EQ(invalidQuad, nullptr) << "Expected NULL with generation using invalid size";

	invalidQuad = m_testGenerator.CreateQuad(
		g_quadID, g_quadSize, eVertexUnknown);

	EXPECT_EQ(invalidQuad, nullptr) << "Expected NULL with generation using unknown vertex type";
}

TEST_F(CMeshDataGeneratorUTest, CreateQuadPC)
{
	g_quadSize = 8;
	g_quadVertexType = eVertexPC;

	MeshData* testQuad = m_testGenerator.CreateQuad(g_quadID, g_quadSize,
		g_quadVertexType);

	EXPECT_NE(nullptr, testQuad) << "Failed to create test quad";

	if (testQuad)
	{
		// Test quad data

		EXPECT_EQ(g_quadID, testQuad->m_ID) <<
			"Incorrect ID, expected: " + g_triangleID + " got: " + testQuad->m_ID;

		EXPECT_EQ(g_quadVertexType, testQuad->vertexType) << "Incorrect vertex type";
		EXPECT_EQ(4, testQuad->vertexCount) << "Incorrect vertex count";
		EXPECT_EQ(6, testQuad->indexCount) << "Incorrect index count";

		float dist = g_quadSize / 2;
		glm::vec3 posCheck[4];
		posCheck[0] = glm::vec3(-dist, dist, 0);
		posCheck[1] = glm::vec3(dist, dist, 0);
		posCheck[2] = glm::vec3(-dist, -dist, 0);
		posCheck[3] = glm::vec3(dist, -dist, 0);

		SVertexTypePC* pVertex = static_cast<SVertexTypePC*>(testQuad->pVertices);

		EXPECT_EQ(posCheck[0], pVertex[0].position) << "Invalid position @ 1";
		EXPECT_EQ(posCheck[1], pVertex[1].position) << "Invalid position @ 2";
		EXPECT_EQ(posCheck[2], pVertex[2].position) << "Invalid position @ 3";
		EXPECT_EQ(posCheck[3], pVertex[3].position) << "Invalid position @ 4";

		glm::vec3 colourCheck(0, 0, 0);
		EXPECT_EQ(colourCheck, pVertex[0].colour) << "Invalid colour @ 1";
		EXPECT_EQ(colourCheck, pVertex[1].colour) << "Invalid colour @ 2";
		EXPECT_EQ(colourCheck, pVertex[2].colour) << "Invalid colour @ 3";
		EXPECT_EQ(colourCheck, pVertex[3].colour) << "Invalid colour @ 4";

		delete testQuad;
		testQuad = nullptr;
	}
}


// ========= EOF Quad mesh generation tests =========