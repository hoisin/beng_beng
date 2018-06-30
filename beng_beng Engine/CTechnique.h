///--------------------------------------------------------------------------
//
//	Base shader technique class
//
//--------------------------------------------------------------------------

#ifndef __CTECHNIQUE_H__
#define __CTECHNIQUE_H__

#include <gl/glew.h>
#include <gl/wglew.h>
#include <list>

class CTechnique
{
public:
	CTechnique();
	virtual ~CTechnique();

	virtual bool VInit();

	void Enable();

	bool IsInit() const;

protected:
	bool AddShader(GLenum shaderType, const char* pShaderText);

	bool Finialise();

	GLint GetUniformLocation(const char* pUniformName);

	GLint GetProgramParam(GLint param);

protected:
	GLuint m_shaderProg;

	bool m_bInit;

	typedef std::list<GLuint> ShaderObjList;
	ShaderObjList m_shaderObjList;
};

#endif