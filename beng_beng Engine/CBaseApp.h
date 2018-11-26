//--------------------------------------------------------------------------
//
//	Base Application framework
//
//	03/11/2017
//
//--------------------------------------------------------------------------
#pragma once

#include <string>
#include <vector>
#include <windows.h>

#include "Errors.h"

#define DEFAULT_WINDOW_TITLE "Default"

class CBaseApp
{
public:
	CBaseApp();
	virtual ~CBaseApp();

	ErrorId Initialise(const std::string& windowTitle, UINT windowWidth,
		UINT windowHeight, HINSTANCE hInstance = nullptr);

	virtual void AppRun() = 0;
	virtual void CloseRun();
	virtual void ShutDown();
	 
	UINT GetWindowWidth() const;
	UINT GetWindowHeight() const;

	const std::string& GetWindowName() const;
	const std::string& GetWindowClassName() const;

	HINSTANCE GetHInstance() const;
	HANDLE GetMutex() const;

	bool IsInitialised() const;

protected:
	// Callback function definition
	static LRESULT CALLBACK MsgHandlerMain(HWND hWnd, UINT uiMsg,
		WPARAM wParam, LPARAM lParam);

	bool RegisterAppClass(HINSTANCE hAppInstance);
	bool CreateAppWindow(HINSTANCE hAppInstance, const std::string& windowTitle,
		UINT windowWidth, UINT windowHeight);
	void UpdateWindowName(const std::string& name);

	// Overrides
	virtual ErrorId OnInitialise();
	virtual bool OnEvent(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	HWND	m_hWnd;

protected:
	HINSTANCE	m_hInstance;
	HANDLE		m_hMutex;

	std::string m_windowName;
	std::string m_appName;

	UINT m_width;
	UINT m_height;

	bool m_bAppActive;
	bool m_bRun;
	bool m_bInitialised;
};