//--------------------------------------------------------------------------
//
//	Emitter object
//
//--------------------------------------------------------------------------
#pragma once

#include "CObject.h"

class CEmitter : public CObject
{
public:
	CEmitter();
	virtual  ~CEmitter();

	virtual void Update(float deltaT);

	void SetParticleSpawnPerTick(int particles);
	void SetParticleSpawnRate(float tick);

	int GetParticleSpawnPerTick() const;
	float GetParticleSpawnRate() const;

protected:
	float m_spawnRate;
	float m_tickCount;
	int m_spawnPerTick;
};

