#include "TextureManager.h"

TextureManager::TextureManager()
{
}
TextureManager::~TextureManager()
{
	map<string, LPDIRECT3DTEXTURE9>::iterator iter ;
	LPDIRECT3DTEXTURE9 pTexture ;

	for(iter=m_Texture.begin(); iter!=m_Texture.end(); iter++)
		iter->second->Release() ;
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(string texfile, D3DXIMAGE_INFO *pTexInfo)
{
	map<string, LPDIRECT3DTEXTURE9>::iterator iter ;

	iter = m_Texture.find(texfile) ;
	if(iter==m_Texture.end())
	{
		LPDIRECT3DTEXTURE9 pTexture = NULL ;

		if( FAILED( D3DXCreateTextureFromFileEx( pd3dDevice, texfile.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, NULL,
					D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, pTexInfo, NULL, &pTexture ) ) )
		{
			char str[1024] ;
			sprintf(str, "Could not find %s Texture File", texfile.c_str()) ;
			MessageBox(NULL, str, "Texture error", MB_OK) ;

			return NULL ;
		}

		m_Texture[texfile] = pTexture ;
	}

	return m_Texture[texfile] ;
}

/*
map<string, class*> testmap;

testmap.insert(map<string, class*>::value_type(k, v)).first->second = v; //k=key, v=value


�Ǵ�


testmap.insert(pair<string, class*>(k,v));
*/