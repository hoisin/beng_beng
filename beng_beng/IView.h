//--------------------------------------------------------------------------
//
//	Interface for views
//
//--------------------------------------------------------------------------

#pragma once

#include <Windows.h>

class IView
{
public:
	virtual ~IView() {}

	virtual void VUpdate(float deltaT) = 0;

	virtual bool VHandleEvent(HWND wnd, UINT msg, WPARAM wParam) = 0;
};