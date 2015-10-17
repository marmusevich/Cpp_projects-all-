#pragma once
#include "Graphics.h"

class CStarField
{
	//! Это спрайт звезды
	CSpritePtr m_Sprite;
	//! счётчик времени для рождения новых звёзд
	float m_fDT;

	struct Star // одна звезда
	{
		D3DXVECTOR2 m_pos; // позиция на экране
		int m_size; // размер
		Star(D3DXVECTOR2 pos=D3DXVECTOR2(0,0), int size=8);
	};
	std::vector<Star> vecStars;
public:
	CStarField(void);
	~CStarField(void);
	void Update(float fDeltaTime);
	void Draw();
};
