#include "WinSystem.h"
#include "D3dSystem.h"
#include "ProcessManager.h"

CWinSystem::CWinSystem(HINSTANCE hInst) : m_hInst(hInst),
											t(0.0f),
											dwOldTime(0)
{
}
CWinSystem::~CWinSystem()
{
}

void CWinSystem::WinSet(LPCTSTR TitleName, DWORD WinStyle, int WinWidth, int WinHeight)
{
	m_wc.cbSize = sizeof(WNDCLASSEX) ;
	m_wc.style = CS_CLASSDC ;
	m_wc.lpfnWndProc = MsgProc ;
	m_wc.cbClsExtra = 0L ;
	m_wc.cbWndExtra = 0L ;
	m_wc.hInstance = m_hInst ;
	m_wc.hIcon = NULL ;
	m_wc.hCursor = LoadCursor(NULL, IDC_ARROW) ;
	m_wc.hbrBackground = NULL ;
	m_wc.lpszMenuName = NULL ;
	m_wc.lpszClassName = "FW_V" ;
	m_wc.hIconSm = NULL ;

	RegisterClassEx( &m_wc );

	m_WinWidth = WinWidth ;
	m_WinHeight = WinHeight ;

	WinStyle = WinStyle & ~WS_THICKFRAME ;

	int FrameX, FrameY ;
	int CaptionY ;
	FrameX = GetSystemMetrics(SM_CXFRAME) ;
	FrameY = GetSystemMetrics(SM_CYFRAME) ;
	CaptionY = GetSystemMetrics(SM_CYCAPTION) ;

	m_hWnd = CreateWindow( "FW_V", TitleName,
							WinStyle,
							CW_USEDEFAULT, CW_USEDEFAULT, m_WinWidth+(FrameX<<1)-10, m_WinHeight+(FrameY<<1)+CaptionY-10,
							NULL, NULL, m_wc.hInstance, NULL ) ;

	/*RECT rt = { 0, 0, m_WinWidth, m_WinHeight } ;
	//AdjustWindowRect( &rt, WS_OVERLAPPEDWINDOW, false ) ;
	AdjustWindowRect( &rt, WinStyle, false ) ;

	m_hWnd = CreateWindow( "FW_V", TitleName,
							WinStyle,
							CW_USEDEFAULT, CW_USEDEFAULT, rt.right-rt.left, rt.bottom-rt.top,
							NULL, NULL, m_wc.hInstance, NULL ) ;*/
}

void CWinSystem::WinMsg(int Frame)
{
	char ErrorStr[1024] ;

	if( SUCCEEDED( D3dSystem.InitD3d( m_hInst, m_hWnd, m_WinWidth, m_WinHeight, ErrorStr ) ) )	// 다이렉트X 초기화 && 시스템 초기화
	{
		g_ProcessManager->InitProcess() ;

		ShowWindow( m_hWnd, SW_SHOWDEFAULT );
		UpdateWindow( m_hWnd );

		MsgLoop(Frame) ;	// 메세지 루프
    }
	else
		MessageBox(m_hWnd, ErrorStr, "Error", MB_OK) ;
}

void CWinSystem::WinEnd()
{
	UnregisterClass( "FW_V", m_wc.hInstance );
}

void CWinSystem::MsgLoop(int Frame)
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while( msg.message!=WM_QUIT ) // WM_QUIT메시지 발생시 종료
	{
		if( PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) // 메시지가 있다 없다.
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			t = (float)(GetTickCount() - dwOldTime) * 0.001f ;

			if(t>=(float)(1/Frame))
			{
				Update() ;
				Render() ;

				dwOldTime = GetTickCount() ;
			}
		}
	}
}

void CWinSystem::Update()
{
	g_ProcessManager->UpdateProcess(t) ;
}

void CWinSystem::Render()
{
	if( D3dSystem.BeginScene() )
	{
		g_ProcessManager->RenderProcess() ;

		D3dSystem.EndScene() ;
	}
}

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//LONG wndStyle ;

	switch(msg)
	{
	/*case WM_SIZE :
		wndStyle = GetWindowLong(hWnd, GWL_STYLE) ;
		wndStyle = wndStyle & ~WS_THICKFRAME ;
		SetWindowLong(hWnd, GWL_STYLE, wndStyle) ;
		SendMessage(hWnd, WM_NCPAINT, wParam, lParam) ;
		return 0 ;*/
	//case WM_MOUSEMOVE:
	//	mouse.x = LOWORD(lParam) ;
	//	mouse.y = HIWORD(lParam) ;
	//	g_InputManager->SetMousePoint(mouse) ;
	//	break;
	case WM_DESTROY :
		//	Cleanup();
		PostQuitMessage( 0 ) ;
		return 0 ;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam) ;
}