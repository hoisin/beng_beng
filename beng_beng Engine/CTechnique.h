//--------------------------------------------------------------------------
//
//	Base shader technique class
//
//--------------------------------------------------------------------------

#ifndef __CTECHNIQUE_H__
#define __CTECHNIQUE_H__

#include <gl/glew.h>
#include <gl/wglew.h>
#include <list>
#include "Errors.h"

class CTechnique
{
public:
	CTechnique();
	virtual ~CTechnique();

	virtual ErrorId VInit();

	void Enable();

	bool IsInit() const;

protected:
	ErrorId AddShader(GLenum shaderType, const char* pShaderText);

	ErrorId Finialise();

	GLint GetUniformLocation(const char* pUniformName);

	GLint GetProgramParam(GLint param);

protected:
	GLuint m_shaderProg;

	bool m_bInit;

	typedef std::list<GLuint> ShaderObjList;
	ShaderObjList m_shaderObjList;
};

#endif