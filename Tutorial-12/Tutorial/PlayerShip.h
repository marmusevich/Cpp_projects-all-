#pragma once
#include "liveobject.h"
#include "Graphics.h"

class CPlayerShip :
	public CLiveObject
{
	//! ��� ������ ������
	CSprite m_Sprite;

public:
	CPlayerShip(void);
	~CPlayerShip(void);
	//! ������� ���������
	void Draw();
	//! ������� �������� (����������) �������
	void Scroll(float dx, float dy);
};
