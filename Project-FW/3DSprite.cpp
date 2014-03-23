#include "StdAfx.h"
#include "3DSprite.h"

C3DSprite::C3DSprite()
{
	m_pVB = NULL ;
	m_pTexture = NULL ;

	m_nWidth = m_nHeight = 0 ;
	m_fScaleX = m_fScaleY = 1.0f ;
	m_fAngle[0] = m_fAngle[1] = m_fAngle[2] = 0.0f ;
	m_fX = m_fY = 0.0f ;
	m_R = m_G = m_B = 255 ;
	m_nAlpha = 255 ;

	m_tu[0] = 0.0f ; m_tv[0] = 0.0f ;
	m_tu[1] = 1.0f ; m_tv[1] = 0.0f ;
	m_tu[2] = 0.0f ; m_tv[2] = 1.0f ;
	m_tu[3] = 1.0f ; m_tv[3] = 1.0f ;
}
C3DSprite::~C3DSprite()
{
	if(m_pVB!=NULL)
	{
		m_pVB->Release() ;
		m_pVB = NULL ;
	}
	if(m_pTexture!=NULL)
	{
		m_pTexture->Release() ;
		m_pTexture = NULL ;
	}
}

void C3DSprite::SetDevice(LPDIRECT3DDEVICE9 d3dDevice)
{
	m_pd3dDevice = d3dDevice ;
}

bool C3DSprite::Initialize(int Width, int Height)
{
	m_nWidth = Width ;
	m_nHeight = Height ;

	if( FAILED( InitVB() ) )
		return false ;

	return true ;
}

HRESULT C3DSprite::InitVB()
{
	if(m_pVB!=NULL)
	{
		m_pVB->Release() ;
		m_pVB = NULL ;
	}
	if( FAILED( m_pd3dDevice->CreateVertexBuffer( 4*sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &m_pVB, NULL ) ) )
		return E_FAIL ;

	CUSTOMVERTEX* pVertices ;
	if( FAILED( m_pVB->Lock( 0, sizeof(CUSTOMVERTEX), (void**)&pVertices, 0 ) ) )
		return E_FAIL ;

	pVertices[0].x = -(m_nWidth/2.0f) -0.5f ;
	pVertices[0].y = (m_nHeight/2.0f) -0.5f ;
	pVertices[0].z = 0.0f ;
	pVertices[0].color = D3DCOLOR_XRGB(m_R, m_G, m_B) ;
	pVertices[0].tu = m_tu[0];
	pVertices[0].tv = m_tv[0] ;
	pVertices[1].x = (m_nWidth/2.0f) -0.5f ;
	pVertices[1].y = (m_nHeight/2.0f) -0.5f ;
	pVertices[1].z = 0.0f ;
	pVertices[1].color = D3DCOLOR_XRGB(m_R, m_G, m_B) ;
	pVertices[1].tu = m_tu[1] ;
	pVertices[1].tv = m_tv[1] ;
	pVertices[2].x = -(m_nWidth/2.0f) -0.5f ;
	pVertices[2].y = -(m_nHeight/2.0f) -0.5f ;
	pVertices[2].z = 0.0f ;
	pVertices[2].color = D3DCOLOR_XRGB(m_R, m_G, m_B) ;
	pVertices[2].tu = m_tu[2] ;
	pVertices[2].tv = m_tv[2] ;
	pVertices[3].x = (m_nWidth/2.0f) -0.5f ;
	pVertices[3].y = -(m_nHeight/2.0f) -0.5f ;
	pVertices[3].color = D3DCOLOR_XRGB(m_R, m_G, m_B) ;
	pVertices[3].z = 0.0f ;
	pVertices[3].tu = m_tu[3] ;
	pVertices[3].tv = m_tv[3] ;

	m_pVB->Unlock() ;

	return S_OK ;
}

void C3DSprite::SetUV(float u1, float v1, float u2, float v2)
{
	m_tu[0] = m_tu[2] = u1 ; m_tv[0] = m_tv[2] = v1 ;
	m_tu[1] = m_tu[3] = u2 ; m_tv[1] = m_tv[3] = v2 ;

	CUSTOMVERTEX* pVertices ;
	if( FAILED( m_pVB->Lock( 0, sizeof(CUSTOMVERTEX), (void**)&pVertices, 0 ) ) )
		return ;

	for(int i=0; i<4; i++)
	{
		pVertices[i].tu = m_tu[i] ;
		pVertices[i].tv = m_tv[i] ;
	}

	m_pVB->Unlock() ;
}

void C3DSprite::SetUV(int X1, int Y1, int X2, int Y2, int Width, int Height)
{
	float u1, v1 ;
	float u2, v2 ;

	u1 = X1 / Width ; v1 = Y1 / Height ;
	u2 = X2 / Width ; v2 = Y2 / Height ;

	SetUV(u1, v1, u2, v2) ;
}

void C3DSprite::SetXY(float X, float Y)
{
	int x, y ;
	x = (int)(X + 0.5f) ;
	y = (int)(Y + 0.5f) ;

	SetXY(x, y) ;
}

void C3DSprite::SetXY(int X, int Y)
{
	m_fX = (float)X ;
	m_fY = (float)Y ;
}

void C3DSprite::SetXYLt(float X, float Y)
{
	int x, y ;
	x = (int)(X + 0.5f) ;
	y = (int)(Y + 0.5f) ;

	SetXYLt(x, y) ;
}

void C3DSprite::SetXYLt(int x, int y)
{
	m_fX = (float)(x + (m_nWidth/2)) ;
	m_fY = (float)(y + (m_nHeight/2)) ;
}

void C3DSprite::SetRGB(int R, int G, int B)
{
	m_R = R ;
	m_G = G ;
	m_B = B ;

	CUSTOMVERTEX* pVertices ;
	if( FAILED( m_pVB->Lock( 0, sizeof(CUSTOMVERTEX), (void**)&pVertices, 0 ) ) )
		return ;

	for(int i=0; i<4; i++)
		pVertices[i].color = D3DCOLOR_XRGB(m_R, m_G, m_B) ;

	m_pVB->Unlock() ;
}

void C3DSprite::SetAlpha(int Alpha)
{
	m_nAlpha = Alpha ;
}

void C3DSprite::SetAngle(float Angle, eAxis Axis)
{
	m_fAngle[Axis] = (D3DX_PI/180 * Angle) ;
}

void C3DSprite::SetScale(float ScaleX, float ScaleY)
{
	m_fScaleX = ScaleX ;
	m_fScaleY = ScaleY ;
}

void C3DSprite::TexReverse()
{
	SetUV(m_tu[0], m_tv[0], m_tu[1], m_tv[1]) ;
}

void C3DSprite::SetupMatrices()
{
	D3DXMATRIXA16 matWorld, matX, matY, matZ, matT, matS ;
	D3DXMatrixIdentity( &matWorld );
	D3DXMatrixRotationZ(&matX, m_fAngle[AxisX]);
	D3DXMatrixRotationZ(&matY, m_fAngle[AxisY]);
	D3DXMatrixRotationZ(&matZ, m_fAngle[AxisZ]);
	D3DXMatrixTranslation( &matT, m_fX, m_fY, 0.0f );
	D3DXMatrixScaling( &matS, m_fScaleX, m_fScaleY, 1.0f ) ;
	matWorld = matWorld * matX * matY * matZ * matT ;
	m_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
}

void C3DSprite::Render()
{
	/*pD3DDevice->SetTexture(0, m_Textrue.GetTexture());
	pD3DDevice->SetStreamSource(0, m_TextureData[m_nNowCount].m_Sprite.GetVertexBuffer(), 0, sizeof(SVertex));
	pD3DDevice->SetFVF(D3DFVF);
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);*/

	SetupMatrices() ;

	m_pd3dDevice->SetTexture( 0, m_pTexture ) ;

	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE ) ;
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE ) ;
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_TFACTOR ) ;
	m_pd3dDevice->SetRenderState( D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB( m_nAlpha, 0, 0, 0 ) );		// m_Alpha 값이 알파채널*/
	//m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	//m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);	// 정점색에 있는 Alpha 채널을 값으로 알파조정 ex) pVertices[3].color = D3DCOLOR_ARGB(m_Alpha, m_R, m_G, m_B) ;

	//
	//m_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR) ;
	//m_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR) ;
	//

	m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE ) ;	// 알파 블렌딩
	m_pd3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA ) ;
	m_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA ) ;

	m_pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof(CUSTOMVERTEX) );
	m_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
	m_pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2 );

	m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE ) ;	// 알파 블렌딩 끄기
}