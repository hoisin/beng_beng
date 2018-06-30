//--------------------------------------------------------------------------
//
//	Base Application framework
//
//	03/11/2017
//
//--------------------------------------------------------------------------
#include "CBaseApp.h"

CBaseApp::CBaseApp() : m_hInstance(nullptr), m_hMutex(nullptr), m_windowName(""), m_appName(""),
	m_width(0), m_height(0), m_bRun(false), m_bAppActive(false), m_bInitialised(false)
{
}

CBaseApp::~CBaseApp()
{
}

//------------------------------------------------------------------
//
//	Initialise(..)
//
//	windowTitle		-	Window title text
//	windowWidth		-	Window width in pixels
//	windowHeight	-	Window height in pixels
//	hInstance		-	Handle to current instance
//
//	Initialises application with specified unique identifier.
//	Prevents running of multiple instances
//
//------------------------------------------------------------------
bool CBaseApp::Initialise(const std::string& windowTitle, UINT windowWidth,
	UINT windowHeight, HINSTANCE hInstance)
{
	if (windowTitle == "")
		return false;

	m_windowName = windowTitle;
	m_appName = m_windowName + "App";

	// Don't allow running of multiple instances
	m_hMutex = CreateMutex(NULL, true, m_appName.c_str());
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		MessageBox(NULL, "Application already running!", "Multiple instances found",
			MB_ICONINFORMATION | MB_OK);
		return false;
	}

	// Attempt to register window class
	if (!RegisterAppClass(hInstance))
		return false;

	// Attempt to create the window
	if (!CreateAppWindow(hInstance, windowTitle, windowWidth, windowHeight))
		return false;

	// Derived initalise implementation
	if (OnInitialise())
		m_bRun = true;
	else
		return false;
			
	m_bInitialised = true;
	return true;
}

void CBaseApp::CloseRun()
{
	m_bRun = false;
}

void CBaseApp::ShutDown()
{
	if (m_hWnd)
	{
		DestroyWindow(m_hWnd);
		m_hWnd = nullptr;
	}
	
	// Release and CloseHandle to fully close the mutex (for unit tests)
	if (m_hMutex)
	{
		ReleaseMutex(m_hMutex);
		CloseHandle(m_hMutex);
		m_hMutex = nullptr;
	}

	UnregisterClass(m_appName.c_str(), m_hInstance);

	m_bInitialised = false;
	m_bAppActive = false;
	m_width = 0;
	m_height = 0;
}

UINT CBaseApp::GetWindowWidth() const
{
	return m_width;
}

UINT CBaseApp::GetWindowHeight() const
{
	return m_height;
}

const std::string & CBaseApp::GetWindowName() const
{
	return m_windowName;
}

const std::string & CBaseApp::GetWindowClassName() const
{
	return m_appName;
}

HINSTANCE CBaseApp::GetHInstance() const
{
	return m_hInstance;
}

HANDLE CBaseApp::GetMutex() const
{
	return m_hMutex;
}

bool CBaseApp::IsInitialised() const
{
	return m_bInitialised;
}

//------------------------------------------------------------------
//
//	GetInstance(..)
//
//	Params:
//	hWnd	-	Handle to window
//	uiMsg	-	Callback message
//	wParam	-	wParam from callback
//	lParam	-	lParam from callback
//
//	Windows event callback method.
//	Don't handles events here, do it in OnEvent(...)
//
//------------------------------------------------------------------
LRESULT CALLBACK CBaseApp::MsgHandlerMain(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	if (hWnd == NULL) 
		throw std::runtime_error("Invalid window handle");

	// Retrieve a pointer to the Application object
	CBaseApp* app = (CBaseApp*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	if (app == NULL) 
		return DefWindowProc(hWnd, uiMsg, wParam, lParam);
	
	// Handle required messages
	switch (uiMsg) 
	{
	case WM_DESTROY:
		ShowWindow(hWnd, SW_HIDE);
		app->m_bRun = false;
		PostQuitMessage(0);
		break;
	}

	// Run the OnEvent() function to handle our events
	if (app->OnEvent(hWnd, uiMsg, wParam, lParam) == FALSE) 
		return DefWindowProc(hWnd, uiMsg, wParam, lParam);
	
	return 0;
}

//------------------------------------------------------------------
//
//	RegisterAppClass(..)
//
//	Params:
//	hAppInstance		-	Label of class/process
//
//	Registers window class
//
//------------------------------------------------------------------
bool CBaseApp::RegisterAppClass(HINSTANCE hAppInstance)
{
	WNDCLASSEX wcex;
	memset(&wcex, 0, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	// Memory Access Violation error
	/*wcex.hIcon = LoadIcon(m_hInstance, IDI_WINLOGO);
	wcex.hIconSm = LoadIcon(m_hInstance, IDI_WINLOGO);
	wcex.hCursor = LoadCursor(m_hInstance, IDC_ARROW);*/

	wcex.hInstance = hAppInstance;

	wcex.lpfnWndProc = MsgHandlerMain;
	wcex.lpszClassName = m_appName.c_str();

	wcex.lpszMenuName = NULL;

	// Register Class
	if (!RegisterClassEx(&wcex)) 
		return false;

	return true;
}

//------------------------------------------------------------------
//
//	CreateAppWindow(..)
//
//	hAppInstance	-	Handle to current instance
//	windowTitle		-	Window title text
//	windowWidth		-	Window width in pixels
//	windowHeight	-	Window height in pixels
//
//	Creates the window with the specified string as title
//
//------------------------------------------------------------------
bool CBaseApp::CreateAppWindow(HINSTANCE hAppInstance, const std::string & windowTitle, UINT windowWidth, UINT windowHeight)
{
	m_windowName = windowTitle;
	m_width = windowWidth;
	m_height = windowHeight;

	// Create and determine window size
	RECT windowSize;
	windowSize.left = 0;
	windowSize.right = m_width;
	windowSize.top = 0;
	windowSize.bottom = m_height;

	AdjustWindowRectEx(&windowSize, WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX |
		WS_CLIPCHILDREN | WS_CLIPSIBLINGS, false, WS_EX_OVERLAPPEDWINDOW);

	m_hWnd = CreateWindowEx(0, m_appName.c_str(), windowTitle.c_str(), WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_CLIPCHILDREN,
		0, 0, (windowSize.right - windowSize.left), (windowSize.bottom - windowSize.top), NULL,
		NULL, hAppInstance, NULL);

	// Recalculate window to get client area to correct size
	RECT rClient, rWindow;
	POINT ptDiff;
	GetClientRect(m_hWnd, &rClient);
	GetWindowRect(m_hWnd, &rWindow);
	ptDiff.x = (rWindow.right - rWindow.left) - rClient.right;
	ptDiff.y = (rWindow.bottom - rWindow.top) - rClient.bottom;
	MoveWindow(m_hWnd, rWindow.left, rWindow.top, m_width + ptDiff.x, m_height + ptDiff.y, TRUE);

	if (m_hWnd == 0) 
		return false;

	// Store a pointer to this object in the window, otherwise we can't grab it using
	// GetWindowLongPtr(..) in the callback for messages
	SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (INT_PTR)this);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	m_hInstance = hAppInstance;

	return true;
}

//------------------------------------------------------------------
//
//	OnInitialise(..)
//
//	Do App initialisation here
//
//------------------------------------------------------------------
bool CBaseApp::OnInitialise()
{
	// Implement on derived
	return true;
}

//------------------------------------------------------------------
//
//	OnEvent(..)
//
//	Params:
//	wnd		-	Handle to window
//	msg		-	Callback message
//	wParam	-	wParam from callback
//	lParam	-	lParam from callback
//
//	Handle events here
//
//------------------------------------------------------------------
bool CBaseApp::OnEvent(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	bool result = true;

	switch (msg)
	{
	case WM_PAINT:
		BeginPaint(wnd, &ps);
		EndPaint(wnd, &ps);
		break;

	case WM_ACTIVATE:
	{
		switch (LOWORD(wParam))
		{
		case WA_ACTIVE:
		case WA_CLICKACTIVE:
			m_bAppActive = true;
			break;
		case WA_INACTIVE:
			// Set this to false if you want the app to 'pause' when not focused
			m_bAppActive = true;
			break;
		}
		break;
	}
	case WM_SIZE:
		break;

	default:
		result = false;
		break;
	}
	
	// Implement and call in derived

	return result;
}

void CBaseApp::UpdateWindowName(const std::string & name)
{
	m_windowName = name;
}
