#pragma once
#include <Windows.h>
#include <map>

class CInputDevice ;

class CD3dSystem
{
private :
	HINSTANCE			m_hInst ;
	LPDIRECT3D9			g_pD3d ;
	LPDIRECT3DDEVICE9	g_pd3dDevice ;
	std::map<std::string, LPDIRECT3DTEXTURE9> g_pTexture ;

	CInputDevice* m_InputDevice ;

public :
	CD3dSystem() ;
	~CD3dSystem() ;

	void Release() ;

	HRESULT InitD3d(HINSTANCE hInst, HWND hWnd, int nWidth, int nHeight, char* ErrorStr) ;
	LPDIRECT3DDEVICE9 GetDevice() ;
private :
	void SetRenderState() ;
} ;