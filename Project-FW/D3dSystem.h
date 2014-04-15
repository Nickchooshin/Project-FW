#pragma once

#include <d3d9.h>

class CD3dSystem
{
private :
	HINSTANCE			m_hInst ;
	LPDIRECT3D9			m_pD3d ;
	LPDIRECT3DDEVICE9	m_pd3dDevice ;

public :
	CD3dSystem() ;
	~CD3dSystem() ;

	//void Release() ;

	HRESULT InitD3d(HINSTANCE hInst, HWND hWnd, int nWidth, int nHeight, char* ErrorStr) ;
	LPDIRECT3DDEVICE9 GetDevice() ;

	bool BeginScene() ;
	void EndScene() ;
private :
	void SetRenderState() ;
} ;