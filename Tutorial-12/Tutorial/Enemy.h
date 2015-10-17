#pragma once
#include "liveobject.h"
#include "Graphics.h"

class CEnemy :
	public CLiveObject
{
	//! Это спрайт врага
	CSprite m_Sprite;

	//! Скорость полёта
	float m_fSpeed;
	//! Таймер стрельбы. Когда он меньше нуля можно стрелять.
	float fFireTimeOut;

public:
	CEnemy(const std::wstring& strSpriteFile=L"", int iHealth=50, float fSpeed=100);
	virtual ~CEnemy(void);
	//! функция отрисовки
	void Draw();
	//! Функция апдейта
	void Update(float fDeltaTime);
};
