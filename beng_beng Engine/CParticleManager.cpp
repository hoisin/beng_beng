//--------------------------------------------------------------------------
//
//	Particle manager
//  - Handles particles separately from CObjects in world although derive 
//		from same base class
//
//--------------------------------------------------------------------------

#include "CParticleManager.h"

CParticleManager* CParticleManager::m_pInstance = nullptr;



CParticleManager::CParticleManager()
{
}


CParticleManager::~CParticleManager()
{
}

//------------------------------------------------------------------
//
//	CacheParticles(..)
//
//	Params:
//	cacheCount		-	amount to cache
//
//	Pre-cache particles so we don't dynamically allocate on each spawn
//
//------------------------------------------------------------------
bool CParticleManager::CacheParticles(int cacheCount)
{
	// Clear existing particle cache first
	CleanUp();

	for (int i = 0; i < cacheCount; i++) {
		//CParticle* newParticle = new CParticle;
		//m_particles.push_back(newParticle);
		m_particles.push_back(CParticle());
	}

	return true;
}

//------------------------------------------------------------------
//
//	SpawnParticle(..)
//
//	Params:
//	spawnPos		-	Position to spawn at
//	meshID			-	Mesh ID to use for particle
//
//	Spawns particle if found free in cache
//
//------------------------------------------------------------------
CParticle* CParticleManager::SpawnParticle(const glm::vec3 & spawnPos, const std::string & meshID)
{
	CParticle* returnParticle = nullptr;
	int count = 0;
	bool bSpawned = false;

	if ((int)m_particles.size() > 0)
	{
		while (!bSpawned && count < (int)m_particles.size()) {
			if (!m_particles[count].GetActive()) {
				m_particles[count].SetActive(true);
				m_particles[count].SetPosition(spawnPos);
				m_particles[count].SetModelID(meshID);

				returnParticle = &m_particles[count];
				bSpawned = true;
			}
			++count;
		}
	}
	return returnParticle;
}

//------------------------------------------------------------------
//
//	UpdateParticles(..)
//
//	Params:
//	deltaT		-	Time since last update
//
//	Updates all active particles
//
//------------------------------------------------------------------
void CParticleManager::UpdateParticles(float deltaT)
{
	for (int i = 0; i < (int)m_particles.size(); i++) {
		m_particles[i].Update(deltaT);
	}
}

//------------------------------------------------------------------
//
//	GetInstance(..)
//
//	Returns instance of particle manager
//
//------------------------------------------------------------------
CParticleManager * CParticleManager::GetInstance()
{
	if (!m_pInstance) {
		m_pInstance = new CParticleManager;
	}

	return m_pInstance;
}

//------------------------------------------------------------------
//
//	GetActiveParticles(..)
//
//	Params:
//	outList		-	Passed in list for adding to
//
//	Adds active particles to passed in object list
//
//------------------------------------------------------------------
void CParticleManager::GetActiveParticles(std::list<CObject*>* outList)
{
	for (int i = 0; i < (int)m_particles.size(); i++) {
		if (m_particles[i].GetActive() && (m_particles[i].GetModelID() != "")) {
			outList->push_back(&m_particles[i]);
		}
	}
}

//------------------------------------------------------------------
//
//	CleanUp(..)
//
//	Clears the particles cache
//
//------------------------------------------------------------------
void CParticleManager::CleanUp()
{
	m_particles.clear();
}

//------------------------------------------------------------------
//
//	Release(..)
//
//	Releases the particle manager instance
//
//------------------------------------------------------------------
void CParticleManager::Release()
{
	CleanUp();

	if (m_pInstance) {
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

int CParticleManager::GetParticleCacheCount() const
{
	return (int)m_particles.size();
}
