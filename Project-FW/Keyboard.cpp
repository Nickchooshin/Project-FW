#include "StdAfx.h"
#include "Keyboard.h"

CKeyboard::CKeyboard()
{
	DI_Key = NULL ;

	ZeroMemory(KeyBuffer, sizeof(KeyBuffer)) ;

	for(int i=0; i<256; i++)
		kPress[i] = false ;
}
CKeyboard::~CKeyboard()
{
	if(DI_Key!=NULL)
	{
		DI_Key->Unacquire() ;
		DI_Key->Release() ;
		DI_Key = NULL ;
	}
}

bool CKeyboard::Initialize()
{
	if( FAILED( m_lpkDInput->CreateDevice( GUID_SysKeyboard, &DI_Key, NULL ) ) )
	{
		MessageBox(NULL, "KeyBoard CreateDevice Fail", "Error", MB_OK) ;
		return false ;
	}
	if( FAILED( DI_Key->SetDataFormat( &c_dfDIKeyboard ) ) )
	{
		MessageBox(NULL, "KeyBoard SetDataFormat Fail", "Error", MB_OK) ;
		return false ;
	}
	if( FAILED( DI_Key->SetCooperativeLevel( m_hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND ) ) )
	{
		MessageBox(NULL, "KeyBoard SetCooperativeLevel Fail", "Error", MB_OK) ;
		return false ;
	}
	DI_Key->Acquire() ;
	DI_Key->GetDeviceState(sizeof(KeyBuffer), &KeyBuffer) ;

	return true ;
}

HRESULT CKeyboard::Update()
{
	HRESULT hr ;
	ZeroMemory(KeyBuffer, sizeof(KeyBuffer));

	if( FAILED( DI_Key->GetDeviceState( sizeof(KeyBuffer), &KeyBuffer ) ) )
	{
		hr = DI_Key->Acquire();

		while(hr == DIERR_INPUTLOST)	// hr == DIERR_INPUTLOST || hr == E_ACCESSDENIED
		{
			hr = DI_Key->Acquire();
		}

		if( FAILED( hr ) )
			return hr;
	}

	return S_OK ;
}

bool CKeyboard::KeyState(BYTE Button, int Type)	// 1-Button_D, 2-Button_U, 3-Press_D, 4-Press_U, 5-Roll
{
	bool bReturn=false ;

	if(Type==1 && kBuffer[Button][0].kPress)
		bReturn = true ;

	else if(Type==2 && !kBuffer[Button][0].kPress)
		bReturn = true ;

	else if(Type==3 && bKeyRun[Button] && (kBuffer[Button][0].kPress && !kBuffer[Button][1].kPress))
		bReturn = true ;

	else if(Type==4 && bKeyRun[Button] && (!kBuffer[Button][0].kPress && kBuffer[Button][1].kPress))
		bReturn = true ;

	else if(Type==5 && ((kBuffer[Button][0].kPress && kBuffer[Button][2].kPress) && (kBuffer[Button][0].kTime - kBuffer[Button][2].kTime <= 0.5f)))
		bReturn = true ;

	return bReturn ;
}

void CKeyboard::TakeBuffer()
{
	for(int i=0; i<256; i++)	// 106
	{
		bKeyRun[i] = false ;

		if((KeyBuffer[i] & 0x80) && (!kPress[i]))
		{
			kPress[i] = true ;
			bKeyRun[i] = true ;
		}
		else if(!(KeyBuffer[i] & 0x80) && (kPress[i]))
		{
			kPress[i] = false ;
			bKeyRun[i] = true ;
		}

		if(bKeyRun[i])
			SetkBuffer(i, kPress[i]) ;
	}

	/*bKeyRun[Button] = false ;

	if((KeyBuffer[Button] & 0x80) && (!kPress[Button]))
	{
		kPress[Button] = true ;
		bKeyRun[Button] = true ;
	}
	else if(!(KeyBuffer[Button] & 0x80) && (kPress[Button]))
	{
		kPress[Button] = false ;
		bKeyRun[Button] = true ;
	}*/
}

void CKeyboard::SetkBuffer(BYTE Button, bool kPress)
{
	for(int i=1; i>=0; i--)
		kBuffer[Button][i+1] = kBuffer[Button][i] ;
	kBuffer[Button][0].kPress = kPress ;
	kBuffer[Button][0].kTime = (float)GetTickCount() * 0.001f ;
}