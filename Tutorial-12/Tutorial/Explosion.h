#pragma once
#include "SpriteAnimation.h"

class CExplosion
{
	float m_fPlayTime;
	CSpriteAnimation m_anim;
	D3DXVECTOR2 m_pos;

public:
	CExplosion(D3DXVECTOR2 pos);
	~CExplosion(void);
	//! Апдейт взрыва
	void Update(float fDeltaTime);
	//! Отрисовка
	void Draw();
	//! Вызрыв закончен?
	bool IsFinished() const;
};
