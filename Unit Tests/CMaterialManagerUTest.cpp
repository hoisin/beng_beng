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

	// Test Adding
	for (int i = 0; i < totalMaterials; i++) 
	{
		std::string stringID = "testMaterial_" + std::to_string(i + 1);
		CMaterial newMaterial;
		result = m_materialMgr.AddMaterial(stringID, newMaterial);
		EXPECT_EQ(true, result) << "Failed to add material";
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
	result = m_materialMgr.AddMaterial("testMaterial_1", tempMaterial);
	EXPECT_EQ(false, result) << "Expected fail on adding duplicate material ID";

	// Get non-existing material
	CMaterial* pTestMaterial = m_materialMgr.GetMaterial("NoMaterial");
	EXPECT_EQ(nullptr, pTestMaterial) << "Expected null ptr for non existing material get";
}