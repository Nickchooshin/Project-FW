#pragma once
#include <d3dx9.h>

class CSprite
{
private :
	LPDIRECT3DVERTEXBUFFER9	m_pVB ;
	LPDIRECT3DINDEXBUFFER9	m_pIB ;
	LPDIRECT3DTEXTURE9		m_pTexture ;

	float m_fWidth, m_fHeight ;
	float m_fScaleX, m_fScaleY ;
	float m_fAngle[3] ;
	float m_fX, m_fY ;
	int m_R, m_G, m_B ;
	int m_nAlpha ;
	float m_tu[4], m_tv[4] ;
public :
	static LPDIRECT3DDEVICE9 pd3dDevice ;

public :
	CSprite() ;
	~CSprite() ;

	bool Init(float Width, float Height, char *texfile) ;

	void Render() ;
private :
	HRESULT InitVB() ;

	bool SetTexture(char *texfile) ;
	void SetupMatrices() ;
} ;

struct SPRITE_VERTEX
{
	float		x, y, z ;	// The position
	D3DCOLOR	color ;		// The color
	float		tu, tv ;	// The texture coordinates (x, y)
} ;

#define D3DFVF_SPRITE_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)