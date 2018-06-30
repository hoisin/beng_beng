//--------------------------------------------------------------------------
//
//	20/03/2014
//
//	Class managing OpenGL stuff.....
//
//	This class should handle OpenGL specific setup & call related to drawing.
//
//	Author: Matt © 2014
//
//--------------------------------------------------------------------------

#ifndef __COPENGL_H__
#define __COPENGL_H__

#define OPENGL_CLASS_NAME "OpenGL_3_3_App"

#include <gl/glew.h>
#include <gl/wglew.h>
#include <Windows.h>
#include <iostream>

class CVertexBuffer;
class CIndexBuffer;
class CShader;


class COpenGL
{
//public:
//	enum GBUFFER_TEXTURE_TYPE {
//		GBUFFER_TEXTURE_TYPE_POSITION,
//		GBUFFER_TEXTURE_TYPE_DIFFUSE,
//		GBUFFER_TEXTURE_TYPE_NORMAL,
//		GBUFFER_TEXTURE_TYPE_TEXCOORD,
//		GBUFFER_NUM_TEXTURES
//	};

public:
	COpenGL();
	~COpenGL();

	bool InitOpenGL(HINSTANCE hInstance, HWND* hwnd, int majorVer, int minorVer, int winWidth,
		int winHeight, WNDPROC funcCallback);

	bool ResizeOpenGLViewportFull();
	void ReleaseOpenGLControl();

	bool IsInitialised();

	// Shader operations
	// Thinking of removing and leaving to corresponding classes to handle GL calls
	void SetCurrentTexture(GLuint texture);
	GLuint GetCurrentTexture() const;
	void SetCurrentShader(CShader* pNewShader);
	CShader* GetCurrentShader() const;

	void BeginDraw();
	void EndDraw();

	void RenderBuffer(CVertexBuffer* pVertBuffer, CIndexBuffer* pIndexBuffer);

	// May not need these
	void MakeCurrent();
	void ClearScreen();

	void Set2D(bool bFlag);
	void SetWireFrame(bool bFlag);

	void FlipBuffers();

	int GetScreenWidth() const;
	int GetScreenHeight() const;

private:
	bool InitGLEW(HINSTANCE hInstance, WNDPROC funcCallback);

	bool RegisterOpenGLClass(HINSTANCE hInstance, WNDPROC funcCallback);
	void UnregisterOpenGLClass(HINSTANCE hInstance);

private:
	HINSTANCE		m_hInstance;
	HWND*			m_pHwnd;
	CShader*		m_pRefCurrentShader;		// A reference, do not handle cleanup here
	HDC				m_hDC;
	HGLRC			m_hRC;
	int				m_iMajorVer;
	int				m_iMinorVer;
	int				m_winWidth;
	int				m_winHeight;
	GLuint			m_currentTexture;

	bool			m_b2D;
	
	bool		m_bInit;
	bool		m_bClassRegistered;
	bool		m_bGlewInitialised;
};


#endif