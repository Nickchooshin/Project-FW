#pragma once
#include <d3dx9.h>

class CSprite
{
private :
	LPDIRECT3DVERTEXBUFFER9	m_pVB ;
	LPDIRECT3DINDEXBUFFER9	m_pIB ;
	LPDIRECT3DTEXTURE9		m_pTexture ;

	float m_fWidth, m_fHeight ;
	float m_fX, m_fY ;
	float m_fCenterX, m_fCenterY ;
	float m_fScaleX, m_fScaleY ;
	float m_fAngle[3] ;
	int m_R, m_G, m_B ;
	int m_nAlpha ;
	float m_tu[4], m_tv[4] ;

	D3DXIMAGE_INFO m_TexInfo ;
public :
	static LPDIRECT3DDEVICE9 pd3dDevice ;

public :
	CSprite() ;
	~CSprite() ;

	bool Init(char *texfile) ;
	bool Init(float Width, float Height, char *texfile) ;

	void SetXY(float X, float Y) ;								// ��ǥ���� (�߾� ����)
	void SetCenterPoint(float CenterX, float CenterY) ;			// �߽��� ����
	void SetScale(float ScaleX, float ScaleY) ;					// Ȯ��, ���
	void SetAngle(float Angle, char Direction='z') ;			// ���� ���� (�ݽð����)
	void SetRGB(int R, int G, int B) ;							// RGB�� ����
	void SetAlpha(int Alpha) ;									// ���İ� ���� 0~255
	
	void SetTextureUV(float u1, float v1, float u2, float v2) ;	// �ؽ��� UV ����
	void TexReverse() ;											// �ؽ��� ������

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