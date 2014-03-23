#pragma once

class CKeyBuffer
{
public :
	bool kPress ;
	float kTime ;

public :
	CKeyBuffer() : kPress(false), kTime(0.0) {}
	CKeyBuffer(bool b, float f) : kPress(b), kTime(f) {}
	~CKeyBuffer() {}
} ;

class CKeyboard : public CInputDevice
{
private :
	LPDIRECTINPUTDEVICE8 DI_Key ;
	BYTE KeyBuffer[256] ;

	bool kPress[256] ;
	CKeyBuffer kBuffer[256][3] ;
	bool bKeyRun[256] ;

public :
	CKeyboard() ;
	~CKeyboard() ;

	bool Initialize() ;

	HRESULT Update() ;

	bool KeyState(BYTE Button, int Type) ;
	void TakeBuffer() ;
	void SetkBuffer(BYTE Button, bool kPress) ;
} ;