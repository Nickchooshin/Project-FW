#include "StdAfx.h"
#include "Mouse.h"

CMouse::CMouse()
{
	DI_Mouse = NULL ;

	for(int i=0; i<3; i++)
	{
		mClick[i] = false ;
	}
}
CMouse::~CMouse()
{
	if(DI_Mouse!=NULL)
	{
		DI_Mouse->Unacquire() ;
		DI_Mouse->Release() ;
		DI_Mouse = NULL ;
	}
}

bool CMouse::Initialize()
{
	if( FAILED( m_lpkDInput->CreateDevice( GUID_SysMouse, &DI_Mouse, NULL ) ) )
	{
		MessageBox(NULL, "Mouse CreateDevice Fail", "Error", MB_OK) ;
		return false ;
	}
	if( FAILED( DI_Mouse->SetDataFormat( &c_dfDIMouse ) ) )
	{
		MessageBox(NULL, "Mouse SetDataFormat Fail", "Error", MB_OK) ;
		return false ;
	}
	if( FAILED( DI_Mouse->SetCooperativeLevel( m_hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND ) ) )
	{
		MessageBox(NULL, "Mouse SetCooperativeLevel Fail", "Error", MB_OK) ;
		return false ;
	}

	return true ;
}

HRESULT CMouse::Update()
{
	HRESULT hr ;

	if( FAILED( DI_Mouse->GetDeviceState( sizeof(MouseBuffer), &MouseBuffer ) ) )
	{
		hr = DI_Mouse->Acquire() ;

		while(hr == DIERR_INPUTLOST)
		{
			hr = DI_Mouse->Acquire() ;
		}

		if( FAILED( hr ) )
			return hr ;
	}

	return S_OK ;
}

bool CMouse::MouseState(int Button, int Type)	// 1-Mouse_D, 2-Mouse_U, 3-Click_D, 4-Click_U, Double_Click
{
	bool bReturn=false ;

	if(Type==1 && mBuffer[Button][0].mClick)
		bReturn = true ;

	else if(Type==2 && !mBuffer[Button][0].mClick)
		bReturn = true ;

	else if(Type==3 && bMouseRun[Button] && (mBuffer[Button][0].mClick && !mBuffer[Button][1].mClick))
		bReturn = true ;

	else if(Type==4 && bMouseRun[Button] && (!mBuffer[Button][0].mClick && mBuffer[Button][1].mClick))
		bReturn = true ;
	
	else if(Type==5 && ((mBuffer[Button][0].mClick && mBuffer[Button][2].mClick) && (mBuffer[Button][0].kTime - mBuffer[Button][2].kTime <= 0.5f)))
		bReturn = true ;

	return bReturn ;
}

void CMouse::TakeBuffer()
{
	for(int i=0; i<3; i++)
	{
		bMouseRun[i] = false ;

		if((MouseBuffer.rgbButtons[0] == 0x80) && (!mClick[i]))
		{
			mClick[i] = true ;
			bMouseRun[i] = true ;
		}
		else if((MouseBuffer.rgbButtons[0] != 0x80) && (mClick[i]))
		{
			mClick[i] = false ;
			bMouseRun[i] = true ;
		}

		if(bMouseRun[i])
			SetmBuffer(i, mClick[i]) ;
	}
}

void CMouse::SetmBuffer(int Button, bool mClick)
{
	for(int i=1; i>=0; i--)
		mBuffer[Button][i+1] = mBuffer[Button][i] ;
	mBuffer[Button][0].mClick = mClick ;
	mBuffer[Button][0].kTime = (float)GetTickCount() * 0.001f ;
}