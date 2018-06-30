#include "CCameraUTest.h"

//--------------------------------------------------------------------------
// UTest class
//--------------------------------------------------------------------------

CCameraUTest::CCameraUTest()
{
}

CCameraUTest::~CCameraUTest()
{
}

void CCameraUTest::SetUp()
{
}

void CCameraUTest::TearDown()
{
}


//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------
TEST_F(CCameraUTest, GetSet)
{
	glm::vec3 pos(1.0, 1.0, 1.0);
	glm::vec3 up(1.0, 1.0, 1.0);
	glm::vec3 look(1.0, 1.0, 1.0);
	glm::vec3 prevPos(2.0, 2.0, 2.0);
	glm::vec3 prevLook(2.0, 2.0, 2.0);
	float near = 1.0;
	float far = 1.0;
	float aspectRatio = 1.0;
	float fov = 1.0;

	// Expected dafaults should be 0.
	EXPECT_EQ(m_camera.GetPosition(), glm::vec3(0, 0, 0)) << "Expected position to be 0 on default";
	EXPECT_EQ(m_camera.GetUp(), glm::vec3(0, 0, 0)) << "Expected up to be 0 on default";
	EXPECT_EQ(m_camera.GetLook(), glm::vec3(0, 0, 0)) << "Expected look to be 0 on default";
	EXPECT_EQ(m_camera.GetPrevPosition(), glm::vec3(0, 0, 0)) << "Expected prev position to be 0 on default";
	EXPECT_EQ(m_camera.GetPrevLook(), glm::vec3(0, 0, 0)) << "Expected prev look to be 0 on default";
	EXPECT_EQ(m_camera.GetNear(), 0.0) << "Expected near to be 0 on default";
	EXPECT_EQ(m_camera.GetFar(), 0.0) << "Expected far to be 0 on defautl";
	EXPECT_EQ(m_camera.GetAspectRatio(), 0.0) << "Expected aspect ratio to be 0 on default";
	EXPECT_EQ(m_camera.GetFOV(), 0.0) << "Expected fov to be 0 on default";

	// Setting values
	m_camera.SetPosition(pos);
	m_camera.SetUp(up);
	m_camera.SetLook(look);
	m_camera.SetPrevPosition(prevPos);
	m_camera.SetPrevLook(prevLook);
	m_camera.SetNear(near);
	m_camera.SetFar(far);
	m_camera.SetAspectRatio(aspectRatio);
	m_camera.SetFOV(fov);

	// Testing expected return values
	EXPECT_EQ(m_camera.GetPosition(), pos) << "Unexpected position after set";
	EXPECT_EQ(m_camera.GetUp(), up) << "Unexpected up after set";
	EXPECT_EQ(m_camera.GetLook(), look) << "Unexpected look after set";
	EXPECT_EQ(m_camera.GetPrevPosition(), prevPos) << "Unexpected prev position after set";
	EXPECT_EQ(m_camera.GetPrevLook(), prevLook) << "Unexpected prev look after set";
	EXPECT_EQ(m_camera.GetNear(), near) << "Unexpected near after set";
	EXPECT_EQ(m_camera.GetFar(), far) << "Unexpected far after set";
	EXPECT_EQ(m_camera.GetAspectRatio(), aspectRatio) << "Unexpected aspect ratio after set";
	EXPECT_EQ(m_camera.GetFOV(), fov) << "Unexpected fov after set";

	// To Do:
	// Test the get matrix functions probably.
	// Although they are simply GLM math calls.
}