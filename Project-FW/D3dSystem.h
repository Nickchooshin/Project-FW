#pragma once

#include <d3d9.h>

class CD3dSystem
{
private :
	HINSTANCE			m_hInst ;
	LPDIRECT3D9			g_pD3d ;
	LPDIRECT3DDEVICE9	g_pd3dDevice ;

public :
	CD3dSystem() ;
	~CD3dSystem() ;

	void Release() ;

	HRESULT InitD3d(HINSTANCE hInst, HWND hWnd, int nWidth, int nHeight, char* ErrorStr) ;
	LPDIRECT3DDEVICE9 GetDevice() ;
private :
	void SetRenderState() ;
} ;