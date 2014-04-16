#include "SampleProcess.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "Camera.h"

CSprite pSprite ;
CCamera Camera ;

SampleProcess::SampleProcess()
{
}
SampleProcess::~SampleProcess()
{
}

Process* SampleProcess::process()
{
	Process *process = new SampleProcess ;

	return process ;
}

void SampleProcess::Init()
{
	pSprite.Init(50.0f, 50.0f, "sample_texture.png") ;
}

void SampleProcess::Destroy()
{
}

void SampleProcess::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;

	if(g_Keyboard->IsButtonDown(DIK_UP))
	{
		//MessageBox(NULL, "UP", "UP", MB_OK) ;
		pSprite.SetAngle(0) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_DOWN))
	{
		pSprite.TexReverse() ;
	}
	if(g_Keyboard->IsButtonDown(DIK_RIGHT))
	{
		pSprite.SetAngle(-90) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_LEFT))
	{
		pSprite.SetAngle(90) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_0))
	{
		pSprite.SetCenterPoint(0.0f, 0.0f) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_1))
	{
		pSprite.SetCenterPoint(10.f, 0.0f) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_2))
	{
		pSprite.SetCenterPoint(-10.f, 0.0f) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_3))
	{
		pSprite.SetCenterPoint(0.0f, 10.0f) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_4))
	{
		pSprite.SetCenterPoint(0.0f, -10.0f) ;
	}

	if(g_Mouse->IsMouse(g_Mouse->LBUTTON_DOWN))
	{
		MessageBox(NULL, "LBUTTON_DOWN", "LBUTTON_DOWN", MB_OK) ;
	}

	if(g_Joystick->IsButtonDown(0))
	{
		MessageBox(NULL, "0 Button", "0 BUtton", MB_OK) ;
	}
	if(g_Joystick->IsButtonDown(1))
	{
		MessageBox(NULL, "1 Button", "1 BUtton", MB_OK) ;
	}
	if(g_Joystick->IsButtonDown(3))
	{
		MessageBox(NULL, "3 Button", "3 BUtton", MB_OK) ;
	}
	if(g_Joystick->IsButtonDown(4))
	{
		MessageBox(NULL, "4 Button", "4 BUtton", MB_OK) ;
	}
	if(g_Joystick->IsAxisMin(1000, 'x'))
	{
		MessageBox(NULL, "X 1000", "X 1000", MB_OK) ;
	}
	if(g_Joystick->IsPov(22500))
	{
		MessageBox(NULL, "POV ��", "POV ��", MB_OK) ;
	}
}

void SampleProcess::Render()
{
	Camera.Run() ;

	pSprite.Render() ;
}