#pragma once
#include "Sprite.h"
#include <vector>

class CSpriteAnimation
{
	std::vector<CSprite> m_vecSprites;
	std::vector<float> m_vecTimes;

public:
	CSpriteAnimation(void);
	~CSpriteAnimation(void);

	//! Добавление спрайта в анимацию
	void Add(const std::wstring& strTexFileName=L"",
		int x=0, int y=0, int sx=0, int sy=0,
		int pivotx=0, int pivoty=0, float fTimeToShow=.1f);

	//! Отрисовка анимации (указываем необходимое время)
	void Draw(D3DXVECTOR2 pos, float fTime, float fSize);
	//! Общая длина анимации
	float Length() const;
};
