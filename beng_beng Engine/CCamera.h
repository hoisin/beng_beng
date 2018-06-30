//--------------------------------------------------------------------------
//
//	11/04/2014
//
//	Base camera class
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __CCAMERA_H__
#define __CCAMERA_H__

#include <glm\glm.hpp>
#include <glm\gtc\constants.hpp>

class CCamera
{
public:
	CCamera(const glm::vec3 &pos, const glm::vec3 &up, const glm::vec3 &look, 
		float zNear, float zFar, float aspectRatio, float fov);
	CCamera(const CCamera& other);
	CCamera();
	virtual ~CCamera();

	virtual void Update();

	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetViewMatrix();
	virtual glm::mat4 GetViewMatrix(float interpTick);

	void SetPosition(const glm::vec3& position);
	void SetUp(const glm::vec3& up);
	void SetLook(const glm::vec3 look);
	void SetPrevPosition(const glm::vec3 prevPosition);
	void SetPrevLook(const glm::vec3 prevLook);
	void SetNear(float near);
	void SetFar(float far);
	void SetAspectRatio(float aspectRatio);
	void SetFOV(float fov);

	const glm::vec3& GetPosition() const;
	const glm::vec3& GetUp() const;
	const glm::vec3& GetLook() const;
	const glm::vec3& GetPrevPosition() const;
	const glm::vec3& GetPrevLook() const;
	float GetNear() const;
	float GetFar() const;
	float GetAspectRatio() const;
	float GetFOV() const;

protected:
	float ResetAngle180(float angle);		//resets angle back to 0 when over 180 or under -180
	float RestrictAngle90(float angle);		//restricts angle to 90 - (-90)

protected:
	// View matrix stuff
	glm::vec3 m_position;
	glm::vec3 m_up;
	glm::vec3 m_look;

	glm::vec3 m_prevPosition;
	glm::vec3 m_prevLook;

	// Projection matrix stuff
	float m_zNear;
	float m_zFar;
	float m_aspectRatio;
	float m_fov;
};

#endif