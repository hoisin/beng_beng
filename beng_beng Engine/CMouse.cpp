#include "CMouse.h"



CMouse::CMouse() : m_updateTick(0), m_updateTimer(0), m_buttonHeldTick(0), m_bCursorShow(true)
{
	for (int i = 0; i < eMouseTotal; i++)
	{
		m_buttons[i] = 'u';
		m_buttonHeldTime[i] = 0;
	}
}


CMouse::~CMouse()
{
}

void CMouse::Setup(int updateTick, int buttonHeldTime)
{
	m_updateTick = updateTick;
	m_buttonHeldTick = buttonHeldTime;
}

bool CMouse::IsMouseButtonDown(eMouseButton button) const
{
	if (m_buttons[button] == 'd' || m_buttons[button] == 'h')
		return true;

	return false;
}

bool CMouse::IsMouseButtonUp(eMouseButton button) const
{
	if (m_buttons[button] == 'u')
		return true;

	return false;
}

bool CMouse::IsMouseButtonHeld(eMouseButton button) const
{
	if (m_buttons[button] == 'h')
		return true;

	return false;
}

POINT CMouse::GetMousePos() const
{
	return m_mousePos;
}

POINT CMouse::GetMousePrevPos() const
{
	return m_mousePrevPos;
}

POINT CMouse::GetMouseDownPos(eMouseButton button) const
{
	return m_mouseDownPos[button];
}

POINT CMouse::GetMouseUpPos(eMouseButton button) const
{
	return m_mouseUpPos[button];
}

void CMouse::SetMouseCursorPos(POINT pos)
{
	POINT setPos = pos;
	m_mousePos = setPos;
	m_mousePrevPos = setPos;
	ClientToScreen(::GetActiveWindow(), &setPos);
	::SetCursorPos(setPos.x, setPos.y);

}

void CMouse::UpdateMousePrevPos()
{
	m_mousePrevPos = m_mousePos;
}

void CMouse::ShowCursor(bool bShow)
{
	if (bShow)
	{
		m_bCursorShow = true;
		::ShowCursor(TRUE);
	}
	else
	{
		m_bCursorShow = false;
		::ShowCursor(FALSE);
	}
}

bool CMouse::IsCursorVisible()
{
	return m_bCursorShow;
}

void CMouse::Update(float deltaT)
{
	m_updateTimer += (int)deltaT;

	if (m_updateTimer > m_updateTick)
	{
		for (int i = 0; i < 3; i++)
		{
			// If mouse button is down
			if (m_buttons[i] == 'd')
			{
				m_buttonHeldTime[i] += (int)deltaT;
				// If button duration down exceeds tick, set as held
				if (m_buttonHeldTime[i] > m_buttonHeldTick)
				{
					m_buttons[i] = 'h';
				}
			}
		}
		m_updateTimer = 0;
	}
}

bool CMouse::VHandleEvent(HWND wnd, UINT msg, WPARAM wParam)
{
	bool handledEvent = false;

	switch (msg)
	{
	case WM_LBUTTONDOWN:
		// Lock the mouse to window when left button is down
		// This is so we don't move mouse outside of window
		m_buttons[eMouseLeft] = 'd';
		::GetCursorPos(&m_mouseDownPos[eMouseLeft]);
		::ScreenToClient(::GetActiveWindow(), &m_mouseDownPos[eMouseLeft]);
		handledEvent = true;
		break;

	case WM_LBUTTONUP:
		// Release the mouse when left mouse button not pressed
		m_buttons[eMouseLeft] = 'u';
		::GetCursorPos(&m_mouseUpPos[eMouseLeft]);
		::ScreenToClient(::GetActiveWindow(), &m_mouseUpPos[eMouseLeft]);
		m_buttonHeldTime[0] = 0;
		handledEvent = true;
		break;

	case WM_MOUSEMOVE:
	{
		POINT temp;
		::GetCursorPos(&temp);
		::ScreenToClient(::GetActiveWindow(), &temp);
		m_mousePrevPos = m_mousePos;
		m_mousePos = temp;
		handledEvent = true;
	}
	break;

	default:
		break;
	}

	return handledEvent;
}



