#include "D3dSystem.h"

CD3dSystem::CD3dSystem()
{
	g_pD3d = NULL ;
	g_pd3dDevice = NULL ;
}
CD3dSystem::~CD3dSystem()
{
	if( g_pd3dDevice != NULL )
		g_pd3dDevice->Release();

	if( g_pD3d != NULL )
		g_pD3d->Release();
}

HRESULT CD3dSystem::InitD3d(HINSTANCE hInst, HWND hWnd, int nWidth, int nHeight, char* ErrorStr)
{
	if( NULL == ( g_pD3d = Direct3DCreate9( D3D_SDK_VERSION ) ) )
	{
		strcpy(ErrorStr, "DirectX를 초기화 하지 못했습니다.") ;
		return E_FAIL;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.BackBufferWidth = nWidth ;	// 백버퍼 넓이
	d3dpp.BackBufferHeight = nHeight ;	// 백버퍼 높이
	d3dpp.Windowed = TRUE ;	// 창모드 유무
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD ;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8 ;	// 백버퍼 포맷	// D3DFMT_UNKNOWN
	d3dpp.BackBufferCount = 1 ;	// 백버퍼 개수
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE ;	// 멀티샘플링 사용 유무
	d3dpp.MultiSampleQuality = 0 ;	// 멀티샘플링(1x 2x 4x 8x ...)

	if( FAILED( g_pD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_MIXED_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice ) ) )
	{
		//if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice ) ) )
		{
			if( FAILED( g_pD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice ) ) )
			{
				strcpy(ErrorStr, "DirectX 디바이스를 생성하지 못했습니다.") ;
				return E_FAIL;
			}
		}
	}

	m_hInst = hInst ;

	SetRenderState() ;

	return S_OK;
}

LPDIRECT3DDEVICE9 CD3dSystem::GetDevice()
{
	return g_pd3dDevice ;
}

void CD3dSystem::SetRenderState()
{
	g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	g_pd3dDevice->SetRenderState( D3DRS_DITHERENABLE, FALSE ); // 색 혼합법
	g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );	// 광원
	g_pd3dDevice->SetRenderState( D3DRS_SPECULARENABLE, FALSE ); // 재질 광원

	g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE ) ;	// Z버퍼
	g_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE ) ;	// Z버퍼 2D 관련??

	g_pd3dDevice->SetRenderState( D3DRS_ANTIALIASEDLINEENABLE, FALSE ) ;	// 안티앨리어싱 렌더링
}