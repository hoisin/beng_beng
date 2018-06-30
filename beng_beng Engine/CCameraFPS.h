//--------------------------------------------------------------------------
//
//	11/04/2014
//
//	FPS camera class
//	Movement in right-handed coordinate system
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __CCAMERAFPS_H__
#define __CCAMERAFPS_H__

#include "CCamera.h"

class CCameraFPS : public CCamera
{
	enum ECameraDirection 
	{
		eForward = 0,
		eBackward,
		eLeft,
		eRight,
		eTotalDirections
	};

public:
	CCameraFPS(const glm::vec3 &pos, const glm::vec3 &up, float zNear, float zFar, float aspectRatio, 
		float fovV, float horizAngle = 0.f, float vertAngle = 0.f);
	CCameraFPS(const CCameraFPS& other);
	CCameraFPS();
	~CCameraFPS();

	void Update() override;

	void MoveForward(float amt);
	void MoveBack(float amt);
	void StrafeLeft(float amt);
	void StrafeRight(float amt);

	void RotateYaw(float degrees);
	void RotatePitch(float degrees);

	void SetHorizontalAngle(float angle);
	void SetVerticalAngle(float angle);
	float GetHorizontalAngle() const;
	float GetVerticalAngle() const;

	virtual glm::mat4 GetViewMatrix(float interpTick);

protected:
	float m_horizontalAngle;
	float m_verticalAngle;

	float m_prevHAngle;
	float m_prevVAngle;

	bool m_directionFlag[eTotalDirections];
	float m_moveAmount[eTotalDirections];
};

#endif