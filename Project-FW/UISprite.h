#pragma once
#include <d3dx9.h>

class CUISprite
{
private :
	LPDIRECT3DVERTEXBUFFER9	m_pVB ;
	LPDIRECT3DINDEXBUFFER9	m_pIB ;
	LPDIRECT3DTEXTURE9		m_pTexture ;

	float m_fWidth, m_fHeight ;
	float m_fX, m_fY ;
	int m_R, m_G, m_B ;
	int m_nAlpha ;
	float m_tu[4], m_tv[4] ;

	D3DXIMAGE_INFO m_TexInfo ;

public :
	CUISprite() ;
	~CUISprite() ;

	bool Init(char *texfile) ;
	bool Init(float Width, float Height, char *texfile) ;

	void SetXY(float X, float Y) ;						// ��ǥ���� (�߾� ����)
	void SetRGB(int R, int G, int B) ;					// RGB�� ����
	void SetAlpha(int Alpha) ;							// ���İ� ���� 0~255
	
	void SetTextureUV(float u1, float v1, float u2, float v2) ;	// �ؽ��� UV ����
	void TexReverse() ;									// �ؽ��� ������

	void Render() ;
private :
	HRESULT InitVB() ;

	bool SetTexture(char *texfile) ;
	void SetupMatrices() ;
} ;

struct UISPRITE_VERTEX
{
	float		x, y, z, rhw ;	// The position
	D3DCOLOR	color ;			// The color
	float		tu, tv ;		// The texture coordinates (x, y)
} ;

#define D3DFVF_UISPRITE_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)