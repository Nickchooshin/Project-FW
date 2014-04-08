#include "SampleProcess.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

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
		MessageBox(NULL, "UP", "UP", MB_OK) ;
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
}