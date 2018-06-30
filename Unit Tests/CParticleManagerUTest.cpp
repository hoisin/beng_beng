#include "CParticleManagerUTest.h"
#include "CObject.h"

//--------------------------------------------------------------------------
// UTest class
//--------------------------------------------------------------------------

CParticleManagerUTest::CParticleManagerUTest()
{
}

CParticleManagerUTest::~CParticleManagerUTest()
{
}

void CParticleManagerUTest::SetUp()
{
	m_testMgr = PARTICLEMGR->GetInstance();
}

void CParticleManagerUTest::TearDown()
{
	m_testMgr->Release();
}

//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------

TEST_F(CParticleManagerUTest, GeneralTests)
{
	EXPECT_EQ(0, PARTICLEMGR->GetParticleCacheCount()) << "Cache count should be 0 by default";
	EXPECT_EQ(nullptr, PARTICLEMGR->SpawnParticle(glm::vec3(), "TestMeshID")) << "Expected nullptr on spawn when no cached particles";

	int particleCacheCount = 300;
	bool result = PARTICLEMGR->CacheParticles(particleCacheCount);

	EXPECT_EQ(true, result) << "Failed to cache particles";
	EXPECT_EQ(particleCacheCount, PARTICLEMGR->GetParticleCacheCount()) << "Unexpected particle cache count";

	std::list<CObject*> activeParticles;
	PARTICLEMGR->GetActiveParticles(&activeParticles);
	EXPECT_EQ(0, (int)activeParticles.size()) << "Expected particle list to be empty when not spawned any particles";

	CParticle* testParticle = PARTICLEMGR->SpawnParticle(glm::vec3(), "TestMeshID");
	testParticle->SetModelID("TestModelID");
	PARTICLEMGR->GetActiveParticles(&activeParticles);
	EXPECT_NE(nullptr, testParticle) << "Unexpected NULL ptr, should return a particle with cached particles";
	EXPECT_LT(0, (int)activeParticles.size()) << "Particle list should not be empty after setting a particle active & model ID";
}