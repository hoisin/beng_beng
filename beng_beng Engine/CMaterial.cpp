#include "CMaterial.h"


CMaterial::CMaterial() : m_ambient(0.f), m_diffuse(0.f), m_specular(0.f), m_specExpo(1.f)
{
	m_ambientCol = glm::vec3(0, 0, 0);
	m_diffuseCol = glm::vec3(0, 0, 0);
	m_specularCol = glm::vec3(0, 0, 0);
}

CMaterial::CMaterial(const CMaterial & other)
{
	m_ambient = other.m_ambient;
	m_diffuse = other.m_diffuse;
	m_specular = other.m_specular;
	m_specExpo = other.m_specExpo;

	m_ambientCol = other.m_ambientCol;
	m_diffuseCol = other.m_diffuseCol;
	m_specularCol = other.m_specularCol;

	m_diffuseTextureID = other.m_diffuseTextureID;
	m_normalMapTextureID = other.m_normalMapTextureID;
}

CMaterial::~CMaterial()
{
}

void CMaterial::operator=(const CMaterial & other)
{
	m_ambient = other.m_ambient;
	m_diffuse = other.m_diffuse;
	m_specular = other.m_specular;
	m_specExpo = other.m_specExpo;

	m_ambientCol = other.m_ambientCol;
	m_diffuseCol = other.m_diffuseCol;
	m_specularCol = other.m_specularCol;

	m_diffuseTextureID = other.m_diffuseTextureID;
	m_normalMapTextureID = other.m_normalMapTextureID;
}

void CMaterial::SetAmbient(glm::float32 ambient)
{
	m_ambient = ambient;
}

void CMaterial::SetDiffuse(glm::float32 diffuse)
{
	m_diffuse = diffuse;
}

void CMaterial::SetSpecular(glm::float32 specular)
{
	m_specular = specular;
}

void CMaterial::SetSpecularExpo(glm::float32 specularExpo)
{
	m_specExpo = specularExpo;
}

void CMaterial::SetAmbientCol(const glm::vec3 & ambientCol)
{
	m_ambientCol = ambientCol;
}

void CMaterial::SetDiffuseCol(const glm::vec3 & diffuseCol)
{
	m_diffuseCol = diffuseCol;
}

void CMaterial::SetSpecularCol(const glm::vec3 specularCol)
{
	m_specularCol = specularCol;
}

void CMaterial::SetDiffuseTextureID(const std::string & textureID)
{
	m_diffuseTextureID = textureID;
}

void CMaterial::SetNormalMapTextureID(const std::string & textureID)
{
	m_normalMapTextureID = textureID;
}

glm::float32 CMaterial::GetAmbient() const
{
	return m_ambient;
}

glm::float32 CMaterial::GetDiffuse() const
{
	return m_diffuse;
}

glm::float32 CMaterial::GetSpecular() const
{
	return m_specular;
}

glm::float32 CMaterial::GetSpecExpo() const
{
	return m_specExpo;
}

glm::vec3 CMaterial::GetAmbientColour() const
{
	return m_ambientCol;
}

glm::vec3 CMaterial::GetDiffuseColour() const
{
	return m_diffuseCol;
}

glm::vec3 CMaterial::GetSpecularColour() const
{
	return m_specularCol;
}

const std::string & CMaterial::GetDiffuseTextureID() const
{
	return m_diffuseTextureID;
}

const std::string & CMaterial::GetNormalMapTextureID() const
{
	return m_normalMapTextureID;
}
