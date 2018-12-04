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

#include "CBaseApp.h"

#include "CTimer.h"
#include "IView.h"
// Gfx
#include "CSceneManager.h"
#include "CRenderer.h"
// Logic
#include "CWorld.h"


class CApp : public CBaseApp
{
public:
	CApp();
	~CApp();

	void AppRun() override;
	void CloseRun() override;
	void ShutDown() override;

protected:
	ErrorId OnInitialise() override;
	bool OnEvent(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void OnUpdate(float fTime);
	void CalculateFrameStats();

	bool OnLoadAssets();

protected:
	CTimer			m_timer;	

	// Array of views
	std::vector<IView*> m_viewArray;
	CSceneManager m_sceneMgr;
	CRenderer m_renderer;
	CWorld m_world;

};



#endif