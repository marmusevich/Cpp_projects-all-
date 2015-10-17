#include "StdAfx.h"
#include "Sprite.h"
#include "Graphics.h"

CSprite::CSprite(const std::wstring& strTexFileName,
				 int x, int y, int sx, int sy,
				 int pivotx, int pivoty)
{
	m_pTexture = CTexturePtr(NULL);
	
	if (strTexFileName.length()!=0)
		m_pTexture = Graphics::get().LoadTexture(strTexFileName);
	
	ZeroMemory(m_v, sizeof(VertPosTc)*4);
	// если текстура не указана или не была загружена
	if (m_pTexture != NULL)
	{
		int width = m_pTexture->Width();
		int height = m_pTexture->Height();
		if (width==0 || height==0)
			return; // спрайт "пустой"
		if (sx==0)
			sx = width-x;
		if (sy==0)
			sy = height-y;
		
		// считаем размеры спрайта
		float x1 = float(x-pivotx);
		float x2 = float(x-pivotx+sx);

		float y1 = float(y-pivoty);
		float y2 = float(y-pivoty+sy);

		m_v[0] = VertPosTc(D3DXVECTOR3(x1, y1, 0), 
			D3DXVECTOR2(float(x)/width, float(y)/height));
		
		m_v[1] = VertPosTc(D3DXVECTOR3(x2, y1, 0), 
			D3DXVECTOR2(float(x+sx)/width, float(y)/height));
		
		m_v[2] = VertPosTc(D3DXVECTOR3(x1, y2, 0), 
			D3DXVECTOR2(float(x)/width, float(y+sy)/height));
		
		m_v[3] = VertPosTc(D3DXVECTOR3(x2, y2, 0), 
			D3DXVECTOR2(float(x+sx)/width, float(y+sy)/height));
	};
	m_rect = CRect(CPoint(x, y), CPoint(x+sx, y+sy));
	m_pivot = CPoint(pivotx, pivoty);
}

CSprite::~CSprite(void)
{
}

CRect CSprite::TexRect() const
{
	return m_rect;
}

CPoint CSprite::TexPivot() const
{
	return m_pivot;
}

void CSprite::Draw( D3DXVECTOR2 pos, float size ) const
{
	Graphics::get().SetTexture(0, m_pTexture);
	
	VertPosTc verts[4];
	memcpy(verts, m_v, sizeof(VertPosTc)*4);
	for (int i=0; i<4; i++)
		verts[i].m_pos = verts[i].m_pos*size + D3DXVECTOR3(pos.x, pos.y, 0);
	Graphics::get().SetFVF(D3DFVF_XYZ|D3DFVF_TEX1);
	Graphics::get().DPUP(D3DPT_TRIANGLESTRIP, 2, verts, sizeof(VertPosTc));
}
