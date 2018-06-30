///--------------------------------------------------------------------------
//
//	Base shader technique class
//
//--------------------------------------------------------------------------
#include "CTechnique.h"
#include <fstream>
#include <string>

CTechnique::CTechnique() : m_shaderProg(0), m_bInit(false)
{
}


CTechnique::~CTechnique()
{
	for (const auto& it : m_shaderObjList) {
		glDeleteShader(it);
	}

	if (m_shaderProg != 0) {
		glDeleteProgram(m_shaderProg);
		m_shaderProg = 0;
	}
}

//------------------------------------------------------------------
//
//	VInit()
//
//	Virtual initialise functions, call first in derived classes
//	and then add custom behaviour.
//
//------------------------------------------------------------------
bool CTechnique::VInit()
{
	m_bInit = true;
	m_shaderProg = glCreateProgram();

	if (m_shaderProg == 0)
		m_bInit = false;

	return m_bInit;
}


//------------------------------------------------------------------
//
//	AddShader(..)
//
//	Params:
//	shaderType		-	The shader type to add
//	pFileName		-	The path to the shader file
//
//	Adds specified shader to this technique
//
//------------------------------------------------------------------
bool CTechnique::AddShader(GLenum shaderType, const char* pFileName)
{
	std::ifstream shaderStream(pFileName, std::ios::in);
	std::string shaderCode;

	// Attempt to open the shader file stream
	if (shaderStream.is_open()) {
		std::string line = "";
		while (std::getline(shaderStream, line))
			shaderCode += "\n" + line;

		shaderStream.close();
	}
	else
		return false;

	// Create shader object from specified shader type
	GLuint shaderObj = glCreateShader(shaderType);

	// Is valid?
	if (shaderObj == 0)
		return false;

	m_shaderObjList.push_back(shaderObj);

	// Load shader code and compile
	const GLchar* p[1];
	p[0] = shaderCode.c_str();
	GLint lengths[1] = { (GLint)shaderCode.size() };

	glShaderSource(shaderObj, 1, p, lengths);
	glCompileShader(shaderObj);

	// Check if successful compile
	GLint success;
	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar infoLog[1024];
		glGetShaderInfoLog(shaderObj, 1024, NULL, infoLog);
		OutputDebugStringA(infoLog);
		return false;
	}

	glAttachShader(m_shaderProg, shaderObj);
	return true;
}

//------------------------------------------------------------------
//
//	Finialise()
//
//	Finialises shader and links/compiles.
//
//------------------------------------------------------------------
bool CTechnique::Finialise()
{
	GLint success = 0;
	GLchar errorLog[1024] = { 0 };

	// Attempt to link loaded shader programs
	glLinkProgram(m_shaderProg);
	glGetProgramiv(m_shaderProg, GL_LINK_STATUS, &success);

	if (success == 0) {
		glGetProgramInfoLog(m_shaderProg, sizeof(errorLog), NULL, errorLog);
		OutputDebugString(errorLog);
		return false;
	}

	// Validate and check linked shader program
	glValidateProgram(m_shaderProg);
	glGetProgramiv(m_shaderProg, GL_VALIDATE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_shaderProg, sizeof(errorLog), NULL, errorLog);
		OutputDebugString(errorLog);
		return false;
	}

	// Remove unrequried loaded shader objects since we have linked shader program.
	for (auto it = m_shaderObjList.begin(); it != m_shaderObjList.end(); it++) 
		glDeleteShader(*it);
	
	m_shaderObjList.clear();
	return  true;
}

//------------------------------------------------------------------
//
//	Enable()
//
//	Sets current technique to use as shader program
//
//------------------------------------------------------------------
void CTechnique::Enable()
{
	glUseProgram(m_shaderProg);
}

bool CTechnique::IsInit() const
{
	return m_bInit;
}

//------------------------------------------------------------------
//
//	GetUniformLocation()
//
//	Params:
//	pUniformName	-	Name of uniform
//
//	Returns the location of the named uniform in shader
//
//------------------------------------------------------------------
GLint CTechnique::GetUniformLocation(const char* pUniformName)
{
	GLuint location = glGetUniformLocation(m_shaderProg, pUniformName);

	return location;
}

GLint CTechnique::GetProgramParam(GLint param)
{
	GLint ret;
	glGetProgramiv(m_shaderProg, param, &ret);
	return ret;
}