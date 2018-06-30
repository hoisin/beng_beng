//--------------------------------------------------------------------------
//
//	Player View class.
//	- What the user would see
//
//--------------------------------------------------------------------------
#pragma once

#include "IView.h"

#include "CApp.h"
#include "CSceneManager.h"
#include "CWorld.h"

#include "CMouse.h"
#include "CKeyboard.h"

class CPlayerView : public IView
{
public:
	CPlayerView(CSceneManager* pSceneMgr, CWorld* pWorld, CApp* pApp);
	~CPlayerView();

	void VUpdate(float deltaT);

	void SetUpdateTick(float updateTick);

	bool VHandleEvent(HWND wnd, UINT msg, WPARAM wParam);
	
private:
	CPlayerView();

protected:
	CSceneManager* m_pSceneMgr;
	CWorld* m_pWorld;
	CApp* m_pApp;

	CMouse m_mouse;
	CKeyboard m_keyboard;

	// Mouse handling
	float m_tickCounter;
	float m_updateTick;
	bool m_bLeftMouseDown;
	glm::vec2 m_lastPos;
	POINT m_mouseDownPos;

	bool m_bSnapMouseUpdate;
};


