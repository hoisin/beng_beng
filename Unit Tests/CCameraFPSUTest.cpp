#include "CCameraFPSUTest.h"

//--------------------------------------------------------------------------
// UTest class
//--------------------------------------------------------------------------

CCameraFPSUTest::CCameraFPSUTest()
{
	m_defaultPos = glm::vec3(0, 0, 0);
	m_defaultLook = glm::vec3(0, 0, -1);
	m_defaultUp = glm::vec3(0, 1, 0);
}

CCameraFPSUTest::~CCameraFPSUTest()
{
}

void CCameraFPSUTest::SetUp()
{
	m_camera = CCameraFPS(m_defaultPos, m_defaultUp, 1.0f, 100.0f, 0.45f, 75);
}

void CCameraFPSUTest::TearDown()
{
}


//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------

TEST_F(CCameraFPSUTest, Movement)
{
	// Default tests
	EXPECT_EQ(m_defaultPos, m_camera.GetPosition()) << "Expected camera to at default position";
	EXPECT_EQ(m_defaultPos, m_camera.GetPrevPosition()) << "Expected camera prev position to be at default position";
	EXPECT_EQ(m_defaultLook, m_camera.GetLook()) << "Expected camera look to be at default look";
	EXPECT_EQ(m_defaultUp, m_camera.GetUp()) << "Expected camera up to be at default up";

	float amtMove = 10;
	glm::vec3 expectPos = m_defaultPos;
	glm::vec3 expectLook = m_defaultLook;
	glm::vec3 expectUp = m_defaultUp;

	// Camera uses right handed coordinate system 

	// Move forward test
	expectPos.z -= amtMove;
	expectLook.z -= amtMove;
	m_camera.MoveForward(amtMove);
	m_camera.Update();
	EXPECT_EQ(expectPos, m_camera.GetPosition()) << "Unexpected camera position after MoveForward";
	EXPECT_EQ(m_defaultPos, m_camera.GetPrevPosition()) << "Unexpected camera prev position after MoveForward";
	EXPECT_EQ(expectLook, m_camera.GetLook()) << "Unexpected camera look after MoveForward";
	EXPECT_EQ(expectUp, m_camera.GetUp()) << "Unexpected camera up after MoveForward";

	// Move back test
	// Update move value and record previous pos
	glm::vec3 prevPos = m_camera.GetPosition();
	amtMove = 20;
	expectPos.z += amtMove;
	expectLook.z += amtMove;
	m_camera.MoveBack(amtMove);
	m_camera.Update();
	EXPECT_EQ(expectPos, m_camera.GetPosition()) << "Unexpected camera position after MoveBack";
	EXPECT_EQ(prevPos, m_camera.GetPrevPosition()) << "Unexpected camera prev position after MoveBack";
	EXPECT_EQ(expectLook, m_camera.GetLook()) << "Unexpected camera look after MoveBack";
	EXPECT_EQ(expectUp, m_camera.GetUp()) << "Unexpected camera up after MoveBack";

	// Move left test
	prevPos = m_camera.GetPosition();
	amtMove = 5;
	expectPos.x -= amtMove;
	expectLook.x -= amtMove;
	m_camera.StrafeLeft(amtMove);
	m_camera.Update();
	EXPECT_EQ(expectPos, m_camera.GetPosition()) << "Unexpected camera position after StrafeLeft";
	EXPECT_EQ(prevPos, m_camera.GetPrevPosition()) << "Unexpected camera prev position after StrafeLeft";
	EXPECT_EQ(expectLook, m_camera.GetLook()) << "Unexpected camera look after StrafeLeft";
	EXPECT_EQ(expectUp, m_camera.GetUp()) << "Unexpected camera up after StrafeLeft";

	// Move right test
	prevPos = m_camera.GetPosition();
	amtMove = 15;
	expectPos.x += amtMove;
	expectLook.x += amtMove;
	m_camera.StrafeRight(amtMove);
	m_camera.Update();
	EXPECT_EQ(expectPos, m_camera.GetPosition()) << "Unexpected camera position after StrafeRight";
	EXPECT_EQ(prevPos, m_camera.GetPrevPosition()) << "Unexpected camera prev position after StrafeRight";
	EXPECT_EQ(expectLook, m_camera.GetLook()) << "Unexpected camera look after StrafeRight";
	EXPECT_EQ(expectUp, m_camera.GetUp()) << "Unexpected camera up after StrafeRight";

	// Check angle default
	EXPECT_EQ(0, m_camera.GetHorizontalAngle()) << "Expected default horizontal angle to be 0";
	EXPECT_EQ(0, m_camera.GetVerticalAngle()) << "Expected default vertical angle to be 0";

	// Set test
	float angle = 90;
	m_camera.SetHorizontalAngle(angle);
	m_camera.SetVerticalAngle(angle);
	EXPECT_EQ(angle, m_camera.GetHorizontalAngle()) << "Unexpected horizontal angle after Set";
	EXPECT_EQ(angle, m_camera.GetVerticalAngle()) << "Unexpected vertical angle after Set";

	// Reset to 0 and test rotates
	m_camera.SetHorizontalAngle(0);
	m_camera.SetVerticalAngle(0);
	angle = -90;
	expectLook.z += 1;
	expectLook.x -= 1;
	float expectAngle = (angle * (glm::pi<float>() / 180)) * -1;	// Right angled coordinate system
	m_camera.RotateYaw(angle);
	m_camera.Update();
	EXPECT_EQ(expectPos, m_camera.GetPosition()) << "Position should not change after RotateYaw";
	EXPECT_EQ(expectAngle, m_camera.GetHorizontalAngle()) << "Unexpected horizontal angle after RotateYaw";
	EXPECT_EQ(0, m_camera.GetVerticalAngle()) << "Unexpected vertical angle after RotateYaw";
	EXPECT_EQ(expectLook, m_camera.GetLook()) << "Unexpected camera look after RotateYaw";

	// Do the look test later for pitch....
	angle = 45;
	//expectLook.x += 1;
	//expectLook.y += 1;
	expectAngle = angle * (glm::pi<float>() / 180);
	m_camera.RotatePitch(angle);
	m_camera.Update();
	EXPECT_EQ(expectPos, m_camera.GetPosition()) << "Position should not change after RotatePitch";
	EXPECT_EQ(expectAngle, m_camera.GetVerticalAngle()) << "Unexpected vertical angle after RotatePitch";
	//EXPECT_EQ(expectLook, m_camera.GetLook()) << "Unexpected camera look after RotatePitch";
}