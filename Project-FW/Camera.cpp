#include "Camera.h"

LPDIRECT3DDEVICE9 CCamera::pd3dDevice = NULL ;
float CCamera::WinWidth = 0.0f ;
float CCamera::WinHeight = 0.0f ;

CCamera::CCamera() : m_fX(0.0f),
					 m_fY(0.0f)
{
}
CCamera::~CCamera()
{
}

void CCamera::SetXY(float x, float y)
{
	m_fX = x ;
	m_fY = y ;
}

void CCamera::Run()
{
	D3DXMATRIXA16 matWorld ;
	D3DXMatrixIdentity( &matWorld );
	pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld ) ;

	D3DXVECTOR3 vEyePt( m_fX, m_fY, -10.0f );	// 카메라의 위치
	D3DXVECTOR3 vLookatPt( m_fX, m_fY, 0.0f );	// 카메라의 시선
	D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );	// 상방벡터 (정수리)
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
	pd3dDevice->SetTransform( D3DTS_VIEW, &matView ) ;

	D3DXMATRIXA16 matProj;
	D3DXMatrixOrthoLH(&matProj, WinWidth, WinHeight, 1.0f, 1000.0f) ;
	pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}