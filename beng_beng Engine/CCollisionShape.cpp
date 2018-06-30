#include "CCollisionShape.h"

CCollisionShape::CCollisionShape() : m_type()
{
	Reset();
}

CCollisionShape::~CCollisionShape()
{
}

void CCollisionShape::UpdateBoundary(const glm::vec3 & newMin, const glm::vec3 & newMax)
{
	// Update min bound
	if (newMin.x < m_minBound.x)
		m_minBound.x = newMin.x;

	if (newMin.y < m_minBound.y)
		m_minBound.y = newMin.y;

	if (newMin.z < m_minBound.z)
		m_minBound.z = newMin.z;

	// Update max bound
	if (newMax.x > m_maxBound.x)
		m_maxBound.x = newMax.x;

	if (newMax.y > m_maxBound.y)
		m_maxBound.y = newMax.y;

	if (newMax.z > m_maxBound.z)
		m_maxBound.z = newMax.z;
}

void CCollisionShape::SetType(ECollisionShape type)
{
	m_type = type;
}

ECollisionShape CCollisionShape::GetType() const
{
	return m_type;
}

void CCollisionShape::operator=(const CCollisionShape & other)
{
	m_minBound = other.m_minBound;
	m_maxBound = other.m_maxBound;
	m_type = other.m_type;
}

//------------------------------------------------------------------
//
//	Reset(..)
//
//	Resets the min and max bound values to defaults
//
//------------------------------------------------------------------
void CCollisionShape::Reset()
{
	m_maxBound = glm::vec3(INT_FAST32_MIN, INT_FAST32_MIN, INT_FAST32_MIN);
	m_maxBound = glm::vec3(INT_FAST32_MAX, INT_FAST32_MAX, INT_FAST32_MAX);
}
