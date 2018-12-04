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

	void operator=(const CFwdRender& other);

	const std::string& GetVertexShaderPath() const;
	const std::string& GetFragmentShaderPath() const;

private:
	GLuint m_projViewMatLoc;
	GLuint m_worldMatLoc;
	GLuint m_invWorldMatLoc;
	GLuint m_diffuseTexSamplerLoc;

	std::string m_vertexShaderPath;
	std::string m_fragmentShaderPath;
};


#endif