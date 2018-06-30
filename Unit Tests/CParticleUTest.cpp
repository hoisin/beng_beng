#include "CParticleUTest.h"

//--------------------------------------------------------------------------
// UTest class
//--------------------------------------------------------------------------

CParticleUTest::CParticleUTest()
{
}

CParticleUTest::~CParticleUTest()
{
}

void CParticleUTest::SetUp()
{
}

void CParticleUTest::TearDown()
{
}

//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------

TEST_F(CParticleUTest, SetGetTests)
{
	// Default state values
	EXPECT_EQ(0, m_testParticle.GetLifeTime()) << "Life should be 0 by default";
	EXPECT_EQ(0, m_testParticle.GetSpeed()) << "Speed should be 0 by default";

	float lifeTime = 10.0;
	float speed = 5.0;

	// Testing Set
	m_testParticle.SetLifeTime(lifeTime);
	m_testParticle.SetSpeed(speed);

	// Test set values
	EXPECT_EQ(lifeTime, m_testParticle.GetLifeTime()) << "Unexpected life time after Set";
	EXPECT_EQ(speed, m_testParticle.GetSpeed()) << "Unexpected speed after set";
}