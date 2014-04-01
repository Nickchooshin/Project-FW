#include "SampleProcess.h"

#include "Keyboard.h"

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
}

void SampleProcess::Destroy()
{
	delete Key ;
}

void SampleProcess::Update(float dt)
{
	Key->Update() ;

	if(Key->IsButtonDown(DIK_UP))
	{
		MessageBox(NULL, "UP", "UP", MB_OK) ;
	}
}

void SampleProcess::Render()
{
}