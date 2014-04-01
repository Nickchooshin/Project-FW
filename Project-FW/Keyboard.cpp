#include "Keyboard.h"
#include "InputDevice.h"

Keyboard::Keyboard()
{
	m_pDIDKeyboard = NULL ;

	ZeroMemory(KeyBuffer, sizeof(KeyBuffer)) ;

	for(int i=0; i<256; i++)
	{
		kStatusDown[i] = false ;
		kStatusUp[i] = false ;
	}
}
Keyboard::~Keyboard()
{
	if(m_pDIDKeyboard!=NULL)
	{
		m_pDIDKeyboard->Unacquire() ;
		m_pDIDKeyboard->Release() ;
		m_pDIDKeyboard = NULL ;
	}
}

bool Keyboard::Init()
{
	//if( FAILED( m_pDInput->CreateDevice( GUID_SysKeyboard, &m_pDIDKeyboard, NULL ) ) )
	if( FAILED( g_InputDevice->m_pDInput->CreateDevice( GUID_SysKeyboard, &m_pDIDKeyboard, NULL ) ) )
	{
		MessageBox(NULL, "Keyboard CreateDevice Fail", "Error", MB_OK) ;
		return false ;
	}
	if( FAILED( m_pDIDKeyboard->SetDataFormat( &c_dfDIKeyboard ) ) )
	{
		MessageBox(NULL, "Keyboard SetDataFormat Fail", "Error", MB_OK) ;
		return false ;
	}
	//if( FAILED( m_pDIDKeyboard->SetCooperativeLevel( hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND ) ) )
	if( FAILED( m_pDIDKeyboard->SetCooperativeLevel( g_InputDevice->m_hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND ) ) )
	{
		MessageBox(NULL, "KeyBoard SetCooperativeLevel Fail", "Error", MB_OK) ;
		return false ;
	}
	m_pDIDKeyboard->Acquire() ;
	m_pDIDKeyboard->GetDeviceState(sizeof(KeyBuffer), &KeyBuffer) ;
}

bool Keyboard::Update()
{
	HRESULT hr ;
	ZeroMemory(KeyBuffer, sizeof(KeyBuffer)) ;

	if( FAILED( m_pDIDKeyboard->GetDeviceState( sizeof(KeyBuffer), &KeyBuffer ) ) )
	{
		hr = m_pDIDKeyboard->Acquire() ;

		while(hr == DIERR_INPUTLOST) // hr == DIERR_INPUTLOST || hr == E_ACCESSDENIED
		{
			hr = m_pDIDKeyboard->Acquire() ;
		}

		if( FAILED( hr ) )
			return hr ;
	}

	return true ;
}

bool Keyboard::IsButtonDown(BYTE Button)
{
	if(KeyBuffer[Button] & 0x80)
	{
		kStatusDown[Button] = true ;

		return TRUE ;
	}

	return FALSE ;
}

bool Keyboard::IsButtonUp(BYTE Button)
{
	if(KeyBuffer[Button] & 0x80)
	{
		return FALSE ;
	}

	kStatusUp[Button] = true ;

	return TRUE ;
}

bool Keyboard::IsPressDown(BYTE Button)
{
	IsButtonUp(Button) ;
	kStatusDown[Button] = false ;
	IsButtonDown(Button) ;

	if(kStatusUp[Button] && kStatusDown[Button])
	{
		kStatusUp[Button] = false ;

		return TRUE ;
	}

	return FALSE ;
}

bool Keyboard::IsPressUp(BYTE Button)
{
	IsButtonDown(Button) ;
	kStatusUp[Button] = false ;
	IsButtonUp(Button) ;

	if(kStatusUp[Button] && kStatusDown[Button])
	{
		kStatusDown[Button] = false ;

		return TRUE ;
	}

	return FALSE ;
}