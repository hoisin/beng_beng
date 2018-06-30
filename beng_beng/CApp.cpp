//--------------------------------------------------------------------------
//
//	Application framework
//	- Window initialisation and creation
//  - Main app loop
//  - Event function call back
//
//--------------------------------------------------------------------------

#include <sstream>
#include "CApp.h"
#include "CPlayerView.h"
#include "CAssetManager.h"
#include "CCameraFPS.h"


CApp::CApp() : m_bAppActive(true), m_bRun(true)
{
}

CApp::~CApp()
{
}

//------------------------------------------------------------------
//
//	InitialiseApp(..)
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
bool CApp::InitialiseApp(const std::string &windowTitle, UINT windowWidth, UINT windowHeight,
	HINSTANCE hInstance)
{
	m_appName = windowTitle;
	m_hMutex = CreateMutex(NULL, 1, m_appName.c_str());

	// Don't allow to run multiple instances
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		MessageBox(NULL, "Application already running!", "Multiple Instances Found", MB_ICONINFORMATION | MB_OK);
		return false;
	}

	// Attempt to register window class
	if (!RegisterAppClass(hInstance)) {
		return false;
	}
	
	// Attempt to create the window
	if (!CreateAppWindow(hInstance, windowTitle, windowWidth, windowHeight)) {
		return false;
	}

	return true;
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
bool CApp::RegisterAppClass(HINSTANCE hAppInstance)
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
	if (!RegisterClassEx(&wcex)) {
		return false;
	}

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
bool CApp::CreateAppWindow(HINSTANCE hAppInstance, const std::string &windowTitle, UINT windowWidth, UINT windowHeight)
{
	m_windowName = windowTitle;

	// Create and determine window size
	RECT windowSize;
	windowSize.left = 0;
	windowSize.right = windowWidth;
	windowSize.top = 0;
	windowSize.bottom = windowHeight;

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
	MoveWindow(m_hWnd, rWindow.left, rWindow.top, windowWidth + ptDiff.x, windowHeight + ptDiff.y, TRUE);

	if (m_hWnd == 0) {
		return false;
	}

	// Store a pointer to this object in the window, otherwise we can't grab it using
	// GetWindowLongPtr(..) in the callback for messages
	SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (INT_PTR)this);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	m_hInstance = hAppInstance;

	// Run initialisation, if fail quit the application
	if (!OnInitialise(windowWidth, windowHeight)) {
		m_bRun = false;
	}

	return true;
}

//------------------------------------------------------------------
//
//	AppRun(..)
//
//	Main Loop 
//
//------------------------------------------------------------------
void CApp::AppRun()
{
	MSG msg;
	long currentUpdate = timeGetTime();
	long lastUpdate = timeGetTime();

	// Setup timer for frame stats tracking
	m_timer.Reset();
	m_timer.Start();

	while (m_bRun) {
		// Check for event updates
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// Otherwise send message to appropriate window
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			// If app is currently active
			if (m_bAppActive) {
				// Only want to process the timer when our app is the active window (may change)
				m_timer.Tick();

				currentUpdate = timeGetTime();

				// This is currently in milliseconds!
				OnUpdate((float)(currentUpdate - lastUpdate));

				// Update last update time
				lastUpdate = currentUpdate;

				CalculateFrameStats();
			}
			else {
				// Do not consume processor power if application isn't active
				Sleep(200);
			}
		}
	}
}

void CApp::CloseRun()
{
	m_bRun = false;
}

//------------------------------------------------------------------
//
//	ShutDown(..)
//
//	Cleans up 
//
//------------------------------------------------------------------
void CApp::ShutDown()
{
	// Nuke assets on application close!!!!!!!!!
	ASSETMGR->ShutDown();

	// Shut down the renderer

	// Shut down the scene manager
	m_sceneMgr.ShutDown();

	// Shut down the logic world
	m_world.ShutDown();

	// Release views
	for (int view = 0; view < (int)m_viewArray.size(); view++) {
		if (m_viewArray[view]) {
			delete m_viewArray[view];
			m_viewArray[view] = nullptr;
		}
	}

	DestroyWindow(m_hWnd);
	UnregisterClass(m_appName.c_str(), m_hInstance);
	ReleaseMutex(m_hMutex);
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
LRESULT CALLBACK CApp::MsgHandlerMain(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	if (hWnd == NULL) {
		throw std::runtime_error("Invalid window handle");
	}

	// Retrieve a pointer to the Application object
	CApp* app = (CApp*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	if (app == NULL) {
		return DefWindowProc(hWnd, uiMsg, wParam, lParam);
	}

	// Handle required messages
	switch (uiMsg) {
	case WM_CLOSE:
		ShowWindow(hWnd, SW_HIDE);
		app->m_bRun = false;
		break;
	}

	// Run the OnEvent() function to handle our events
	if (app->OnEvent(hWnd, uiMsg, wParam, lParam) == FALSE) {
		return DefWindowProc(hWnd, uiMsg, wParam, lParam);
	}

	return 0;
}

//------------------------------------------------------------------
//
//	OnInitialise(..)
//
//	Params:
//	windowWidth		-	Window width
//	windowHeight	-	Window height
//
//	Do App initialisation here
//
//------------------------------------------------------------------
bool CApp::OnInitialise(UINT windowWidth, UINT windowHeight)
{
	// Setup graphics module
	if (!m_renderer.Initialise(m_hInstance, &m_hWnd, windowWidth, windowHeight, MsgHandlerMain)) {
		std::cerr << "Failed to initialise renderer" << std::endl;
		return false;
	}

	if (!m_sceneMgr.Initialise(&m_renderer)) {
		std::cerr << "Failed to initialise scene manager" << std::endl;
		return false;
	}
	// Add a first person camera
	CCameraFPS* pFPSCam = new CCameraFPS(
		glm::vec3(0, 10, 0), glm::vec3(0, 1, 0), 1.f, 1000.f, (float)(windowWidth / windowHeight), 45.f);
	m_sceneMgr.AddCamera(pFPSCam);

	// Setup views 
	//
	// Create a player view
	CPlayerView* newPlayerView = new CPlayerView(&m_sceneMgr, &m_world, this);
	newPlayerView->SetUpdateTick(50);
	// Will need to initialise later dev. before adding (e.g. assign pointer to sceneMGR)
	m_viewArray.push_back(newPlayerView);

	// Initialise Asset manager
	if (!ASSETMGR->Initialise()) {
		std::cerr << "FAiled to initialise the asset manager" << std::endl;
		return false;
	}

	// Load assets
	//
	// These are model data (vertex/index), shaders, textures & material descriptions which are assigned to meshes.
	//
	OnLoadAssets();
	
	// Setup world logic
	//
	// Based on loaded assets, we use typically IDs to refer to the loaded assets (likely to be strings).
	m_world.Initialise(glm::vec3(-500, 0, -500), glm::vec3(500, 100, 500));
	m_world.CreateCameraFPS(glm::vec3(0, 10, 0), glm::vec3(0, 1, 0), 1.f, 1000.f, (float)(windowWidth / windowHeight), 45.f);

	// 50ms in between updates
	m_world.SetUpdateTick(50);


	return true;
}

//------------------------------------------------------------------
//
//	OnUpdate(..)
//
//	fTime	-	Time elapsed since last update
//
//	Do updating here
//
//------------------------------------------------------------------
void CApp::OnUpdate(float fTime)
{
	m_world.Update(fTime);

	// Update views
	for (int view = 0; view < (int)m_viewArray.size(); view++) {
		m_viewArray[view]->VUpdate(fTime);
	}

	// Resets 'updated' flag in world
	// Used for processing between this and Update() of world and anything that
	//	needs to know that world has been updated.
	m_world.EndUpdate();
}

//------------------------------------------------------------------
//
//	OnEvent(..)
//
//	Params:
//	wnd	-	Handle to window
//	msg	-	Callback message
//	wParam	-	wParam from callback
//	lParam	-	lParam from callback
//	Handle events here
//
//------------------------------------------------------------------
bool CApp::OnEvent(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

	// Don't run view events if closing
	if (m_bRun) {
		// Pass to view
		for (int view = 0; view < (int)m_viewArray.size(); view++) {
			result = m_viewArray[view]->VHandleEvent(wnd, msg, wParam);
		}
	}

	return result;
}

//------------------------------------------------------------------
//
//	CalculateFrameStats(..)
//
//	Calculates frames per second
//
//------------------------------------------------------------------
void CApp::CalculateFrameStats()
{
	static int frameCount = 0;
	static double timeElapsed = 0.0f;

	// Increment counter and elapsed time
	frameCount++;
	timeElapsed += m_timer.DeltaTime();

	// If exceed over a second
	if ((timeElapsed) >= 1.0f) {
		float fps = (float)frameCount;
		float mspf = 1000.0f / fps;

		// Write stats on the title of the window
		std::ostringstream outs;
		outs.precision(6);
		outs << m_windowName << "    " << "FPS: " << fps << "    " << "Frame Time: " << mspf << " (ms)";

		SetWindowText(m_hWnd, outs.str().c_str());

		// Reset vars
		frameCount = 0;
		timeElapsed = 0;
	}
}

//------------------------------------------------------------------
//
//	OnLoadAssets(..)
//
//	Loads assets used by application
//
//------------------------------------------------------------------
bool CApp::OnLoadAssets()
{
	// Load shaders
	ASSETMGR->LoadTechnique("..\\Shaders\\texturePointVertexShader.vsh", "..\\Shaders\\texturePointFragmentShader.fsh");

	// Load textures
	std::string myTextureTest = "..\\Textures\\test.bmp";
	std::string myTexturePlane = "..\\Textures\\plane.bmp";

	std::string testTextureID = "Test_1";
	std::string planeTextureID = "Plane_1";

	ASSETMGR->LoadTexture(myTextureTest, testTextureID);
	ASSETMGR->LoadTexture(myTexturePlane, planeTextureID);

	// Load materials
	std::string myMaterialID_1 = "material_1";
	std::string myMaterialID_2 = "material_2";

	// Material 1
	CMaterial tempMaterial;
	tempMaterial.m_diffuseTextureID = testTextureID;
	ASSETMGR->AddMaterial(tempMaterial, myMaterialID_1);

	// Material 2
	tempMaterial.m_diffuseTextureID = planeTextureID;
	ASSETMGR->AddMaterial(tempMaterial, myMaterialID_2);

	// Create models
	std::string modelCube_1 = "cube_1";
	std::string modelCube_2 = "cube_2";
	std::string modelSphere_1 = "sphere_1";
	std::string modelPlane_1 = "plane_1";
	
	ASSETMGR->LoadModel("..\\Models\\Rabbit", "Rabbit.obj", modelCube_1);
	//ASSETMGR->CreateModelCube(48, 3, eVertexPNT, modelCube_1, myMaterialID_1);
	ASSETMGR->CreateModelCube(6, 2, eVertexPNT, modelCube_2, myMaterialID_1);
	ASSETMGR->CreateModeSphere(3, 10, eVertexPNT, modelSphere_1, myMaterialID_1);
	ASSETMGR->CreateModelPlane(250, 10, eVertexPNT, modelPlane_1, myMaterialID_2);

	return true;
}