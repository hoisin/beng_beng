#include "CFwdRender.h"

CFwdRender::CFwdRender(const std::string& vertexShaderPath,
	const std::string& fragmentShaderPath)
{
	m_vertexShaderPath = vertexShaderPath;
	m_fragmentShaderPath = fragmentShaderPath;
}

CFwdRender::CFwdRender(const CFwdRender & other)
{
	m_vertexShaderPath = other.m_vertexShaderPath;
	m_fragmentShaderPath = other.m_fragmentShaderPath;
}

CFwdRender::CFwdRender() : m_vertexShaderPath(""), m_fragmentShaderPath("")
{
}


CFwdRender::~CFwdRender()
{
}

//------------------------------------------------------------------
//
//	VInit()
//
//	Override parent VInit.
//
//------------------------------------------------------------------
ErrorId CFwdRender::VInit()
{
	// Base class should set m_bInit if successful
	ErrorId error = CTechnique::VInit();

	// Fail if error
	if (IsError(error))
	{
		m_bInit = false;
		return error;
	}

	error = AddShader(GL_VERTEX_SHADER, m_vertexShaderPath.c_str());
	if (IsError(error))
	{
		m_bInit = false;
		return error;
	}

	// If successful adding vertex shader 
	error = AddShader(GL_FRAGMENT_SHADER, m_fragmentShaderPath.c_str());
	if (IsError(error))
	{
		m_bInit = false;
		return error;
	}

	// If successful adding fragment shader
	error = Finialise();
	if (IsError(error))
	{
		m_bInit = false;
		return error;
	}

	// If successful linking and finalising shader program
	m_projViewMatLoc = GetUniformLocation("projViewMatrix");
	m_worldMatLoc = GetUniformLocation("worldMatrix");
	m_invWorldMatLoc = GetUniformLocation("invWorldMat");
	m_diffuseTexSamplerLoc = GetUniformLocation("diffuseTextureSampler");

	// Point lights
	m_pointLightLoc = GetUniformLocation("pointLights");
	m_pointLightColorLoc = GetUniformLocation("lightColor");
	m_pointLightIntensityLoc = GetUniformLocation("lightIntensity");
	m_pointLightAttenuationLoc = GetUniformLocation("attenuation");
	m_activePointLightsLoc = GetUniformLocation("activePointLights");

	// Spot lights
	m_spotLightLoc = GetUniformLocation("spotLights");
	m_spotLightColorLoc = GetUniformLocation("spotLightColor");
	m_spotLightDirLoc = GetUniformLocation("spotLightDir");
	m_spotLightIntensityLoc = GetUniformLocation("spotLightIntensity");
	m_spotLightAttenLoc = GetUniformLocation("spotLightAtten");
	m_spotLightConeAngleLoc = GetUniformLocation("spotLightConeAngle");
	m_activeSpotLightsLoc = GetUniformLocation("activeSpotLights");

	// If fail to get uniforms
	if (m_projViewMatLoc < 0 || m_worldMatLoc < 0 || m_diffuseTexSamplerLoc < 0 ||
		m_pointLightLoc < 0 || m_pointLightColorLoc < 0 || m_pointLightIntensityLoc < 0 || m_pointLightAttenuationLoc < 0 || m_activePointLightsLoc < 0 ||
		m_spotLightLoc < 0 || m_spotLightColorLoc < 0 || m_spotLightDirLoc < 0 || m_spotLightIntensityLoc < 0 ||
		m_spotLightAttenLoc < 0 || m_spotLightConeAngleLoc < 0 || m_activeSpotLightsLoc < 0)
	{
		m_bInit = false;
		return ERRORID_SHADER_UNIFORM_GET_FAILED;
	}

	return error;
}


void CFwdRender::SetProjViewMatrix(const glm::mat4& projViewMat)
{
	glUniformMatrix4fv(m_projViewMatLoc, 1, GL_FALSE, (const GLfloat*)&projViewMat[0][0]);
}


void CFwdRender::SetWorldMatrix(const glm::mat4& worldMat)
{
	glUniformMatrix4fv(m_worldMatLoc, 1, GL_FALSE, (const GLfloat*)&worldMat[0][0]);
}


void CFwdRender::SetInvWorldMatrx(const glm::mat4& invWorldMat)
{
	glUniformMatrix4fv(m_invWorldMatLoc, 1, GL_FALSE, (const GLfloat*)&invWorldMat);
}


void CFwdRender::SetDiffuseTexture(GLuint textureID)
{
	glUniform1i(m_diffuseTexSamplerLoc, textureID);
}

void CFwdRender::SetPointLight(UINT idx, const glm::vec3 & pos, const glm::vec3 & color, float lightIntensity, float attenuation)
{
	if (idx < MAX_POINT_LIGHTS)
	{
		m_pointLightPos[idx] = pos;
		m_pointLightCol[idx] = color;
		m_pointLightIntensity[idx] = lightIntensity;
		m_pointLightAttenuation[idx] = attenuation;
	}
}

void CFwdRender::SetSpotLight(UINT idx, const glm::vec3 & pos, const glm::vec3 & color, float coneAngle,
	const glm::vec3& dir, float intensity, float atten, float coneAtten)
{
	if (idx < MAX_SPOT_LIGHTS)
	{
		m_spotLightPos[idx] = pos;
		m_spotLightCol[idx] = color;
		m_spotLightDir[idx] = dir;
		m_spotLightIntensity[idx] = intensity;
		m_spotLightAtten[idx] = atten;
		m_spotLightConeAngle[idx] = coneAngle;
	}
}

void CFwdRender::UploadPointLightData()
{
	// Point lights
	glUniform1i(m_activePointLightsLoc, m_activePointLights);
	glUniform3fv(m_pointLightLoc, MAX_POINT_LIGHTS, &m_pointLightPos[0].x);
	glUniform3fv(m_pointLightColorLoc, MAX_POINT_LIGHTS, &m_pointLightCol[0].r);
	glUniform1fv(m_pointLightIntensityLoc, MAX_POINT_LIGHTS, &m_pointLightIntensity[0]);
	glUniform1fv(m_pointLightAttenuationLoc, MAX_POINT_LIGHTS, &m_pointLightAttenuation[0]);

	// Spot lights
	glUniform1i(m_activeSpotLightsLoc, m_activeSpotLights);
	glUniform3fv(m_spotLightLoc, MAX_SPOT_LIGHTS, &m_spotLightPos[0].x);
	glUniform3fv(m_spotLightColorLoc, MAX_SPOT_LIGHTS, &m_spotLightCol[0].r);
	glUniform3fv(m_spotLightDirLoc, MAX_SPOT_LIGHTS, &m_spotLightDir[0].x);
	glUniform1fv(m_spotLightIntensityLoc, MAX_SPOT_LIGHTS, &m_spotLightIntensity[0]);
	glUniform1fv(m_spotLightAttenLoc, MAX_SPOT_LIGHTS, &m_spotLightAtten[0]);
	glUniform1fv(m_spotLightConeAngleLoc, MAX_SPOT_LIGHTS, &m_spotLightConeAngle[0]);
}

void CFwdRender::SetActivePointLights(UINT lights)
{
	m_activePointLights = lights;
	if (m_activePointLights > MAX_POINT_LIGHTS)
		m_activePointLights = MAX_POINT_LIGHTS;
}

void CFwdRender::SetActiveSpotLight(UINT lights)
{
	m_activeSpotLights = lights;
	if (m_activeSpotLights > MAX_SPOT_LIGHTS)
		m_activeSpotLights = MAX_SPOT_LIGHTS;
}

void CFwdRender::operator=(const CFwdRender & other)
{
	m_vertexShaderPath = other.m_vertexShaderPath;
	m_fragmentShaderPath = other.m_fragmentShaderPath;
	m_projViewMatLoc = other.m_projViewMatLoc;
	m_worldMatLoc = other.m_worldMatLoc;
	m_invWorldMatLoc = other.m_invWorldMatLoc;
	m_pointLightLoc = other.m_pointLightLoc;
	m_pointLightColorLoc = other.m_pointLightColorLoc;
	m_pointLightIntensityLoc = other.m_pointLightIntensityLoc;
	m_pointLightAttenuationLoc = other.m_pointLightAttenuationLoc;
	m_spotLightConeAngleLoc = other.m_spotLightConeAngleLoc;
	m_activePointLightsLoc = other.m_activePointLightsLoc;

	// Copy light data????
}

const std::string & CFwdRender::GetVertexShaderPath() const
{
	return m_vertexShaderPath;
}

const std::string & CFwdRender::GetFragmentShaderPath() const
{
	return m_fragmentShaderPath;
}
