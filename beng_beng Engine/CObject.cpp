//--------------------------------------------------------------------------
//
//	Base Object
//	- Base entity in the virtual world
//
//--------------------------------------------------------------------------
#include "CObject.h"

CObject::CObject() : m_position(0,0,0), m_direction(0,0,0), m_rotation(0, 0, 0), m_modelID(""), m_bActive(false), m_scale(1)
{
}

CObject::~CObject()
{
}

void CObject::Update(float deltaT)
{
	// Does nothing
}

void CObject::SetLocation(const glm::vec3& pos)
{
	m_position = pos;
	m_prevPosition = pos;
}

void CObject::SetFacingDirection(const glm::vec3& rot)
{
	m_rotation = rot;
	m_prevRotation = rot;

}

void CObject::SetPosition(const glm::vec3 & pos)
{
	m_position = pos;
}

void CObject::SetPrevPosition(const glm::vec3 & pos)
{
	m_prevPosition = pos;
}

void CObject::SetDirection(const glm::vec3 & dir)
{
	m_direction = dir;
}

void CObject::SetRotation(const glm::vec3 & rot)
{
	m_rotation = rot;
}

void CObject::SetPrevRotation(const glm::vec3& rot)
{
	m_prevRotation = rot;
}

void CObject::SetModelID(const std::string & modelID)
{
	m_modelID = modelID;
}

const glm::vec3 & CObject::GetPosition() const
{
	return m_position;
}

const glm::vec3 & CObject::GetPrevPosition() const
{
	return m_prevPosition;
}

const glm::vec3 & CObject::GetDirection() const
{
	return m_direction;
}

const glm::vec3 & CObject::GetRotation() const
{
	return m_rotation;
}

const glm::vec3 & CObject::GetPrevRotation() const
{
	return m_prevRotation;
}

const std::string & CObject::GetModelID() const
{
	return m_modelID;
}

EObjectType CObject::GetType() const
{
	return EType_Object;
}

void CObject::SetActive(bool bActive)
{
	m_bActive = bActive;
}

bool CObject::GetActive() const
{
	return m_bActive;
}

void CObject::SetScale(float scale)
{
	m_scale = scale;
}

float CObject::GetScale() const
{
	return m_scale;
}
