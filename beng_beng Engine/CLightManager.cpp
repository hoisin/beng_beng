//--------------------------------------------------------------------------
//
//	11/03/2015
//
//	Light manager
//
//	Author: Matt © 2015
//
//--------------------------------------------------------------------------


#include "CLightManager.h"

CLightManager::CLightManager(void)
{
	m_maxPointLights = 10;
	m_maxSpotLights = 5;
}


CLightManager::~CLightManager(void)
{
}


bool CLightManager::CreateAmbientLight(const glm::vec3& colour, float intensity)
{
	// Create ambient light if non exist
	if (!m_bAmbLight) {

		auto newAmbLight = new SLight;
		newAmbLight->type = ELightType::eLightAmb;
		newAmbLight->colour = colour;
		newAmbLight->intensity = intensity;

		// Flag as already created light
		m_bAmbLight = true;

		return true;
	}

	// Fail if already an ambient light created
	return false;
}


bool CLightManager::CreateDirectionalLight(const glm::vec3& colour, float intensity, const glm::vec3& direction)
{
	return true;
}


bool CLightManager::CreatePointLight(const glm::vec3& colour, float intensity, const glm::vec3& position, float attenuation)
{
	return true;
}


bool CLightManager::CreateSpotLight(const glm::vec3& colour, float intensity, const glm::vec3& position, float attenuation,
	float coneAngle, float coneAttenuation)
{
	return true;
}
