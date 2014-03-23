#pragma once
#include "Singleton.h"

class Process : public Singleton<Process>
{
private :
	virtual void InputUpdate() = 0 ;
public :
	//virtual void ChangeSubProcess() = 0 ;
	virtual void Initialize() = 0 ;
	virtual void Terminate() = 0 ;
	virtual void Pulse() = 0 ;
	virtual void Render() = 0 ;
} ;
#define g_Process Process::GetSingleton()

enum ProcessType ;

void ChangeProcess(ProcessType cProcess) ;