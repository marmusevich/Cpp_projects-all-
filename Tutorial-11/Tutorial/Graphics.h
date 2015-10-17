#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

#include "singleton.h"
#include "Texture.h"
#include "Shader.h"
#include "Sprite.h"

class Graphics : public singleton<Graphics>
{
	friend class singleton<Graphics>;
private:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pd3dDevice;

	// структкура с параметрами девайса
	D3DPRESENT_PARAMETERS m_d3dpp;

	typedef std::vector<CTexturePtr> vecTextures;
	vecTextures m_vecTextures;

// 	typedef std::vector<CSpritePtr> vecSprites;
// 	vecSprites m_vecSprites;

	typedef std::vector<CShaderPtr> vecShaders;
	vecShaders m_vecShaders;

protected:
	Graphics(void);
	~Graphics(void);
	LPDIRECT3DDEVICE9 GetDevice();

public:
	bool Init(HWND hRenderWnd, int width, int height);
	void Cleanup();
	HRESULT Reset();
	bool StartRender(D3DCOLOR bgColor=0xff808080);
	
	HRESULT SetFVF(DWORD FVF);
	HRESULT SetPixelShader(CShaderPtr shader);
	HRESULT SetVertexShader(CShaderPtr shader);
	HRESULT SetRenderState(D3DRENDERSTATETYPE State, DWORD Value);
	HRESULT SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value);
	HRESULT SetTexture(DWORD stage, CTexturePtr pTex);
	HRESULT DPUP( D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride);
	//! Отрисовка спрайта в заданных координатах и с заданными размерами

	bool EndRender();
	CTexturePtr LoadTexture(const std::wstring& szFileName);
	CShaderPtr LoadShader( const std::string& strFileName, const std::string& strFuncName, const std::string& profile);
};
