#pragma once

class CMouseBuffer
{
public :
	bool mClick ;
	float kTime ;

public :
	CMouseBuffer() : mClick(false), kTime(0.0) {}
	CMouseBuffer(bool b, float f) : mClick(b), kTime(f) {}
	~CMouseBuffer() {}
} ;

class CMouse : public CInputDevice
{
private :
	LPDIRECTINPUTDEVICE8 DI_Mouse ;
	DIMOUSESTATE MouseBuffer ;

	bool mClick[3] ;
	CMouseBuffer mBuffer[3][3] ;
	bool bMouseRun[3] ;

	//char mStatus[6] ;
public :
	enum MouseType{LBUTTON_DOWN, LBUTTON_UP, RBUTTON_DOWN, RBUTTON_UP, MBUTTON_DOWN, MBUTTON_UP} ;

public :
	CMouse() ;
	~CMouse() ;

	bool Initialize() ;

	HRESULT Update() ;

	bool MouseState(int Button, int Type) ;
	void TakeBuffer() ;
	void SetmBuffer(int Button, bool mClick) ;

	//BOOL IsMouse(MouseType Mouse) ;
	//BOOL IsClickDown(MouseType MouseUp, MouseType MouseDown) ;
	//BOOL IsClickUp(MouseType MouseUp, MouseType MouseDown) ;
} ;

/*class CKeyboard : public CInputDevice
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
} ;*/