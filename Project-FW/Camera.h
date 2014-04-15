#pragma once
#include <d3dx9.h>

class CCamera
{
private :
	float m_fX, m_fY ;
public :
	static LPDIRECT3DDEVICE9 pd3dDevice ;
	static float WinWidth, WinHeight ;

public :
	CCamera() ;
	~CCamera() ;

	void SetXY(float x, float y) ;

	void Run() ;
} ;