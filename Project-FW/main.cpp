/*#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 ) */

#include "WinSystem.h"

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
	CWinSystem WinSystem(hInst) ;

	WinSystem.WinSet() ;	// WS_THICKFRAME - ������â �ø���/���̱� ũ������ ��������.
	WinSystem.WinMsg() ;
	WinSystem.WinEnd() ;

	return 0 ;
}