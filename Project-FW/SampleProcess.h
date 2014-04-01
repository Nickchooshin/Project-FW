#pragma once

#include "Process.h"

class Keyboard ;

class SampleProcess : public Process
{
	Keyboard *Key ;

public :
	static Process* process() ;

	SampleProcess() ;
	virtual ~SampleProcess() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;