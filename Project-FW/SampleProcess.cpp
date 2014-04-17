#include "SampleProcess.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "UISprite.h"
#include "Camera.h"

const int sprite_max=1000 ;

CSprite Sprite ;
CUISprite UISprite ;
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
	Sprite.Init(50.0f, 50.0f, "sample_texture.png") ;
	UISprite.Init(60.0f, 80.0f, "sample_texture2.png") ;
}

void SampleProcess::Destroy()
{
}

void SampleProcess::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;

	static float x=0.0f, y=0.0f ;

	if(g_Keyboard->IsButtonDown(DIK_UP))
	{
		y += 1.5f ;
	}
	if(g_Keyboard->IsButtonDown(DIK_DOWN))
	{
		y -= 1.5f ;
	}
	if(g_Keyboard->IsButtonDown(DIK_RIGHT))
	{
		x += 1.5f ;
	}
	if(g_Keyboard->IsButtonDown(DIK_LEFT))
	{
		x -= 1.5f ;
	}

	/*if(g_Mouse->IsMouse(g_Mouse->LBUTTON_DOWN))
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
		MessageBox(NULL, "POV ก็", "POV ก็", MB_OK) ;
	}*/

	Sprite.SetXY(x, y) ;
	UISprite.SetXY(100.0f, 100.0f) ;
}

void SampleProcess::Render()
{
	Camera.Run() ;

	Sprite.Render() ;
	UISprite.Render() ;
}