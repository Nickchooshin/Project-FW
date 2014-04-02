#pragma once
#include <dinput.h>

class Keyboard
{
private :
	LPDIRECTINPUTDEVICE8 m_pDIDKeyboard ;

	char KeyBuffer[256] ;

public :
	Keyboard() ;
	~Keyboard() ;

	bool Init() ;

	bool Update() ;

	bool IsButtonDown(BYTE Button) ;
	bool IsButtonUp(BYTE Button) ;
} ;