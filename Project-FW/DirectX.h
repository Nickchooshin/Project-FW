#pragma once

#include <d3dx9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#pragma warning( disable : 4995 )
#include <strsafe.h>
#include <dinput.h>

struct CUSTOMVERTEX
{
	FLOAT		x, y, z ;	// The position
	D3DCOLOR	color ;		// The color
	FLOAT		tu, tv ;	// The texture coordinates
} ;

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)