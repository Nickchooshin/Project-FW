#pragma once

#include "Singleton.h"
#include <dinput.h>

class Keyboard ;

class InputDevice : public Singleton<InputDevice>
{
private :
	LPDIRECTINPUT8 m_pDInput ;
	HWND m_hWnd ;

public :
	InputDevice() ;
	~InputDevice() ;

	bool InitDevice(HINSTANCE hInstance, HWND hWnd) ;
	//void Release() ;

	//virtual HRESULT Update() = 0 ;

	friend Keyboard ;
} ;

#define g_InputDevice InputDevice::GetInstance()