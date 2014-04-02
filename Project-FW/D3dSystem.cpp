#include "D3dSystem.h"

//
#include "InputDevice.h"

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
		strcpy(ErrorStr, "DirectX�� �ʱ�ȭ ���� ���߽��ϴ�.") ;
		return E_FAIL;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.BackBufferWidth = nWidth ;	// ����� ����
	d3dpp.BackBufferHeight = nHeight ;	// ����� ����
	d3dpp.Windowed = TRUE ;	// â��� ����
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD ;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8 ;	// ����� ����	// D3DFMT_UNKNOWN
	d3dpp.BackBufferCount = 1 ;	// ����� ����
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE ;	// ��Ƽ���ø� ��� ����
	d3dpp.MultiSampleQuality = 0 ;	// ��Ƽ���ø�(1x 2x 4x 8x ...)

	if( FAILED( g_pD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_MIXED_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice ) ) )
	{
		//if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice ) ) )
		{
			if( FAILED( g_pD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice ) ) )
			{
				strcpy(ErrorStr, "DirectX ����̽��� �������� ���߽��ϴ�.") ;
				return E_FAIL;
			}
		}
	}

	m_hInst = hInst ;

	g_InputDevice->InitDevice(hInst, hWnd) ;

	SetRenderState() ;

	return S_OK;
}

LPDIRECT3DDEVICE9 CD3dSystem::GetDevice()
{
	return g_pd3dDevice ;
}

bool CD3dSystem::BeginScene()
{
	g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0 ); // D3DCOLOR_XRGB

	return SUCCEEDED( g_pd3dDevice->BeginScene() ) ;
}

void CD3dSystem::EndScene()
{
	g_pd3dDevice->EndScene();

	g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}

void CD3dSystem::SetRenderState()
{
	g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	g_pd3dDevice->SetRenderState( D3DRS_DITHERENABLE, FALSE ); // �� ȥ�չ�
	g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );	// ����
	g_pd3dDevice->SetRenderState( D3DRS_SPECULARENABLE, FALSE ); // ���� ����

	g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE ) ;	// Z����
	g_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE ) ;	// Z���� 2D ����??

	g_pd3dDevice->SetRenderState( D3DRS_ANTIALIASEDLINEENABLE, FALSE ) ;	// ��Ƽ�ٸ���� ������
}