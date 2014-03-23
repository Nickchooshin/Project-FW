#pragma once

class C3DSprite
{
public :
	enum eAxis {AxisX=0, AxisY, AxisZ} ;
private :
	static LPDIRECT3DDEVICE9 m_pd3dDevice ;
	LPDIRECT3DVERTEXBUFFER9	m_pVB ;
	LPDIRECT3DTEXTURE9		m_pTexture ;

	int m_nWidth, m_nHeight ;
	float m_fScaleX, m_fScaleY ;
	float m_fAngle[3] ;
	float m_fX, m_fY ;
	int m_R, m_G, m_B ;
	int m_nAlpha ;
	float m_tu[4], m_tv[4] ;

public :
	C3DSprite() ;
	~C3DSprite() ;

	static void SetDevice(LPDIRECT3DDEVICE9 d3dDevice) ;
	bool Initialize(int Width, int Height) ;

	void SetUV(float u1, float v1, float u2, float v2) ;
	void SetUV(int X1, int Y1, int X2, int Y2, int Width, int Height) ;
	void SetXY(float X, float Y) ;
	void SetXY(int X, int Y) ;
	void SetXYLt(float X, float Y) ;
	void SetXYLt(int X, int y) ;
	void SetRGB(int R, int G, int B) ;
	void SetAlpha(int Alpha) ;
	void SetAngle(float Angle, eAxis Axis) ;
	void SetScale(float ScaleX, float ScaleY) ;

	void TexReverse() ;

	void Render() ;
private :
	HRESULT InitVB() ;
	void SetupMatrices() ;
} ;

LPDIRECT3DDEVICE9 C3DSprite::m_pd3dDevice = NULL ;