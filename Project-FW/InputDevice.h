#pragma once

#include "Singleton.h"
#include <dinput.h>

class Keyboard ;
class Mouse ;

class InputDevice : public Singleton<InputDevice>
{
private :
	LPDIRECTINPUT8 m_pDInput ;
	HWND m_hWnd ;

public :
	InputDevice() ;
	~InputDevice() ;

	bool InitDevice(HINSTANCE hInstance, HWND hWnd) ;

	friend Keyboard ;
	friend Mouse ;
} ;

#define g_InputDevice InputDevice::GetInstance()