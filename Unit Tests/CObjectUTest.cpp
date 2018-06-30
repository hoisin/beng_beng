#include "CObjectUTest.h"
#include <glm\vec3.hpp>

//--------------------------------------------------------------------------
// UTest class
//--------------------------------------------------------------------------

CObjectUTest::CObjectUTest()
{
}

CObjectUTest::~CObjectUTest()
{
}

void CObjectUTest::SetUp()
{
}

void CObjectUTest::TearDown()
{
}


//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------

TEST_F(CObjectUTest, SetGetTests)
{
	glm::vec3 testLocation(10, 10, 10);
	glm::vec3 testFacingDirection(1.0, 0, 0);
	glm::vec3 testPos(5, 5, 5);
	glm::vec3 testPrevPos(2, 2, 2);
	glm::vec3 testDirection(0, 1.0, 0);
	glm::vec3 testRotation(90, 0, 90);
	glm::vec3 testPrevRotation(0, 90, 0);
	std::string testModelID = "MyTestID";
	float testScale = 10.0;

	// Test set location
	m_testObject.SetLocation(testLocation);
	EXPECT_EQ(testLocation, m_testObject.GetPosition()) << "Position should match test location on SetLocation";
	EXPECT_EQ(testLocation, m_testObject.GetPrevPosition()) << "Prev position should match test location on SetLocation";

	// Test set facing direction
	m_testObject.SetFacingDirection(testFacingDirection);
	EXPECT_EQ(testFacingDirection, m_testObject.GetRotation()) << "Rotation should match test facing direction on SetFacingDirection";
	EXPECT_EQ(testFacingDirection, m_testObject.GetPrevRotation()) << "Prev rotation should match test facing direction on SetFacingDirection";

	// Run rest of sets
	m_testObject.SetPosition(testPos);
	m_testObject.SetPrevPosition(testPrevPos);
	m_testObject.SetDirection(testDirection);
	m_testObject.SetRotation(testRotation);
	m_testObject.SetPrevRotation(testPrevRotation);
	m_testObject.SetModelID(testModelID);
	m_testObject.SetScale(testScale);

	// Get tests
	EXPECT_EQ(testPos, m_testObject.GetPosition()) << "Position does not match set";
	EXPECT_EQ(testPrevPos, m_testObject.GetPrevPosition()) << "Prev position does not match set";
	EXPECT_EQ(testDirection, m_testObject.GetDirection()) << "Direction does not match set";
	EXPECT_EQ(testRotation, m_testObject.GetRotation()) << "Rotation does not match set";
	EXPECT_EQ(testPrevRotation, m_testObject.GetPrevRotation()) << "Prev rotation does not match set";
	EXPECT_EQ(testModelID, m_testObject.GetModelID()) << "Mesh ID does not match set";
	EXPECT_EQ(testScale, m_testObject.GetScale()) << "Scale value does not match set";
}