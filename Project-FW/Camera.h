#pragma once
#include <d3dx9.h>

class CCamera
{
private :
	D3DXVECTOR3 m_Position ;
public :
	static LPDIRECT3DDEVICE9 pd3dDevice ;
	static float WinWidth, WinHeight ;

public :
	CCamera() ;
	~CCamera() ;

	void SetPosition(float x, float y) ;

	void Run() ;
} ;