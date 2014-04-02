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
}

void SampleProcess::Render()
{
}