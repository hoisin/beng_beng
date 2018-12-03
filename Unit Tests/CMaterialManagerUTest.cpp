#include "CMaterialManagerUTest.h"

//--------------------------------------------------------------------------
// UTest class
//--------------------------------------------------------------------------
CMaterialManagerUTest::CMaterialManagerUTest()
{
}

CMaterialManagerUTest::~CMaterialManagerUTest()
{
}

void CMaterialManagerUTest::SetUp()
{
}

void CMaterialManagerUTest::TearDown()
{
}


//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------

TEST_F(CMaterialManagerUTest, AddGetMaterial)
{
	bool result = false;
	int totalMaterials = 10;
	std::vector<CMaterial> materials;
	ErrorId error;

	// Test Adding
	for (int i = 0; i < totalMaterials; i++) 
	{
		std::string stringID = "testMaterial_" + std::to_string(i + 1);
		CMaterial newMaterial;
		error = m_materialMgr.AddMaterial(stringID, newMaterial);
		EXPECT_EQ(ERRORID_NONE, error) << "Failed to add material";
	}

	// Test getting
	for (int j = 0; j < totalMaterials; j++)
	{
		std::string stringID = "testMaterial_" + std::to_string(j + 1);
		CMaterial* pMaterial = m_materialMgr.GetMaterial(stringID);
		EXPECT_NE(nullptr, pMaterial) << "Failed to get material: " + stringID;
	}

	// Duplicate add
	CMaterial tempMaterial;
	error = m_materialMgr.AddMaterial("testMaterial_1", tempMaterial);
	EXPECT_EQ(ERRORID_MATERIAL_ID_DUPLICATE, error) << "Expected fail on adding duplicate material ID";

	// Get non-existing material
	CMaterial* pTestMaterial = m_materialMgr.GetMaterial("NoMaterial");
	EXPECT_EQ(nullptr, pTestMaterial) << "Expected null ptr for non existing material get";
}