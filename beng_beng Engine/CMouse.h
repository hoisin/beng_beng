//--------------------------------------------------------------------------
//
// Mouse handler class
// Mouse button state the same as keyboard.
// u = up
// d = down
// h = held
//
//	No Unit tests
//
//--------------------------------------------------------------------------

#pragma once

#include <windows.h>

enum eMouseButton
{
	eMouseLeft = 0,
	eMouseRight,
	eMouseMiddle,
	eMouseTotal
};

class CMouse
{
public:
	CMouse();
	~CMouse();

	void Setup(int updateTick, int buttonHeldTime);

	bool IsMouseButtonDown(eMouseButton button) const;
	bool IsMouseButtonUp(eMouseButton button) const;
	bool IsMouseButtonHeld(eMouseButton button) const;

	POINT GetMousePos() const;
	POINT GetMousePrevPos() const;

	// Returns the mouse position when specified mouse button was pressed
	POINT GetMouseDownPos(eMouseButton button) const;

	// Returns the mouse position when specified mouse button was released
	POINT GetMouseUpPos(eMouseButton button) const;

	void SetMouseCursorPos(POINT pos);
	void UpdateMousePrevPos();

	void ShowCursor(bool bShow);
	bool IsCursorVisible();

	void Update(float deltaT);

	bool VHandleEvent(HWND wnd, UINT msg, WPARAM wParam);

private:
	POINT m_mousePos;
	POINT m_mousePrevPos;

	POINT m_mouseDownPos[eMouseTotal];
	POINT m_mouseUpPos[eMouseTotal];

	int m_updateTick;		// Elapsed time to update
	int m_updateTimer;		// Timer counter to keep track of time elapsed
	int m_buttonHeldTick;	// Time elapsed to consider button 'held'

	// Handling 3 mouse buttons
	// 1 = left, 2 = right, 3 = middle/wheel press
	char m_buttons[eMouseTotal];
	int m_buttonHeldTime[eMouseTotal];

	bool m_bCursorShow;
};

