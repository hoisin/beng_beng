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

class CBaseApp
{
public:
	CBaseApp();
	virtual ~CBaseApp();

	bool Initialise(const std::string& windowTitle, UINT windowWidth,
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

	// Registers the application class
	bool RegisterAppClass(HINSTANCE hAppInstance);

	// Creates the appplication window
	bool CreateAppWindow(HINSTANCE hAppInstance, const std::string& windowTitle,
		UINT windowWidth, UINT windowHeight);

	virtual bool OnInitialise();

	virtual bool OnEvent(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void UpdateWindowName(const std::string& name);

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