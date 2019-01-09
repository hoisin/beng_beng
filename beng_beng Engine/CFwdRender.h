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

	void SetPointLight(const glm::vec3& pos, const glm::vec3& color,
		float lightIntensity, float attenuation);

	void operator=(const CFwdRender& other);

	const std::string& GetVertexShaderPath() const;
	const std::string& GetFragmentShaderPath() const;

private:
	GLuint m_projViewMatLoc;
	GLuint m_worldMatLoc;
	GLuint m_invWorldMatLoc;
	GLuint m_diffuseTexSamplerLoc;

	GLuint m_pointLightLoc;
	GLuint m_lightColorLoc;
	GLuint m_lightIntensityLoc;
	GLuint m_lightAttenuationLoc;

	std::string m_vertexShaderPath;
	std::string m_fragmentShaderPath;
};


#endif