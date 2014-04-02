#pragma once

#include "Singleton.h"
#include <dinput.h>

typedef bool (CALLBACK *EX)(const DIDEVICEOBJECTINSTANCE*, VOID*);

class Joystick : public Singleton<Joystick>
{
private :
	LPDIRECTINPUTDEVICE8 m_pDIDJoystick ;

public :
	Joystick() ;
	~Joystick() ;

	bool Init() ;

	bool Update() ;

	bool IsButtonDown(BYTE Button) ;
	bool IsButtonUp(BYTE Button) ;
private :
	friend BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE* instance, VOID* context) ;
} ;

#define g_Joystick Joystick::GetInstance()