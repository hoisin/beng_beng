//--------------------------------------------------------------------------
//
//	11/03/2015
//
//	Light manager
//
//	Author: Matt © 2015
//
//--------------------------------------------------------------------------

#ifndef __CLIGHTMANAGER_H__
#define __CLIGHTMANAGER_H__

#include "GfxDefs.h"

#include <vector>

class CLight;

class CLightManager
{
public:
	CLightManager(void);
	~CLightManager(void);

	bool CreateAmbientLight(const glm::vec3& colour, float intensity);
	bool CreateDirectionalLight(const glm::vec3& colour, float intensity, const glm::vec3& direction);
	bool CreatePointLight(const glm::vec3& colour, float intensity, const glm::vec3& position, float attenuation);
	bool CreateSpotLight(const glm::vec3& colour, float intensity, const glm::vec3& position,
		float attenuation, float coneAngle, float coneAttenuation);


private:
	SLight m_ambientLight;
	SLight m_directionalLight;
	std::vector<SLight> m_pointLights;
	std::vector<SLight> m_spotLights;

	
	bool m_bAmbLight;			// Checks if we already have an ambient light created
	bool m_bDirLight;			// Checks if we already have an directional light created
	int m_maxPointLights;
	int m_maxSpotLights;

	int m_dirLightCount;		// Keep track of lights
	int m_pointLightCount;
	int m_spotLightCount;
};

#endif