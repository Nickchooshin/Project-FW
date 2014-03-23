#pragma once
#include "Process.h"

class CKeyboard ;
class CMouse ;

class Game : public Process
{
private :
	void InputUpdate() ;

	CKeyboard* Keyboard ;
	CMouse* Mouse ;

public :
	Game() ;
	virtual ~Game() ;

	void Initialize() ;
	void Terminate() ;
	void Pulse() ;	
	void Render() ;
} ;