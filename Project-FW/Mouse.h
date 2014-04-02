#pragma once
#include <dinput.h>

class Mouse
{
private :
	LPDIRECTINPUTDEVICE8 m_pDIDMouse ;

	DIMOUSESTATE MouseBuffer ;

	char KeyBuffer[256] ;
public :
	enum MouseButtonType{LBUTTON_DOWN, LBUTTON_UP, RBUTTON_DOWN, RBUTTON_UP} ;

public :
	Mouse() ;
	~Mouse() ;

	bool Init() ;

	bool Update() ;

	bool IsMouse(MouseButtonType ButtonType) ;
} ;