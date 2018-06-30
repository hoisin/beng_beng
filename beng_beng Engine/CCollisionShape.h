//--------------------------------------------------------------------------
//
//	Collision shape interface
//

//--------------------------------------------------------------------------
#pragma once

#include "glm\vec3.hpp"

enum ECollisionShape {
	eUnknown,
	eSphere,
	eBox,
	eCollisionShapeTotal
};

class CCollisionShape
{
public:
	CCollisionShape();
	virtual ~CCollisionShape();

	virtual void UpdateBoundary(const glm::vec3& newMin, const glm::vec3& newMax);

	void SetType(ECollisionShape type);
	ECollisionShape GetType() const;

	void operator=(const CCollisionShape& other);

	// Resets the min/max bounds to default
	void Reset();

protected:
	glm::vec3 m_minBound;
	glm::vec3 m_maxBound;
	ECollisionShape m_type;
};
