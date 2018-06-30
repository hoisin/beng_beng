//--------------------------------------------------------------------------
//
//	Keyboard handler class
//	Representing each key in a char array where each one is a ASCII.
//  Storing 'u' 'd' or 'h'
//  These represent Up, Down or held states for the keys
//
//	No Unit tests
//
//--------------------------------------------------------------------------
#pragma once

#include <Windows.h>

class CKeyboard
{
public:
	CKeyboard(float updateTick = 100, int keyHeldTime = 500);
	~CKeyboard();

	bool Initialise(float updateTick, int keyHeldTime);

	void SetUpdateTick(float updateTick);
	void SetKeyHeldTime(float delayTime);

	bool IsKeyDown(char key);
	bool IsKeyUp(char key);
	bool IsKeyHeld(char key);

	void Update(float deltaT);

	bool VHandleEvent(UINT msg, WPARAM wParam);

private:
	// Supporting ASCII
	char m_keys[256];
	int m_keysTimer[256];
	
	int m_keyHeldTime;

	float m_updateTimer;
	float m_updateTick;
};

