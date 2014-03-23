#include "InputDevice.h"

LPDIRECTINPUT8 CInputDevice::m_lpkDInput ;
HWND CInputDevice::m_hWnd ;

CInputDevice::CInputDevice()
{
}
CInputDevice::~CInputDevice()
{
}

bool CInputDevice::InitDevice(HINSTANCE hInstance, HWND hWnd)
{
	m_hWnd = hWnd ;

	if( FAILED( DirectInput8Create( hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_lpkDInput, NULL ) ) )
	{
		MessageBox(NULL, "DirectInput8Create Fail", "Error", MB_OK) ;
		return false ;
	}

	return true ;
}

void CInputDevice::Release()
{
	if(m_lpkDInput!=NULL)
	{
		m_lpkDInput->Release() ;
	}
}