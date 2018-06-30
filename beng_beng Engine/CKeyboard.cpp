#include "CKeyboard.h"

CKeyboard::CKeyboard(float updateTick, int keyHeldTime) :
	m_updateTimer(0.f), m_updateTick(updateTick), m_keyHeldTime(keyHeldTime)
{
	for (int i = 0; i < 256; i++)
	{
		m_keys[i] = 'u';
		m_keysTimer[i] = 0;
	}
}


CKeyboard::~CKeyboard()
{
}

bool CKeyboard::Initialise(float updateTick, int keyHeldTime)
{
	m_updateTick = updateTick;
	m_keyHeldTime = keyHeldTime;
	return true;
}

void CKeyboard::SetUpdateTick(float updateTick)
{
	m_updateTick = updateTick;
}

void CKeyboard::SetKeyHeldTime(float delayTime)
{
	m_keyHeldTime = delayTime;
}

bool CKeyboard::IsKeyDown(char key)
{
	// Consider key press or held as down
	if (m_keys[key] == 'd' || m_keys[key] == 'h')
		return true;

	return false;
}

bool CKeyboard::IsKeyUp(char key)
{
	if (m_keys[key] == 'u')
		return true;

	return false;
}

bool CKeyboard::IsKeyHeld(char key)
{
	// Returns true if key held for specific time unlike IsKeyDown()
	if (m_keys[key] == 'h')
		return true;

	return false;
}

void CKeyboard::Update(float deltaT)
{
	m_updateTimer += deltaT;

	if (m_updateTimer > m_updateTick)
	{
		for (int i = 0; i < 256; i++)
		{
			if (m_keys[i] == 'd')
			{
				m_keysTimer[i] += (int)deltaT;
				if (m_keysTimer[i] > m_keyHeldTime)
				{
					m_keys[i] = 'h';
				}
			}
		}

		m_updateTimer = 0;
	}
}

bool CKeyboard::VHandleEvent(UINT msg, WPARAM wParam)
{
	bool handledEvent = false;

	switch (msg)
	{
	case WM_KEYDOWN:
		m_keys[wParam] = 'd';
		handledEvent = true;
		break;

	case WM_KEYUP:
		m_keys[wParam] = 'u';
		m_keysTimer[wParam] = 0;	// Reset held timer when key up
		handledEvent = true;
		break;

	default:
		break;
	}

	return handledEvent;
}
