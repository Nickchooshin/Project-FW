#pragma once

class CInputDevice : public Singleton<CInputDevice>
{
protected :
	static LPDIRECTINPUT8 m_lpkDInput ;
	static HWND m_hWnd ;

public :
	CInputDevice() ;
	~CInputDevice() ;

	bool InitDevice(HINSTANCE hInstance, HWND hWnd) ;
	void Release() ;

	//virtual HRESULT Update() = 0 ;
} ;