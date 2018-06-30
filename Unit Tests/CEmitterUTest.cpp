#include "CEmitterUTest.h"

//--------------------------------------------------------------------------
// UTest class
//--------------------------------------------------------------------------

CEmitterUTest::CEmitterUTest()
{
}

CEmitterUTest::~CEmitterUTest()
{
}

void CEmitterUTest::SetUp()
{
}

void CEmitterUTest::TearDown()
{
}

//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------

TEST_F(CEmitterUTest, SetGetTests)
{
	// Defaults 
	EXPECT_EQ(0, m_testEmitter.GetParticleSpawnRate()) << "Unexpected default for spawn rate";
	EXPECT_EQ(0, m_testEmitter.GetParticleSpawnPerTick()) << "Unexpected default for spawn per tick";

	float spawnRate = 10.0;
	int spawnPerTick = 4;

	m_testEmitter.SetParticleSpawnRate(spawnRate);
	m_testEmitter.SetParticleSpawnPerTick(spawnPerTick);

	EXPECT_EQ(spawnRate, m_testEmitter.GetParticleSpawnRate()) << "Unexpected spawn rate after set";
	EXPECT_EQ(spawnPerTick, m_testEmitter.GetParticleSpawnPerTick()) << "Unexpected spawn per tick after set";
}