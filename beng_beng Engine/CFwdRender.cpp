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
bool CFwdRender::VInit()
{
	// Base class should set m_bInit if successful
	if (!CTechnique::VInit())
		m_bInit = false;

	// If Base init OK
	if (m_bInit)
	{
		if (!AddShader(GL_VERTEX_SHADER, m_vertexShaderPath.c_str()))
			m_bInit = false;
		
		// If successful adding vertex shader 
		if (m_bInit)
		{
			if (!AddShader(GL_FRAGMENT_SHADER, m_fragmentShaderPath.c_str()))
				m_bInit = false;

			// If successful adding fragment shader
			if (m_bInit)
			{
				if (!Finialise())
					m_bInit = false;

				// If successful linking and finalising shader program
				if (m_bInit)
				{
					m_projViewMatLoc = GetUniformLocation("projViewMatrix");
					m_worldMatLoc = GetUniformLocation("worldMatrix");
					m_invWorldMatLoc = GetUniformLocation("invWorldMat");
					m_diffuseTexSamplerLoc = GetUniformLocation("diffuseTextureSampler");

					// If fail to get uniforms
					if (m_projViewMatLoc < 0 || m_worldMatLoc < 0 || m_diffuseTexSamplerLoc < 0)
						m_bInit = false;
				}
			}
		}
	}

	return m_bInit;
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

void CFwdRender::operator=(const CFwdRender & other)
{
	m_vertexShaderPath = other.m_vertexShaderPath;
	m_fragmentShaderPath = other.m_fragmentShaderPath;
	m_projViewMatLoc = other.m_projViewMatLoc;
	m_worldMatLoc = other.m_worldMatLoc;
	m_invWorldMatLoc = other.m_invWorldMatLoc;
}

const std::string & CFwdRender::GetVertexShaderPath() const
{
	return m_vertexShaderPath;
}

const std::string & CFwdRender::GetFragmentShaderPath() const
{
	return m_fragmentShaderPath;
}
