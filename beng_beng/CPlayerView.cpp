//--------------------------------------------------------------------------
//
//	Player View class.
//	- What the player would see
//
//--------------------------------------------------------------------------
#include "CPlayerView.h"
#include "CCameraFPS.h"
#include "CParticleManager.h"

CPlayerView::CPlayerView(CSceneManager* pSceneMgr, CWorld* pWorld, CApp* pApp)
	: m_pSceneMgr(pSceneMgr), m_pWorld(pWorld), m_pApp(pApp),
	m_bLeftMouseDown(false), m_tickCounter(0.f), m_updateTick(0.f), m_bSnapMouseUpdate(false)
{
	m_mouse.Setup(50, 500);
	m_keyboard.Initialise(50, 500);
}

CPlayerView::~CPlayerView()
{
}

//------------------------------------------------------------------
//
//	Update(..)
//
//	deltaT - Time elapsed since last update
//
//	Perform updating
//
//------------------------------------------------------------------
void CPlayerView::VUpdate(float deltaT)
{
	// Get World
	// - Get object list
	// - For each object get its mesh ID, orientation and position
	// - Create a drawObj list
	// - Pass this list into scene manager for processing.
	//
	// Call scene manager Render()/Display()

	// Update the scene when world has been updated
	if (m_pWorld->IsUpdated()) {
		m_pSceneMgr->UpdateScene(m_pWorld);
	}

	m_mouse.Update(deltaT);
	m_keyboard.Update(deltaT);

	// Update input
	m_tickCounter += deltaT;
	if (m_tickCounter > m_updateTick) 
	{
		CCameraFPS* cam = (CCameraFPS*)m_pSceneMgr->GetCamera(0);
		float rotAmt = 3;

		// Mouse handling
		if (m_mouse.IsMouseButtonDown(eMouseLeft) || m_mouse.IsMouseButtonHeld(eMouseLeft))
		{
			if (m_mouse.IsCursorVisible())
				m_mouse.ShowCursor(false);

			int mouseX = m_mouse.GetMousePos().x - m_mouse.GetMouseDownPos(eMouseLeft).x;// m_mouse.GetMousePrevPos().x;
			int mouseY = m_mouse.GetMousePos().y - m_mouse.GetMouseDownPos(eMouseLeft).y;//m_mouse.GetMousePrevPos().y;

			float d = (deltaT / 1000);

			cam->RotateYaw(mouseX*rotAmt*d);
			cam->RotatePitch(mouseY*rotAmt*d);

			// Reset mouse position
			m_mouse.SetMouseCursorPos(m_mouse.GetMouseDownPos(eMouseLeft));
		}

		if (m_mouse.IsMouseButtonUp(eMouseLeft))
		{
			if (!m_mouse.IsCursorVisible())
				m_mouse.ShowCursor(true);
		}

		float moveAmt = 4;
		//cam->MoveBack(moveAmt);
		// Keyboard handling
		if (m_keyboard.IsKeyDown(VK_LEFT) || m_keyboard.IsKeyHeld(VK_LEFT))
		{
			cam->RotateYaw(-3);
		}
		if (m_keyboard.IsKeyDown(VK_RIGHT) || m_keyboard.IsKeyHeld(VK_RIGHT))
		{
			cam->RotateYaw(3);
		}
		if (m_keyboard.IsKeyDown('W') || m_keyboard.IsKeyHeld('W'))
		{
			cam->MoveForward(moveAmt);
		}
		if (m_keyboard.IsKeyDown('S') || m_keyboard.IsKeyHeld('S'))
		{
			cam->MoveBack(moveAmt);
		}
		if (m_keyboard.IsKeyDown('A') || m_keyboard.IsKeyHeld('A'))
		{
			cam->StrafeLeft(moveAmt);
		}
		if (m_keyboard.IsKeyDown('D') || m_keyboard.IsKeyHeld('D'))
		{
			cam->StrafeRight(moveAmt);
		}
		if (m_keyboard.IsKeyDown(VK_ESCAPE))
		{
			m_pApp->CloseRun();
		}

		m_tickCounter = 0;
	}

	// Interpolation value probably submitted here
	int cam = 1;
	m_pSceneMgr->RenderScene(cam, m_pWorld->GetLastUpdate() / m_pWorld->GetUpdateTick());
}

void CPlayerView::SetUpdateTick(float updateTick)
{
	m_updateTick = updateTick;
}

//------------------------------------------------------------------
//
//	VHandleEvent(..)
//
//	msg		-	windows call back event message
//	wParam	-	windows call back wParam	
//
//	Handle call back events for player view
//	Returns false if no event was handled
//
//------------------------------------------------------------------
bool CPlayerView::VHandleEvent(HWND wnd, UINT msg, WPARAM wParam)
{
	bool result = false;

	// Mouse input
	if (m_mouse.VHandleEvent(wnd, msg, wParam)) 
		result = true;

	if (m_keyboard.VHandleEvent(msg, wParam))
		result = true;
	
	return result;
}