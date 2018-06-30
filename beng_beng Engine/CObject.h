//--------------------------------------------------------------------------
//
//	Base Object
//	- Base entity in the virtual world
//
//--------------------------------------------------------------------------
#pragma once

#include <string>
#include "glm\vec3.hpp"

enum EObjectType {
	EType_Object,		// Placeable static object, does nothing
	EType_Environment,
	EType_Dynamic,		// Object with movement capabilities
	EType_Emitter,
	EType_Particle,
	EType_Total
};

class CObject
{
public:
	CObject();
	virtual ~CObject();

	virtual void Update(float deltaT);

	void SetLocation(const glm::vec3& pos);

	void SetFacingDirection(const glm::vec3& rot);

	void SetPosition(const glm::vec3& pos);

	void SetPrevPosition(const glm::vec3& pos);

	void SetDirection(const glm::vec3& rot);

	void SetRotation(const glm::vec3& rot);

	void SetPrevRotation(const glm::vec3& rot);

	void SetModelID(const std::string& meshID);

	const glm::vec3& GetPosition() const;

	const glm::vec3& GetPrevPosition() const;

	const glm::vec3& GetDirection() const;

	const glm::vec3& GetRotation() const;

	const glm::vec3& GetPrevRotation() const;

	const std::string& GetModelID() const;

	virtual EObjectType GetType() const;

	void SetActive(bool bActive);

	bool GetActive() const;

	void SetScale(float scale);

	float GetScale() const;

protected:
	glm::vec3 m_position;
	glm::vec3 m_prevPosition;

	glm::vec3 m_direction;	
	glm::vec3 m_rotation;
	glm::vec3 m_prevRotation;

	//int m_MeshID
	std::string m_modelID;	// Visual representation of the object

	float m_scale;	// Scaling for model.

	bool m_bActive;
};
