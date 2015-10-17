#pragma once
#include "Texture.h"
#include "VertexTypes.h"
#include "Utils.h"

class Graphics;
struct VertPosTc;

class CSprite
{
	// класс Graphics будет иметь доступ к protected-членам
	friend class Graphics;

	// текстура спрайта
	CTexturePtr m_pTexture;
	VertPosTc m_v[4]; //вертексы спрайта

	CRect m_rect;
	CPoint m_pivot;

public:
	CSprite(const std::wstring& strTexFileName=L"",
		int x=0, int y=0, int sx=0, int sy=0,
		int pivotx=0, int pivoty=0);
	~CSprite(void);

	CRect TexRect() const ;
	CPoint TexPivot() const ;
	void Draw(D3DXVECTOR2 pos, float size=1.0f) const;
};

typedef CSprite* CSpritePtr; // тип указателей на спрайт