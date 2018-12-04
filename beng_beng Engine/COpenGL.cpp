#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glew32.lib")

#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "COpenGL.h"

COpenGL::COpenGL() : 
	m_hInstance(nullptr),
	m_pHwnd(nullptr), 
	m_iMajorVer(3), 
	m_iMinorVer(3), 
	m_winWidth(0),
	m_winHeight(0),
	m_b2D(false), 
	m_bInit(false), 
	m_bClassRegistered(false), 
	m_bGlewInitialised(false),
	m_currentTexture(0), 
	m_hRC(nullptr), 
	m_pRefCurrentShader(nullptr), 
	m_hDC(nullptr)
{
}

COpenGL::~COpenGL()
{
	ReleaseOpenGLControl();
}

//------------------------------------------------------------------
//
//	InitOpenGL(..)
//
//	Params:
//	hInstance		-	App instance
//	hwnd			-	Handle to window
//	majorVer		-	Major version of OpenGL
//	minorVer		-	Minor version of OpenGL
//	winWidth		-	Width of the window
//	winHeight		-	Height of the window
//	funcCallback	-	Callback function
//
//	Initialises OpenGL
//
//------------------------------------------------------------------
ErrorId COpenGL::InitOpenGL(HINSTANCE hInstance, HWND* pHwnd, int majorVer, int minorVer, int winWidth,
	int winHeight, WNDPROC funcCallback)
{
	// hwnd can't be null
	if (pHwnd == nullptr)
		return ERRORID_GFX_INIT_INVALID_NULL_HWND;

	// Invalid window width/height
	if (winWidth <= 0 || winHeight <= 0)
		return ERRORID_GFX_INIT_INVALID_WINDOW_WIDTH_HEIGHT;
	
	// If GLEW failure
	if (InitGLEW(hInstance, funcCallback) != ERRORID_NONE)
		return ERRORID_GFX_INIT_GLEW_FAILED;

	m_pHwnd = pHwnd;
	m_hInstance = hInstance;
	m_hDC = GetDC(*m_pHwnd);
	m_winWidth = winWidth;
	m_winHeight = winHeight;

	ErrorId error = ERRORID_NONE;
	PIXELFORMATDESCRIPTOR pfd;

	// If your GFX card is ancient
	if (majorVer <= 2)
	{
		memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 32;
		pfd.iLayerType = PFD_MAIN_PLANE;

		int iPixelFormat = ChoosePixelFormat(m_hDC, &pfd);
		if (iPixelFormat == 0)
			error = ERRORID_GFX_INVALID_PIXEL_FORMAT;

		if (!IsError(error))
		{
			if (!SetPixelFormat(m_hDC, iPixelFormat, &pfd))
				error = ERRORID_GFX_SET_PIXEL_FORMAT_FAILED;

			if (!IsError(error))
			{
				// Create the old style context (OpenGL 2.1 and before)
				m_hRC = wglCreateContext(m_hDC);
				if (m_hRC)
					wglMakeCurrent(m_hDC, m_hRC);
				else
					error = ERRORID_GFX_MAKECURRENT_HDC_FAILED;
			}
		}
	}
	else if (WGLEW_ARB_create_context && WGLEW_ARB_pixel_format)
	{
		const int iPixelFormatAttribList[] =
		{
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_COLOR_BITS_ARB, 32,
			WGL_DEPTH_BITS_ARB, 24,
			WGL_STENCIL_BITS_ARB, 8,
			0 // End of attributes list
		};

		int iContextAttribs[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, majorVer,
			WGL_CONTEXT_MINOR_VERSION_ARB, minorVer,
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			0 // End of attributes list
		};

		int iPixelFormat, iNumFormats;
		wglChoosePixelFormatARB(m_hDC, iPixelFormatAttribList, NULL, 1, &iPixelFormat, (UINT*)&iNumFormats);

		// PFD seems to be only redundant parameter now
		if (!SetPixelFormat(m_hDC, iPixelFormat, &pfd))
			error = ERRORID_GFX_SET_PIXEL_FORMAT_FAILED;

		if (!IsError(error))
		{
			m_hRC = wglCreateContextAttribsARB(m_hDC, 0, iContextAttribs);

			// If everything went OK
			if (m_hRC)
				wglMakeCurrent(m_hDC, m_hRC);
			else
				error = ERRORID_GFX_MAKECURRENT_HDC_FAILED;
		}
	}
	else
		error = ERRORID_GFX_GLEW_CREATECONTEXT_PIXELFORMAT_ERROR;
	
	if(IsError(error))
	{
		// Generate error messages
		char sErrorMessage[255], sErrorTitle[255];
		sprintf_s(sErrorMessage, "OpenGL %d.%d is not supported! Please download latest GPU drivers!", majorVer, minorVer);
		sprintf_s(sErrorTitle, "OpenGL %d.%d Not Supported", majorVer, minorVer);
		MessageBox(*m_pHwnd, sErrorMessage, sErrorTitle, MB_ICONINFORMATION);
		return error;
	}

	// Set the clear colour
	glClearColor(0.5, 0.0, 0.0, 1.0);
	Set2D(false);
	SetWireFrame(false);

	m_bInit = true;

	return error;
}

//------------------------------------------------------------------
//
//	ResizeOpenGLViewportFull(..)
//
//	Resizes viewport to full window with perspective projection
//
//------------------------------------------------------------------
ErrorId COpenGL::ResizeOpenGLViewportFull()
{
	if(m_pHwnd == NULL)
		return ERRORID_GFX_NULL_HWND;

	RECT rRect; GetClientRect(*m_pHwnd, &rRect);
	glViewport(0, 0, rRect.right, rRect.bottom);

	return ERRORID_NONE;
}

//------------------------------------------------------------------
//
//	ReleaseOpenGLControl(..)
//
//	Releases OpenGL
//
//------------------------------------------------------------------
void COpenGL::ReleaseOpenGLControl()
{
	wglMakeCurrent(NULL, NULL);

	if (m_hRC)
	{
		wglDeleteContext(m_hRC);
		m_hRC = nullptr;
	}

	if (m_pHwnd)
	{
		ReleaseDC(*m_pHwnd, m_hDC);
		m_pHwnd = nullptr;
	}

	UnregisterOpenGLClass(m_hInstance);
}

bool COpenGL::IsInitialised()
{
	return m_bInit;
}

//------------------------------------------------------------------
//
//	SetCurrentTexture(..)
//
//	texture		-	texture handle to set as active
//
//	Sets the passed texture handle to be the active texture
//
//------------------------------------------------------------------
void COpenGL::SetCurrentTexture(GLuint texture)
{
	m_currentTexture = texture;

	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(GL_TEXTURE0 + texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	if (glGetError() != GL_NO_ERROR) {
		// TO DO
		// Use/set to default texture
	}
}

//------------------------------------------------------------------
//
//	GetCurrentTexture(..)
//
//	Returns handle to current set texture
//
//------------------------------------------------------------------
GLuint COpenGL::GetCurrentTexture() const
{
	return m_currentTexture;
}

//------------------------------------------------------------------
//
//	SetCurrentShader(..)
//
//	pNewShader	-	New shader to be used as current
//
//	Simply sets new shader to be stored as current
//	Every draw will use set shader unless a new shader is passed in
//
//------------------------------------------------------------------
void COpenGL::SetCurrentShader(CShader* pNewShader)
{
	m_pRefCurrentShader = pNewShader;
}

//------------------------------------------------------------------
//
//	GetCurrentShader(..)
//
//	Returns handle to current set shader
//
//------------------------------------------------------------------
CShader* COpenGL::GetCurrentShader() const
{
	return m_pRefCurrentShader;
}

void COpenGL::BeginDraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void COpenGL::EndDraw()
{
	FlipBuffers();
}

//------------------------------------------------------------------
//
//	RenderBuffer(..)
//
//	pVertBuffer		-	pointer to the vertex buffer object
//	pIndexBuffer	-	pointer to the index buffer object
//
//	Draws passed vertex data
//
//------------------------------------------------------------------
void COpenGL::RenderBuffer(CVertexBuffer* pVertBuffer, CIndexBuffer* pIndexBuffer)
{
	pVertBuffer->UseBuffer();
	pIndexBuffer->UseBuffer();

	glDrawElements(GL_TRIANGLES, pIndexBuffer->GetIndexCount(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//------------------------------------------------------------------
//
//	MakeCurrent(..)
//
//	Makes current device and OpenGL rendering context to those
//	associated with OpenGL control
//
//------------------------------------------------------------------
void COpenGL::MakeCurrent()
{
	wglMakeCurrent(m_hDC, m_hRC);
}

//------------------------------------------------------------------
//
//	ClearScreen(..)
//
//	Clears the screen
//
//------------------------------------------------------------------
void COpenGL::ClearScreen()
{
	// Clear screen before drawing
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//------------------------------------------------------------------
//
//	Set2D(..)
//
//	bFlag	-	Enable/disable 2D mode
//
//	Sets OpenGL up for 2D drawing
//
//------------------------------------------------------------------
void COpenGL::Set2D(bool bFlag)
{
	m_b2D = bFlag;
	if (m_b2D) {
		glDepthMask(GL_FALSE);		// Disabled
		glDisable(GL_DEPTH_TEST);	// Disabled depth testing
		glEnable(GL_CULL_FACE);		// Back facing triangles don't get drawn
		glFrontFace(GL_CCW);
	}
	else {
		glDepthMask(GL_TRUE);		// Depth buffer enabled for writing
		glEnable(GL_DEPTH_TEST);	// Depth testing (stuff behind stuff don't get draw)
		glEnable(GL_CULL_FACE);		// Back facing triangles don't get drawn
		glFrontFace(GL_CCW);
	}
}

//------------------------------------------------------------------
//
//	SetWireFrame(..)
//
//	bFlag	-	Enable/disable wireframe mode
//
//	Sets OpenGL to draw in wire frame
//
//------------------------------------------------------------------
void COpenGL::SetWireFrame(bool bFlag)
{
	if (bFlag)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

//------------------------------------------------------------------
//
//	SwapBuffersM(..)
//
//	Swaps back and front buffer
//
//------------------------------------------------------------------
void COpenGL::FlipBuffers()
{
	SwapBuffers(m_hDC);
}

int COpenGL::GetScreenWidth() const
{
	return m_winWidth;
}

int COpenGL::GetScreenHeight() const
{
	return m_winHeight;
}

//------------------------------------------------------------------
//
//	InitGLEW(..)
//
//	Initialises the GLEW library
//
//------------------------------------------------------------------
ErrorId COpenGL::InitGLEW(HINSTANCE hInstance, WNDPROC funcCallback)
{
	// No error if already initialised
	if(m_bGlewInitialised)
		return ERRORID_NONE;

	// In order for GLEW to be initialised, we need a window.
	// We create a fake window to initialise GLEW with then destroy the window.
	if (!RegisterOpenGLClass(hInstance, funcCallback))
		return ERRORID_GFX_REGISTEROPENGLCLASS_FAILED;

	HWND hWndTemp = CreateWindow(OPENGL_CLASS_NAME, "FAKE", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, 0, 0,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	if (hWndTemp == NULL)
		return ERRORID_GFX_CREATE_WINDOW_FAILED;

	m_hDC = GetDC(hWndTemp);

	// Choose pixel format
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize		= sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion   = 1;
	pfd.dwFlags    = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;
 
	int iPixelFormat = ChoosePixelFormat(m_hDC, &pfd);
	if (iPixelFormat == 0)
		return ERRORID_GFX_INVALID_PIXEL_FORMAT;

	if (!SetPixelFormat(m_hDC, iPixelFormat, &pfd))
		return ERRORID_GFX_SET_PIXEL_FORMAT_FAILED;

	// Create the fake, old style context (OpenGL 2.1 and before)
	HGLRC hRCFake = wglCreateContext(m_hDC);
	wglMakeCurrent(m_hDC, hRCFake);

	if (glewInit() != GLEW_OK)
	{
		MessageBox(*m_pHwnd, "Couldn't initialize GLEW!", "Fatal Error", MB_ICONERROR);
		return ERRORID_GFX_INIT_GLEW_FAILED;
	}

	m_bGlewInitialised = true;

	// Clean up fake window
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRCFake);
	DestroyWindow(hWndTemp);

	return ERRORID_NONE;
}

//------------------------------------------------------------------
//
//	RegisterOpenGLClass(..)
//
//	hInstance	-	Application instance
//
//	Registers the OpenGL window class
//
//------------------------------------------------------------------
bool COpenGL::RegisterOpenGLClass(HINSTANCE hInstance, WNDPROC funcCallback)
{
	bool result = true;

	if (!m_bClassRegistered)
	{
		WNDCLASSEX wc;
		memset(&wc, 0, sizeof(WNDCLASSEX));
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
		wc.lpfnWndProc = funcCallback;
		wc.cbClsExtra = 0; wc.cbWndExtra = 0;
		wc.hInstance = hInstance;

		// Memory Access Violation error
		//wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
		//wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_MENUBAR + 1);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = OPENGL_CLASS_NAME;

		if (!RegisterClassEx(&wc))
			result = false;
	}

	m_bClassRegistered = true;
	return result;
}

//------------------------------------------------------------------
//
//	UnregisterOpenGLClass(..)
//
//	hInstance	-	Application instance
//
//	Unegisters the OpenGL window class
//
//------------------------------------------------------------------
void COpenGL::UnregisterOpenGLClass(HINSTANCE hInstance)
{
	if (m_bClassRegistered)
	{
		UnregisterClass(OPENGL_CLASS_NAME, hInstance);
		m_bClassRegistered = false;
	}
}