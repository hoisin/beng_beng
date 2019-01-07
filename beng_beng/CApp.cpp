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


CApp::CApp()
{
}

CApp::~CApp()
{
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

//------------------------------------------------------------------
//
//	CloseRun(..)
//
//	Just need to call base at the moment
//
//------------------------------------------------------------------
void CApp::CloseRun()
{
	CBaseApp::CloseRun();
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

	// Call base to handle window clean up
	CBaseApp::ShutDown();
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
ErrorId CApp::OnInitialise()
{
	ErrorId errorId = ERRORID_NONE;

	// Setup graphics module
	if (m_renderer.Initialise(m_hInstance, &m_hWnd, m_width, m_height, MsgHandlerMain)
		!= ERRORID_NONE) {
		std::cerr << "Failed to initialise renderer" << std::endl;
		return ERRORID_APP_RENDERER_INIT_FAILED;
	}

	if (!m_sceneMgr.Initialise(&m_renderer)) {
		std::cerr << "Failed to initialise scene manager" << std::endl;
		return ERRORID_APP_SCENEMGR_INIT_FAILED;
	}
	// Add a first person camera
	CCameraFPS* pFPSCam = new CCameraFPS(
		glm::vec3(0, 10, 0), glm::vec3(0, 1, 0), 1.f, 1000.f, (float)(m_width / m_height), 45.f);
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
		return ERRORID_APP_ASSETMGR_INIT_FAILED;
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
	m_world.CreateCameraFPS(glm::vec3(0, 10, 0), glm::vec3(0, 1, 0), 1.f, 1000.f, (float)(m_width / m_height), 45.f);

	// 50ms in between updates
	m_world.SetUpdateTick(50);
	return ERRORID_NONE;
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
	ErrorId error;
	// Load shaders
	error = ASSETMGR->LoadTechnique("..\\Shaders\\texturePointVertexShader.vsh", "..\\Shaders\\texturePointFragmentShader.fsh");
	if (IsError(error))
		return error;

	// Load textures
	std::string myTextureTest = "..\\Textures\\test.bmp";
	std::string myTexturePlane = "..\\Textures\\plane.bmp";

	std::string testTextureID = "Test_1";
	std::string planeTextureID = "Plane_1";

	error = ASSETMGR->LoadTexture(myTextureTest, testTextureID);
	if (IsError(error))
		return error;

	error = ASSETMGR->LoadTexture(myTexturePlane, planeTextureID);
	if (IsError(error))
		return error;

	// Load materials
	std::string myMaterialID_1 = "material_1";
	std::string myMaterialID_2 = "material_2";

	// Material 1
	CMaterial tempMaterial;
	tempMaterial.m_diffuseTextureID = testTextureID;
	error = ASSETMGR->AddMaterial(tempMaterial, myMaterialID_1);
	if (IsError(error))
		return error;

	// Material 2
	tempMaterial.m_diffuseTextureID = planeTextureID;
	error = ASSETMGR->AddMaterial(tempMaterial, myMaterialID_2);
	if (IsError(error))
		return error;

	// Create models
	std::string modelCube_1 = "cube_1";
	std::string modelCube_2 = "cube_2";
	std::string modelSphere_1 = "sphere_1";
	std::string modelPlane_1 = "plane_1";
	
	if (!ASSETMGR->LoadModel("..\\Models\\Rabbit", "Rabbit.obj", modelCube_1))
		return false;

	//ASSETMGR->CreateModelCube(48, 3, eVertexPNT, modelCube_1, myMaterialID_1);
	error = ASSETMGR->CreateModelCube(4, 1, eVertexPNT, modelCube_2, myMaterialID_1);
	if (IsError(error))
		return error;

	error =	ASSETMGR->CreateModelSphere(3, 10, eVertexPNT, modelSphere_1, myMaterialID_1);
	if (IsError(error))
		return error;

	error = ASSETMGR->CreateModelPlane(500, 10, eVertexPNT, modelPlane_1, myMaterialID_2);
	if (IsError(error))
		return error;

	return true;
}