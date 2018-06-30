//--------------------------------------------------------------------------
//
//	Particle Object
//
//--------------------------------------------------------------------------

#pragma once
#include "CObject.h"

enum EParticleType
{
	eGrav,
	eTotalParticleTypes
};

class CParticle : public CObject
{
public:
	CParticle();
	~CParticle();

	virtual void Update(float deltaT);

	void ResetTickCount();

	void SetLifeTime(float lifeTime);
	void SetSpeed(float speed);
	void SetParticleDirection(glm::vec3 direction);	// Testing

	float GetLifeTime() const;
	float GetSpeed() const;
	glm::vec3 GetParticleDirection() const;		// Testing

protected:
	float m_tickCount;
	float m_lifeTime;
	float m_speed;
	
	// Test variable
	glm::vec3 m_directionP;
	float m_angle;

};

