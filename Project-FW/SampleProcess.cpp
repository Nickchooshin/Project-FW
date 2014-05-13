#include "SampleProcess.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "UISprite.h"
#include "CameraManager.h"

const int sprite_max=1000 ;

CSprite Sprite, Sprite2 ;
CUISprite UISprite, UISprite2 ;

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
	g_CameraManager->AddCamera(new CCamera(), 0) ;
	g_CameraManager->AddCamera(new CCamera(), 1) ;
	g_CameraManager->MovePosition(50.0f, 50.0f, 1) ;

	Sprite.Init(50.0f, 50.0f, "sample_texture.png") ;
	Sprite.SetTextureUV(0.0f, 0.0f, 50.0f, 50.0f) ;
	UISprite.Init(60.0f, 80.0f, "sample_texture2.png") ;
	UISprite.Init("sample_texture2.png") ;

	Sprite2.Init("sample_texture2.png") ;
	UISprite2.Init("sample_texture2.png") ;
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

	if(g_Keyboard->IsButtonDown(DIK_1))
	{
		Sprite.SetTextureUV(0.0f, 0.0f, 50.0f, 50.0f) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_2))
	{
		Sprite.SetTextureUV(50.0f, 0.0f, 100.0f, 50.0f) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_3))
	{
		Sprite.SetTextureUV(0.0f, 50.0f, 50.0f, 100.0f) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_4))
	{
		Sprite.SetTextureUV(50.0f, 50.0f, 100.0f, 100.0f) ;
	}

	if(g_Keyboard->IsButtonDown(DIK_8))
	{
		Sprite.SetZ(-1.0f) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_9))
	{
		Sprite.SetZ(1.0f) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_0))
	{
		Sprite.SetZ(0.0f) ;
	}

	if(g_Keyboard->IsButtonDown(DIK_5))
	{
		UISprite.SetZ(0.0f) ;
		UISprite2.SetZ(0.0f) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_6))
	{
		UISprite.SetZ(1.0f) ;
		UISprite2.SetZ(0.0f) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_7))
	{
		UISprite.SetZ(0.0f) ;
		UISprite2.SetZ(1.0f) ;
	}

	if(g_Keyboard->IsButtonDown(DIK_F1))
	{
		g_CameraManager->SetCamera(0) ;
	}
	if(g_Keyboard->IsButtonDown(DIK_F2))
	{
		g_CameraManager->SetCamera(1) ;
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
	Sprite2.SetXY(100.0f, 100.0f) ;
	UISprite.SetXY(100.0f, 100.0f) ;
	UISprite2.SetXY(50.0f, 50.0f) ;
}

void SampleProcess::Render()
{
	g_CameraManager->CameraRun() ;
	
	Sprite.Render() ;
	UISprite.Render() ;
	Sprite2.Render() ;
	UISprite2.Render() ;
}