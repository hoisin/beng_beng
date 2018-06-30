//--------------------------------------------------------------------------
//
//	19/03/2014
//
//	Main entry point
//
//--------------------------------------------------------------------------

#include <Windows.h>
#include "CApp.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR sCmdLine, int iShow)
{
	//memory leak detection
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(242);

	CApp app;

	if (!app.InitialiseApp("OpenGL 3.3 App", 800, 600, hInstance)) {
		// Should maybe display some error message error message here.
		// Rather than just exiting the program.
		return 0;
	}
	
	app.AppRun();
	app.ShutDown();

	return 0;
}

