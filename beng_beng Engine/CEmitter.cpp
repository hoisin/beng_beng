#include "CEmitter.h"
#include "CParticleManager.h"
#include "glm/geometric.hpp"


CEmitter::CEmitter() : m_tickCount(0), m_spawnPerTick(0), m_spawnRate(0)
{
}


CEmitter::~CEmitter()
{
}

void CEmitter::Update(float deltaT)
{
	m_tickCount += deltaT;

	if (m_tickCount > m_spawnRate) {
		for (int i = 0; i < m_spawnPerTick; i++) {
			CParticle* pParticle = PARTICLEMGR->SpawnParticle(m_position, "sphere_1");
			// Setup particle
			pParticle->SetSpeed(2.0);
			pParticle->SetLifeTime(1500);
			glm::vec3 temp(rand(), -rand(), rand());
			glm::vec3 norm = glm::normalize(temp);

			pParticle->SetParticleDirection(norm);
		}

		m_tickCount = 0;
	}
}

void CEmitter::SetParticleSpawnPerTick(int particles)
{
	m_spawnPerTick = particles;
}

void CEmitter::SetParticleSpawnRate(float tick)
{
	m_spawnRate = tick;
}

int CEmitter::GetParticleSpawnPerTick() const
{
	return m_spawnPerTick;
}

float CEmitter::GetParticleSpawnRate() const
{
	return m_spawnRate;
}
