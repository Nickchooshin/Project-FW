#pragma once
#include <Windows.h>

class CWinSystem
{
private :
	HINSTANCE m_hInst ;
	WNDCLASSEX m_wc ;
	HWND m_hWnd ;
	int m_WinWidth, m_WinHeight ;

	float t ;
	DWORD dwOldTime ;

public :
	CWinSystem(HINSTANCE hInst) ;
	~CWinSystem() ;

	void WinSet(LPCTSTR TitleName="FW_V - 0.1A", DWORD WinStyle=WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, int WinWidth=640, int WinHeight=480) ;	// WS_THICKFRAME - 윈도우창 늘리기/줄이기 크기조정 지원안함.
	void WinMsg(int Frame=60) ;
	void WinEnd() ;
private :
	void MsgLoop(int Frame) ;
	friend LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) ;
} ;