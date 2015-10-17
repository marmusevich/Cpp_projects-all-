#pragma once
#include "liveobject.h"
#include "Graphics.h"

class CEnemy :
	public CLiveObject
{
	//! ��� ������ �����
	CSprite m_Sprite;

	//! ������ ��������. ����� �� ������ ���� ����� ��������.
	float fFireTimeOut;

public:
	CEnemy(void);
	virtual ~CEnemy(void);
	//! ������� ���������
	void Draw();
	//! ������� �������
	void Update(float fDeltaTime);
};
