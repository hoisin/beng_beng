#include "CCamera.h"
#include <glm\gtc\matrix_transform.hpp>

CCamera::CCamera(const glm::vec3 &pos, const glm::vec3 &up, const glm::vec3 &look, 
	float zNear, float zFar, float aspectRatio, float fov) : m_position(pos), m_up(up), m_look(look), m_prevPosition(pos),
	m_prevLook(look), m_zNear(zNear), m_zFar(zFar), m_aspectRatio(aspectRatio), m_fov(fov)
{
}

CCamera::CCamera(const CCamera& other)
{
	m_position = other.m_position;
	m_up = other.m_up;
	m_look = other.m_look;
	m_prevPosition = other.m_prevPosition;
	m_prevLook = other.m_prevLook;
	m_zNear = other.m_zNear;
	m_zFar = other.m_zFar;
	m_aspectRatio = other.m_aspectRatio;
	m_fov = other.m_fov;
}


CCamera::CCamera() : m_position(glm::vec3(0,0,0)), m_up(glm::vec3(0,0,0)), m_look(glm::vec3(0,0,0)),
	m_zNear(0), m_zFar(0), m_aspectRatio(0), m_fov(0)
{
}


CCamera::~CCamera()
{
}

void CCamera::Update()
{
	m_prevPosition = m_position;
	m_prevLook = m_look;
}


//------------------------------------------------------------------
//
//	GetProjectionMatrix(..)
//
//	Calculates and returns the projection matrix based on the camera
//	settings.
//	
//	Note: Optimisation possible by storing the calulated matrix and 
//	only recalculate when camera settings are changed
//
//------------------------------------------------------------------
glm::mat4 CCamera::GetProjectionMatrix()
{
	// Manual calculation of projection matrix
	//float h, w, q;

	//w = (float)1/tan(m_fovV*0.5);	// 1/tan(x) == cot(x)
	//h = (float)1/tan(m_fovV*0.5);	// 1/tan(x) == cot(x)
	//q = m_zFar/(m_zFar - m_zNear);

	//glm::mat4 projMat = glm::mat4(1.0f);

	//projMat[0].x = w;
	//projMat[1].y = h;
	//projMat[2].z = q;
	//projMat[3].z = -q*m_zNear;
	//projMat[2].w = 1;

	//return projMat;

	// Consider using radians for FoV
	return glm::perspective(m_fov, m_aspectRatio, m_zNear, m_zFar);
}


//------------------------------------------------------------------
//
//	GetViewMatrix(..)
//
//	Calculates and returns the view matrix based on the camera
//	settings.
//	
//	Note: Optimisation possible by storing the calulated matrix and 
//	only recalculate when camera settings are changed
//
//------------------------------------------------------------------
glm::mat4 CCamera::GetViewMatrix()
{
	return glm::lookAt(m_position, m_look, m_up);
}

//------------------------------------------------------------------
//
//	GetViewMatrix(..)
//
//	Params:
//	interpTick - value between 1 and 0
//
//	Calculates and returns the view matrix based on the camera
//	settings by interpolating between previous and current state
//	
//	Note: Optimisation possible by storing the calulated matrix and 
//	only recalculate when camera settings are changed
//
//------------------------------------------------------------------
glm::mat4 CCamera::GetViewMatrix(float interpTick)
{
	glm::vec3 interpPos = glm::mix(m_prevPosition, m_position, interpTick);
	glm::vec3 interpLook = glm::mix(m_prevLook, m_look, interpTick);

	return glm::lookAt(interpPos, interpLook, m_up);
}

void CCamera::SetPosition(const glm::vec3 & position)
{
	m_position = position;
}

void CCamera::SetUp(const glm::vec3 & up)
{
	m_up = up;
}

void CCamera::SetLook(const glm::vec3 look)
{
	m_look = look;
}

void CCamera::SetPrevPosition(const glm::vec3 prevPosition)
{
	m_prevPosition = prevPosition;
}

void CCamera::SetPrevLook(const glm::vec3 prevLook)
{
	m_prevLook = prevLook;
}

void CCamera::SetNear(float near)
{
	m_zNear = near;
}

void CCamera::SetFar(float far)
{
	m_zFar = far;
}

void CCamera::SetAspectRatio(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
}

void CCamera::SetFOV(float fov)
{
	m_fov = fov;
}

const glm::vec3 & CCamera::GetPosition() const
{
	return m_position;
}

const glm::vec3 & CCamera::GetUp() const
{
	return m_up;
}

const glm::vec3 & CCamera::GetLook() const
{
	return m_look;
}

const glm::vec3 & CCamera::GetPrevPosition() const
{
	return m_prevPosition;
}

const glm::vec3 & CCamera::GetPrevLook() const
{
	return m_prevLook;
}

float CCamera::GetNear() const
{
	return m_zNear;
}

float CCamera::GetFar() const
{
	return m_zFar;
}

float CCamera::GetAspectRatio() const
{
	return m_aspectRatio;
}

float CCamera::GetFOV() const
{
	return m_fov;
}


//------------------------------------------------------------------
//
//	ResetAngle180(..)
//
//	Params:
//	angle	-	angle in degrees
//
//	Calulates the passed angle to be in between -180 to 180
//
//------------------------------------------------------------------
float CCamera::ResetAngle180(float angle)
{
	float temp = angle;
	if(angle > (180 * (glm::pi<float>()/180)))
		temp +=  (float)(-360 * (glm::pi<float>() /180));

	if(angle < (-180 * (glm::pi<float>() /180)))
		temp +=  (float)(360 * (glm::pi<float>() /180));

	return temp;
}


//------------------------------------------------------------------
//
//	RestrictAngle90(..)
//
//	Params:
//	angle	-	angle in degrees
//
//	Calulates the passed angle to be in between -90 to 90
//
//------------------------------------------------------------------
float CCamera::RestrictAngle90(float angle)
{
	float temp = angle;

	// Using 89.99 to avoid gimbal lock
	float maxBound = (float)(89.99*(glm::pi<float>() /180));
	float minBound = (float)(-89.99*(glm::pi<float>() /180));

	if(angle > maxBound)
		temp = maxBound;

	if(angle < minBound)
		temp = minBound;

	return temp;
}