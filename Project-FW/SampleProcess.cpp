#include "SampleProcess.h"

#include "Keyboard.h"
#include "Mouse.h"

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
	Key = new Keyboard ;
	Key->Init() ;

	mouse = new Mouse ;
	mouse->Init() ;
}

void SampleProcess::Destroy()
{
	delete Key ;
	delete mouse ;
}

void SampleProcess::Update(float dt)
{
	Key->Update() ;
	mouse->Update() ;

	if(Key->IsButtonDown(DIK_UP))
	{
		MessageBox(NULL, "UP", "UP", MB_OK) ;
	}

	if(mouse->IsMouse(Mouse::LBUTTON_DOWN))
	{
		MessageBox(NULL, "LBUTTON_DOWN", "LBUTTON_DOWN", MB_OK) ;
	}
}

void SampleProcess::Render()
{
}