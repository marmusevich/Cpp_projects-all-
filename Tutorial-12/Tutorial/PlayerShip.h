#pragma once
#include "liveobject.h"
#include "Graphics.h"

class CPlayerShip :
	public CLiveObject
{
	//! Это спрайт игрока
	CSprite m_Sprite;

public:
	CPlayerShip(void);
	~CPlayerShip(void);
	//! функция отрисовки
	void Draw();
	//! Функция движения (управления) корабля
	void Scroll(float dx, float dy);
};
