///--------------------------------------------------------------------------
//
//	26/08/2015
//
//	Techinque handing forward lighting implementation
//
//	Current handling:
//	Texture only.
//
//	Author: Matt © 2015
//
//--------------------------------------------------------------------------

#ifndef __CFWDLIGHTING_H__
#define __CFWDLIGHTING_H__

#include <string>
#include "glm\glm.hpp"
#include "CTechnique.h"

#define MAX_POINT_LIGHTS 20
#define MAX_SPOT_LIGHTS 20

class CFwdRender : public CTechnique
{
public:
	CFwdRender(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	CFwdRender(const CFwdRender& other);
	CFwdRender();
	~CFwdRender();

	ErrorId VInit() override;

	void SetProjViewMatrix(const glm::mat4& projViewMat);
	void SetWorldMatrix(const glm::mat4& worldMat);
	void SetInvWorldMatrx(const glm::mat4& invWorldMat);

	void SetDiffuseTexture(GLuint textureID);

	void SetPointLight(UINT idx, const glm::vec3& pos, const glm::vec3& color,
		float lightIntensity, float attenuation);

	void SetSpotLight(UINT idx, const glm::vec3& pos, const glm::vec3& color, float coneAngle,
		const glm::vec3& dir, float intensity, float atten, float coneAtten);

	void UploadPointLightData();

	void SetActivePointLights(UINT lights);
	void SetActiveSpotLight(UINT lights);

	void operator=(const CFwdRender& other);

	const std::string& GetVertexShaderPath() const;
	const std::string& GetFragmentShaderPath() const;

private:
	GLint m_projViewMatLoc;
	GLint m_worldMatLoc;
	GLint m_invWorldMatLoc;
	GLint m_diffuseTexSamplerLoc;

	// Point lights
	GLint m_pointLightLoc;				// Positions
	GLint m_pointLightColorLoc;			// Colors
	GLint m_pointLightIntensityLoc;		// Intensities
	GLint m_pointLightAttenuationLoc;	// Attenuations
	GLint m_activePointLightsLoc;		// Active point lights

	// Spot lights
	GLint m_spotLightLoc;				// Positions
	GLint m_spotLightColorLoc;			// Colors
	GLint m_spotLightDirLoc;			// Direction
	GLint m_spotLightIntensityLoc;		// Intensites
	GLint m_spotLightAttenLoc;			// Attenuations
	GLint m_spotLightConeAngleLoc;		// Cone angle
	GLint m_activeSpotLightsLoc;		// Active spot lights

	// Point Light testing
	int m_activePointLights = 1;
	glm::vec3 m_pointLightPos[MAX_POINT_LIGHTS];
	glm::vec3 m_pointLightCol[MAX_POINT_LIGHTS];
	float m_pointLightIntensity[MAX_POINT_LIGHTS];
	float m_pointLightAttenuation[MAX_POINT_LIGHTS];

	int m_activeSpotLights = 0;
	glm::vec3 m_spotLightPos[MAX_SPOT_LIGHTS];
	glm::vec3 m_spotLightCol[MAX_SPOT_LIGHTS];
	glm::vec3 m_spotLightDir[MAX_SPOT_LIGHTS];
	float m_spotLightIntensity[MAX_SPOT_LIGHTS];
	float m_spotLightAtten[MAX_SPOT_LIGHTS];
	float m_spotLightConeAngle[MAX_SPOT_LIGHTS];

	std::string m_vertexShaderPath;
	std::string m_fragmentShaderPath;
};


#endif