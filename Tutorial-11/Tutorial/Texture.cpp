#include "StdAfx.h"
#include "Texture.h"
#include <d3dx9.h>

CTexture::CTexture(void)
: m_pTex(NULL)
{
	ZeroMemory(&m_ddesc, sizeof(D3DSURFACE_DESC));
}

CTexture::~CTexture(void)
{
	Release();
}

void CTexture::SetTexture( LPDIRECT3DTEXTURE9 pTex )
{
	Release();
	m_pTex = pTex;
	if (m_pTex)
	{
		m_pTex->GetLevelDesc(0, &m_ddesc);
	}
}

void CTexture::SetSrc( const std::wstring& src )
{
	m_strTexSrc = src;
}

std::wstring CTexture::GetSrc() const
{
	return m_strTexSrc;
}

LPDIRECT3DTEXTURE9 CTexture::GetTexture() const
{
	return m_pTex;
}

HRESULT CTexture::Release()
{
	if (m_pTex)
		m_pTex->Release();
	m_pTex = NULL;

	return D3D_OK;
}

HRESULT CTexture::Reload( LPDIRECT3DDEVICE9 pDev )
{
	return D3DXCreateTextureFromFile(pDev, GetSrc().c_str(), &m_pTex);
}

UINT CTexture::Width() const
{
	return m_ddesc.Width;
}

UINT CTexture::Height() const
{
	return m_ddesc.Height;
}
