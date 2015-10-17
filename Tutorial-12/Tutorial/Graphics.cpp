#include "StdAfx.h"
#include "Graphics.h"
#include "VertexTypes.h"

Graphics::Graphics()
{
	m_pD3D = NULL;
	m_pd3dDevice = NULL;
	ZeroMemory(&m_d3dpp, sizeof(D3DPRESENT_PARAMETERS)); // обнулим
}

Graphics::~Graphics( void )
{

}

bool Graphics::Init(HWND hRenderWnd, int width, int height)
{
	// сначала проицициализируем сам DirectX 9
	m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
	if (m_pD3D==NULL)
		return false;

	m_d3dpp.BackBufferWidth = width; // указываем ширину и
	m_d3dpp.BackBufferHeight = height; // высоту области рендера
	m_d3dpp.BackBufferCount = 1; // один внеэкранный буфер
	m_d3dpp.Windowed = TRUE; // рендер в окне, а не в полный экран
	m_d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;// D3DFMT_UNKNOWN; // формат выберет сам DX
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; // так лучше делать всегда
	m_d3dpp.EnableAutoDepthStencil = TRUE; // нам нужен Z-буфер
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8; // формат Z-буфера
	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	// и теперь создадим сам девайс
	HRESULT hr = m_pD3D->CreateDevice( D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, hRenderWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&m_d3dpp, &m_pd3dDevice );
	if (FAILED(hr))
		return FALSE;

	return TRUE;
}


void Graphics::Cleanup()
{
	// освобождаем текстуры
	vecTextures::iterator itr = m_vecTextures.begin();
	while(itr!=m_vecTextures.end())
	{
		(*itr)->Release();
		itr++;
	}
	m_vecTextures.clear();
	
	// освобождаем шейдеры
	vecShaders::iterator itr2 = m_vecShaders.begin();
	while(itr2!=m_vecShaders.end())
	{
		(*itr2)->Release();
		itr2++;
	}
	m_vecShaders.clear();

	if (m_pd3dDevice)
	{
		m_pd3dDevice->Release();
		m_pd3dDevice = NULL;
	}
	if (m_pD3D)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

bool Graphics::StartRender(D3DCOLOR bgColor)
{
	if (FAILED(m_pd3dDevice->BeginScene())) // начинаем рисовать
		return false;

	 // очистка экрана
	if (FAILED(m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET|
		D3DCLEAR_STENCIL| D3DCLEAR_ZBUFFER, bgColor, 1, 0)))
		return false;

	return true;
}

HRESULT Graphics::SetFVF( DWORD FVF )
{
	return m_pd3dDevice->SetFVF(FVF);
}

HRESULT Graphics::SetTexture( DWORD stage, CTexturePtr pTex )
{
	if (pTex)
		return m_pd3dDevice->SetTexture(stage, pTex->GetTexture());
	
	return m_pd3dDevice->SetTexture(stage, NULL);
}

bool Graphics::EndRender()
{
	m_pd3dDevice->EndScene(); // закончили рисовать

	// копируем на экран
	HRESULT hr = m_pd3dDevice->Present(NULL, NULL, NULL, NULL);
	if (FAILED(hr)/*==D3DERR_DEVICELOST*/)
		Reset();
	
	if (FAILED(hr))
		return false;
	
	return true;
}

LPDIRECT3DDEVICE9 Graphics::GetDevice()
{
	return m_pd3dDevice;
}

CTexturePtr Graphics::LoadTexture(const std::wstring& szFileName )
{
	// ищем текстуру среди уже загруженных
	vecTextures::iterator itr = m_vecTextures.begin();
	while(itr!=m_vecTextures.end())
	{
		if ( (*itr)->GetSrc().compare(szFileName)==0 )
			return *itr; // нашли
		itr++;
	}
	
	// не нашли, пробуем загрузить текстуру
	LPDIRECT3DTEXTURE9 pTex = NULL;
	if (FAILED(D3DXCreateTextureFromFile(m_pd3dDevice, szFileName.c_str(), &pTex)))
		return NULL;
	
	// создаём наш собственный обект текстуры
	CTexturePtr pTexPtr = new CTexture();
	pTexPtr->SetSrc(szFileName);
	pTexPtr->SetTexture(pTex);

	m_vecTextures.push_back(pTexPtr);
	
	return pTexPtr; // возвращаем (указатель на) новую текстуру
}

HRESULT Graphics::SetRenderState( D3DRENDERSTATETYPE State, DWORD Value )
{
	return m_pd3dDevice->SetRenderState(State, Value);
}

HRESULT Graphics::SetSamplerState( DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value )
{
	return m_pd3dDevice->SetSamplerState(Sampler, Type, Value);
}

HRESULT Graphics::DPUP( D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride )
{
	return m_pd3dDevice->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT Graphics::SetPixelShader( CShaderPtr shader )
{
	return m_pd3dDevice->SetPixelShader(shader->GetPixelShader());
}

HRESULT Graphics::SetVertexShader( CShaderPtr shader )
{
	return m_pd3dDevice->SetVertexShader(shader->GetVertexShader());
}

CShaderPtr Graphics::LoadShader( const std::string& strFileName, const std::string& strFuncName, const std::string& profile )
{
	CShaderPtr pShader = new CShader;
	if (FAILED(pShader->Load(strFileName, strFuncName, profile)))
		return NULL;

	LPD3DXBUFFER pShaderBuff = pShader->GetCompileBuffer();
	if (pShader->IsPS())
	{
		// создаём пиксельный шейдер
		LPDIRECT3DPIXELSHADER9 pPixelShader;
		m_pd3dDevice->CreatePixelShader(( DWORD* )pShaderBuff->GetBufferPointer(), &pPixelShader);
		pShader->SetHardwareShader(m_pd3dDevice, pPixelShader);
	}
	else
	{
		// создаём вертексный шейдер
		LPDIRECT3DVERTEXSHADER9 pVertexShader;
		m_pd3dDevice->CreateVertexShader(( DWORD* )pShaderBuff->GetBufferPointer(), &pVertexShader);
		pShader->SetHardwareShader(m_pd3dDevice, pVertexShader);
	}
	
	m_vecShaders.push_back(pShader);
	return pShader;
}

HRESULT Graphics::Reset()
{
	// освобождаем текстуры
	vecTextures::iterator itr = m_vecTextures.begin();
	while(itr!=m_vecTextures.end())
	{
		(*itr)->Release();
		itr++;
	}

	// шейдеры освобождать не надо - при лостдевайс они сохраняются

	// сбрасываем девайс
	HRESULT hr = m_pd3dDevice->Reset(&m_d3dpp);
	if (FAILED(hr))
		return hr;

	// загружаем текстуры обратно
	itr = m_vecTextures.begin();
	while(itr!=m_vecTextures.end())
	{
		(*itr)->Reload(m_pd3dDevice);
		itr++;
	}

	return D3D_OK;
}
