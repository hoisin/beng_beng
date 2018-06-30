//--------------------------------------------------------------------------
//
//	Application framework
//	- Window initialisation and creation
//  - Main app loop
//  - Event function call back
//
//--------------------------------------------------------------------------

#ifndef __CAPP_H__
#define __CAPP_H__

#include <string>
#include <vector>
#include <Windows.h>

#include "CTimer.h"
#include "IView.h"
// Gfx
#include "CSceneManager.h"
#include "CRenderer.h"
// Logic
#include "CWorld.h"


class CApp
{
public:
	CApp();
	~CApp();

	// Init app
	bool InitialiseApp(const std::string &windowTitle, UINT windowWidth, UINT windowHeight, 
		HINSTANCE hInstance = nullptr);
	
	// Run App
	void AppRun();

	void CloseRun();

	// Shutdown
	void ShutDown();

protected:
	// Callback function definition
	static LRESULT CALLBACK MsgHandlerMain(HWND hWnd, UINT uiMsg,
		WPARAM wParam, LPARAM lParam);

	// Registers the application class
	bool RegisterAppClass(HINSTANCE hAppInstance);

	// Creates the application window
	bool CreateAppWindow(HINSTANCE hAppInstance, const std::string& windowTitle,
		UINT windowWidth, UINT windowHeight);

	bool OnInitialise(UINT windowWidth, UINT windowHeight);

	void OnUpdate(float fTime);
	
	bool OnEvent(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// Calculates and displays frame stats
	void CalculateFrameStats();

	// Load data files
	bool OnLoadAssets();

public:
	HWND			m_hWnd;

protected:
	HINSTANCE		m_hInstance;
	HANDLE			m_hMutex;

	std::string		m_appName;
	std::string		m_windowName;

	CTimer			m_timer;	
	bool			m_bAppActive;
	bool			m_bRun;

	// Array of views
	std::vector<IView*> m_viewArray;

	CSceneManager m_sceneMgr;
	CRenderer m_renderer;
	CWorld m_world;

};



#endif