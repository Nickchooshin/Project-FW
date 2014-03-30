#include "SampleProcess.h"

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
}

void SampleProcess::Render()
{
}