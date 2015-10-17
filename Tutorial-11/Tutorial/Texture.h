#pragma once
#include <d3d9.h>
#include <string>

class Graphics;

class CTexture
{
	// ����� Graphics ����� ����� ������ � protected-������
	friend class Graphics;

private:
	//! ���� ��������
	std::wstring m_strTexSrc;
	//! ��� ���� ��������
	LPDIRECT3DTEXTURE9 m_pTex;

	D3DSURFACE_DESC m_ddesc;

protected:
	// ������ ������ ��� ������ Graphics
	CTexture(void);
	~CTexture(void);
	HRESULT Release();
	void SetTexture(LPDIRECT3DTEXTURE9 pTex);
	void SetSrc(const std::wstring& src);
	LPDIRECT3DTEXTURE9 GetTexture() const;
	HRESULT Reload(LPDIRECT3DDEVICE9 pDev);

public:
	std::wstring GetSrc() const;
	UINT Width() const;
	UINT Height() const;
};

typedef CTexture* CTexturePtr; // ��� ���������� �� ��������