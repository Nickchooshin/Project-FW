#include "Sprite.h"
#include <stdio.h>

LPDIRECT3DDEVICE9 CSprite::pd3dDevice = NULL ;

CSprite::CSprite() : m_pVB(NULL),
					 m_pIB(NULL),
					 m_pTexture(NULL),
					 m_fWidth(0.0f), m_fHeight(0.0f),
					 m_fScaleX(1.0f), m_fScaleY(1.0f),
					 m_fX(0.0f), m_fY(0.0f),
					 m_R(255), m_G(255), m_B(255),
					 m_nAlpha(255)
{
	for(int i=0; i<3; i++)
		m_fAngle[i] = 0.0f ;

	m_tu[0] = 0.0f ;	m_tv[0] = 0.0f ;
	m_tu[1] = 1.0f ;	m_tv[1] = 0.0f ;
	m_tu[2] = 0.0f ;	m_tv[2] = 1.0f ;
	m_tu[3] = 1.0f ;	m_tv[3] = 1.0f ;
}
CSprite::~CSprite()
{
	if(m_pVB!=NULL)
		m_pVB->Release() ;

	if(m_pIB!=NULL)
		m_pIB->Release() ;

	if(m_pTexture!=NULL)
		m_pTexture->Release() ;
}

bool CSprite::Init(float Width, float Height, char *texfile)
{
	m_fWidth = Width ;
	m_fHeight = Height ;

	if(FAILED(InitVB()))
		return false ;
	if(SetTexture(texfile))
		return false ;

	return true ;
}

void CSprite::Render()
{
	SetupMatrices() ;

	pd3dDevice->SetTexture( 0, m_pTexture ) ;

	pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
	pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_TFACTOR );
	pd3dDevice->SetRenderState( D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB( m_nAlpha, 0, 0, 0 ) );		// m_Alpha 값이 알파채널
	//g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	//g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);	// 정점색에 있는 Alpha 채널을 값으로 알파조정 ex) pVertices[3].color = D3DCOLOR_ARGB(m_Alpha, m_R, m_G, m_B) ;

	//
	//g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR) ;
	//g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR) ;
	//

	pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE ) ; // 알파 블렌딩 ON
	pd3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA ) ;
	pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA ) ;

	pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof(SPRITE_VERTEX) );
	pd3dDevice->SetFVF( D3DFVF_SPRITE_VERTEX );
	pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2) ;

	pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE ) ; // 알파 블렌딩 OFF

	//pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof(CUSTOMVERTEX) );
	//pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
	//pd3dDevice->SetIndices( m_pIB );
	//pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2 );
}

HRESULT CSprite::InitVB()
{
	if( FAILED( pd3dDevice->CreateVertexBuffer( 4*sizeof(SPRITE_VERTEX), 0, D3DFVF_SPRITE_VERTEX, D3DPOOL_DEFAULT, &m_pVB, NULL ) ) )
	{
		return E_FAIL;
	}

	SPRITE_VERTEX* pVertices;
	if( FAILED( m_pVB->Lock( 0, sizeof(SPRITE_VERTEX), (void**)&pVertices, 0 ) ) )
		return E_FAIL;

	float Width_Half = m_fWidth / 2.0f ;
	float Height_Half = m_fHeight / 2.0f ;

	pVertices[0].x = -(Width_Half) - 0.5f ;
	pVertices[0].y = Height_Half - 0.5f ;
	pVertices[0].z = 0.0f ;
	pVertices[0].color = D3DCOLOR_XRGB(m_R, m_G, m_B) ;
	pVertices[0].tu = m_tu[0];
	pVertices[0].tv = m_tv[0] ;

	pVertices[1].x = Width_Half - 0.5f ;
	pVertices[1].y = Height_Half - 0.5f ;
	pVertices[1].z = 0.0f ;
	pVertices[1].color = D3DCOLOR_XRGB(m_R, m_G, m_B) ;
	pVertices[1].tu = m_tu[1] ;
	pVertices[1].tv = m_tv[1] ;

	pVertices[2].x = -(Width_Half) - 0.5f ;
	pVertices[2].y = -(Height_Half) - 0.5f ;
	pVertices[2].z = 0.0f ;
	pVertices[2].color = D3DCOLOR_XRGB(m_R, m_G, m_B) ;
	pVertices[2].tu = m_tu[2] ;
	pVertices[2].tv = m_tv[2] ;

	pVertices[3].x = (Width_Half) - 0.5f ;
	pVertices[3].y = -(Height_Half) - 0.5f ;
	pVertices[3].color = D3DCOLOR_XRGB(m_R, m_G, m_B) ;
	pVertices[3].z = 0.0f ;
	pVertices[3].tu = m_tu[3] ;
	pVertices[3].tv = m_tv[3] ;

	m_pVB->Unlock();

	return true ;
}

bool CSprite::SetTexture(char *texfile)
{
	if( FAILED( D3DXCreateTextureFromFileEx( pd3dDevice, texfile, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, NULL,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE,D3DX_FILTER_NONE, NULL, NULL, NULL, &m_pTexture ) ) )
	{
		char str[1024] ;
		sprintf(str, "Could not find %s Texture File", texfile) ;
		MessageBox(NULL, str, "Textures error", MB_OK) ;
		
		return false ;
	}

	return true ;
}

void CSprite::SetupMatrices()
{
	D3DXMATRIXA16 matWorld, matX, matY, matZ, matT, matS ;
	D3DXMatrixIdentity( &matWorld );
	D3DXMatrixRotationZ(&matX, m_fAngle[0]);
	D3DXMatrixRotationZ(&matY, m_fAngle[1]);
	D3DXMatrixRotationZ(&matZ, m_fAngle[2]);
	D3DXMatrixTranslation( &matT, m_fX, m_fY, 0.0f );
	D3DXMatrixScaling( &matS, m_fScaleX, m_fScaleY, 0.0f ) ;

	matWorld = matWorld * matX * matY * matZ * matT ;
	pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
}