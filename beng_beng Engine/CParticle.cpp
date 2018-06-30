#include "CParticle.h"
#include "glm/gtc/constants.hpp"


CParticle::CParticle() : m_tickCount(0), m_lifeTime(0), m_speed(0), m_angle(0)
{
}


CParticle::~CParticle()
{
}

void CParticle::Update(float deltaT)
{
	if (m_bActive) {
		m_tickCount += deltaT;
		m_angle += 0.1f;

		if (m_angle > 360)
			m_angle = 0;

		// Simple behaviour
		if (m_lifeTime < m_tickCount) {
			// die
			m_tickCount = 0;
			m_bActive = false;
		} else {
			m_prevRotation = m_rotation;
			m_rotation.y = m_angle;
			m_direction.z = std::cos(m_rotation.y * (glm::pi<float>() / 180.f));
			m_direction.x = std::sin(m_rotation.y * (glm::pi<float>() / 180.f));

			m_prevPosition = m_position;
			m_position += (m_directionP * m_speed);
		}
	}
}

void CParticle::ResetTickCount()
{
	m_tickCount = 0;
}

void CParticle::SetLifeTime(float lifeTime)
{
	m_lifeTime = lifeTime;
}

void CParticle::SetSpeed(float speed)
{
	m_speed = speed;
}

void CParticle::SetParticleDirection(glm::vec3 direction)
{
	m_directionP = direction;
}

float CParticle::GetLifeTime() const
{
	return m_lifeTime;
}

float CParticle::GetSpeed() const
{
	return m_speed;
}

glm::vec3 CParticle::GetParticleDirection() const
{
	return m_directionP;
}
