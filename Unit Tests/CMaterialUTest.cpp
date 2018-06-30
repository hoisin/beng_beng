#include "CMaterialUTest.h"
#include "CMaterial.h"

//--------------------------------------------------------------------------
// UTest class
//--------------------------------------------------------------------------
CMaterialUTest::CMaterialUTest()
{
}

CMaterialUTest::~CMaterialUTest()
{
}

void CMaterialUTest::SetUp()
{
}

void CMaterialUTest::TearDown()
{
}


//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------

TEST_F(CMaterialUTest, GetSet)
{
	// Expected/Set values
	glm::float32 setAmbient = 1.0;
	glm::float32 setDiffuse = 1.0;
	glm::float32 setSpecular = 1.0;
	glm::float32 setSpecularExpo = 1.0;
	glm::vec3 setAmbientColour = glm::vec3(1.0, 1.0, 1.0);
	glm::vec3 setDiffuseColour = glm::vec3(1.0, 1.0, 1.0);
	glm::vec3 setSpecularColour = glm::vec3(1.0, 1.0, 1.0);
	std::string setTextureID = "testMaterialID";
	std::string setNormalMapID = "testNormalMapID";

	// Store values
	glm::float32 getAmbient;
	glm::float32 getDiffuse;
	glm::float32 getSpecular;
	glm::float32 getSpecularExpo;
	glm::vec3 getAmbientColour;
	glm::vec3 getDiffuseColour;
	glm::vec3 getSpecularColour;
	std::string getTextureID;
	std::string getNormalMap;

	// Set calls
	m_material.SetAmbient(setAmbient);
	m_material.SetDiffuse(setDiffuse);
	m_material.SetSpecular(setSpecular);
	m_material.SetSpecularExpo(setSpecularExpo);
	m_material.SetAmbientCol(setAmbientColour);
	m_material.SetDiffuseCol(setDiffuseColour);
	m_material.SetSpecularCol(setSpecularColour);
	m_material.SetDiffuseTextureID(setTextureID);
	m_material.SetNormalMapTextureID(setNormalMapID);

	// Test gets
	getAmbient = m_material.GetAmbient();
	getDiffuse = m_material.GetDiffuse();
	getSpecular = m_material.GetSpecular();
	getSpecularExpo = m_material.GetSpecExpo();
	getAmbientColour = m_material.GetAmbientColour();
	getDiffuseColour = m_material.GetAmbientColour();
	getSpecularColour = m_material.GetSpecularColour();
	getTextureID = m_material.GetDiffuseTextureID();
	getNormalMap = m_material.GetNormalMapTextureID();

	EXPECT_EQ(setAmbient, getAmbient) << "Unexpected ambient value";
	EXPECT_EQ(setDiffuse, getDiffuse) << "Unexpected diffuse value";
	EXPECT_EQ(setSpecular, getSpecular) << "Unexpected specular value";
	EXPECT_EQ(setSpecularExpo, getSpecularExpo) << "Unexpected specular expo value";
	EXPECT_EQ(setAmbientColour, getAmbientColour) << "Unexpected ambient colour value";
	EXPECT_EQ(setDiffuseColour, getDiffuseColour) << "Unexpected diffuse colour value";
	EXPECT_EQ(setSpecularColour, getSpecularColour) << "Unexpected specular colour value";
	EXPECT_EQ(setTextureID, getTextureID) << "Unexpected texture ID value";
	EXPECT_EQ(setNormalMapID, getNormalMap) << "unexpected texture ID for normal map";
}