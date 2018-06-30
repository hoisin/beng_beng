//--------------------------------------------------------------------------
//
//	10/04/2015
//
//	Class which holds all information on a material
//
//	Author: Matt © 2015
//
//--------------------------------------------------------------------------

#ifndef __CMATERIAL_H__
#define __CMATERIAL_H__

#include "GfxDefs.h"

class CMaterial
{
public:
	CMaterial();
	CMaterial(const CMaterial& other);
	~CMaterial();

	void operator =(const CMaterial& other);

	void SetAmbient(glm::float32 ambient);
	void SetDiffuse(glm::float32 diffuse);
	void SetSpecular(glm::float32 specular);
	void SetSpecularExpo(glm::float32 specularExpo);
	void SetAmbientCol(const glm::vec3& ambientCol);
	void SetDiffuseCol(const glm::vec3& diffuseCol);
	void SetSpecularCol(const glm::vec3 specularCol);

	void SetDiffuseTextureID(const std::string& textureID);
	void SetNormalMapTextureID(const std::string& textureID);

	glm::float32 GetAmbient() const;
	glm::float32 GetDiffuse() const;
	glm::float32 GetSpecular() const;
	glm::float32 GetSpecExpo() const;
	glm::vec3 GetAmbientColour() const;
	glm::vec3 GetDiffuseColour() const;
	glm::vec3 GetSpecularColour() const;
	const std::string& GetDiffuseTextureID() const;
	const std::string& GetNormalMapTextureID() const;

//protected:
public:
	glm::float32 m_ambient;
	glm::float32 m_diffuse;
	glm::float32 m_specular;
	glm::float32 m_specExpo;

	glm::vec3 m_ambientCol;			// Ambient reflective colour
	glm::vec3 m_diffuseCol;			// Diffuse reflective colour
	glm::vec3 m_specularCol;		// Specular reflective colour

	std::string m_diffuseTextureID;
	std::string m_normalMapTextureID;
};


#endif