//--------------------------------------------------------------------------
//
//	Particle manager
//  - Handles particles separately from CObjects in world although derive 
//		from same base class
//
//--------------------------------------------------------------------------

#pragma once

#include "CParticle.h"
#include "CEmitter.h"

#include <vector>
#include <list>

class CParticleManager
{
public:
	~CParticleManager();

	bool CacheParticles(int cacheCount);
	CParticle* SpawnParticle(const glm::vec3& spawnPos, const std::string& meshID);

	void UpdateParticles(float deltaT);

	static CParticleManager* GetInstance();

	void GetActiveParticles(std::list<CObject*>* outList);

	void CleanUp();
	
	void Release();

	int GetParticleCacheCount() const;

private:
	CParticleManager();

protected:
	std::vector<CParticle> m_particles;

	static CParticleManager* m_pInstance;

};

#define PARTICLEMGR CParticleManager::GetInstance()