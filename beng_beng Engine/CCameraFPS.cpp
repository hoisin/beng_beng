#include "CCameraFPS.h"
#include <glm\gtc\matrix_transform.hpp>

CCameraFPS::CCameraFPS(const glm::vec3 &pos, const glm::vec3 &up , float zNear, float zFar, float aspectRatio, 
	float fovV, float horizAngle, float vertAngle) : 
	m_horizontalAngle(0), m_verticalAngle(0), m_prevHAngle(0), m_prevVAngle(0),
	CCamera(pos, up, glm::vec3(0,0,0), zNear, zFar, aspectRatio, fovV)
{
	//convert angles to radians
	m_horizontalAngle = (float)(horizAngle * (glm::pi<float>() /180));
	m_verticalAngle = (float)(vertAngle * (glm::pi<float>() /180));

	//right handed coordinate system
	//calculate interest
	m_look.x = m_position.x - sin(m_horizontalAngle)*cos(m_verticalAngle);
	m_look.y = m_position.y - sin(m_verticalAngle);
	m_look.z = m_position.z - cos(m_horizontalAngle)*cos(m_verticalAngle);

	// Initial
	m_prevLook = m_look;

	for (int i = 0; i < eTotalDirections; i++)
	{
		m_directionFlag[i] = false;
		m_moveAmount[i] = 0;
	}
}

CCameraFPS::CCameraFPS(const CCameraFPS & other) : CCamera(other)
{
	m_horizontalAngle = other.m_horizontalAngle;
	m_verticalAngle = other.m_verticalAngle;
}

CCameraFPS::CCameraFPS() : CCamera(), m_horizontalAngle(0), m_verticalAngle(0)
{
}


CCameraFPS::~CCameraFPS()
{
}

void CCameraFPS::Update()
{
	CCamera::Update();

	m_prevHAngle = m_horizontalAngle;
	m_prevVAngle = m_verticalAngle;

	// Store last look
	m_prevLook = m_look;

	// Rotate first
	m_look.x = m_position.x - sin(m_horizontalAngle)*cos(m_verticalAngle);
	m_look.y = m_position.y - sin(m_verticalAngle);
	m_look.z = m_position.z - cos(m_horizontalAngle)*cos(m_verticalAngle); 

	float viewDirX = m_look.x - m_position.x;
	float viewDirY = m_look.y - m_position.y;
	float viewDirZ = m_look.z - m_position.z;

	m_prevPosition = m_position;

	// Now do translations
	if (m_directionFlag[eForward])
	{
		m_position.x += m_moveAmount[eForward]*viewDirX;
		m_position.y += m_moveAmount[eForward]*viewDirY;	//remove this to prevent player moving up when facing up
		m_position.z += m_moveAmount[eForward]*viewDirZ;
	}

	if (m_directionFlag[eBackward])
	{
		m_position.x += m_moveAmount[eBackward] * viewDirX;
		m_position.y += m_moveAmount[eBackward] * viewDirY;	//remove this to prevent player moving up when facing up
		m_position.z += m_moveAmount[eBackward] * viewDirZ;
	}

	if (m_directionFlag[eLeft])
	{
		m_position.x += cos(m_horizontalAngle)*m_moveAmount[eLeft];
		m_position.z -= sin(m_horizontalAngle)*m_moveAmount[eLeft];
	}

	if (m_directionFlag[eRight])
	{
		m_position.x += cos(m_horizontalAngle)*m_moveAmount[eRight];
		m_position.z -= sin(m_horizontalAngle)*m_moveAmount[eRight];
	}

	// Update look after translations
	m_look.x = m_position.x - sin(m_horizontalAngle)*cos(m_verticalAngle);
	m_look.y = m_position.y - sin(m_verticalAngle);
	m_look.z = m_position.z - cos(m_horizontalAngle)*cos(m_verticalAngle);

	// Reset
	for (int i = 0; i < eTotalDirections; i++)
	{
		m_directionFlag[i] = false;
		m_moveAmount[i] = 0;
	}
}


void CCameraFPS::MoveForward(float amt)
{
	m_directionFlag[eForward] = true;
	m_moveAmount[eForward] = amt;
}


void CCameraFPS::MoveBack(float amt)
{
	m_directionFlag[eBackward] = true;
	m_moveAmount[eBackward] = amt * -1;
}


void CCameraFPS::StrafeLeft(float amt)
{
	m_directionFlag[eLeft] = true;
	m_moveAmount[eLeft] = amt;
	if (amt > 0)
		m_moveAmount[eLeft] *= -1;
}


void CCameraFPS::StrafeRight(float amt)
{
	m_directionFlag[eRight] = true;
	m_moveAmount[eRight] = amt;

	if (amt < 0)
		m_moveAmount[eRight] *= -1;
}


void CCameraFPS::RotateYaw(float degrees)
{
	m_prevHAngle = m_horizontalAngle;

	// For left handed system (D3DX) use +=
	m_horizontalAngle -= (float)(degrees * (glm::pi<float>() /180));

	float prevHAngle = ResetAngle180(m_prevHAngle);
	float hAngle = ResetAngle180(m_horizontalAngle);

	// Will be cases where value is over 180.
	// This is so that when reset, both previous and current are reset.
	// Otherwise interpolation  issues occur.
	if (prevHAngle != m_prevHAngle && hAngle != m_horizontalAngle)
	{
		m_prevHAngle = prevHAngle;
		m_horizontalAngle = hAngle;
	}

}


void CCameraFPS::RotatePitch(float degress)
{
	m_prevVAngle = m_verticalAngle;

	// For left handed system (D3DX) use -=
	m_verticalAngle += (float)(degress * (glm::pi<float>() /180));

	m_verticalAngle= RestrictAngle90(m_verticalAngle);
}

void CCameraFPS::SetHorizontalAngle(float angle)
{
	m_horizontalAngle = angle;
}

void CCameraFPS::SetVerticalAngle(float angle)
{
	m_verticalAngle = angle;
}

float CCameraFPS::GetHorizontalAngle() const
{
	return m_horizontalAngle;
}

float CCameraFPS::GetVerticalAngle() const
{
	return m_verticalAngle;
}

glm::mat4 CCameraFPS::GetViewMatrix(float interpTick)
{
	glm::vec3 interpPos = glm::mix(m_prevPosition, m_position, interpTick);
	float interpH = glm::mix(m_prevHAngle, m_horizontalAngle, interpTick);
	float interpV = glm::mix(m_prevVAngle, m_verticalAngle, interpTick);

	glm::vec3 interpLook;
	interpLook.x = interpPos.x - sin(interpH)*cos(interpV);
	interpLook.y = interpPos.y - sin(interpV);
	interpLook.z = interpPos.z - cos(interpH)*cos(interpV);

	return glm::lookAt(interpPos, interpLook, m_up);
}

