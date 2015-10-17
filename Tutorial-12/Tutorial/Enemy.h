#pragma once
#include "liveobject.h"
#include "Graphics.h"

class CEnemy :
	public CLiveObject
{
	//! ��� ������ �����
	CSprite m_Sprite;

	//! �������� �����
	float m_fSpeed;
	//! ������ ��������. ����� �� ������ ���� ����� ��������.
	float fFireTimeOut;

public:
	CEnemy(const std::wstring& strSpriteFile=L"", int iHealth=50, float fSpeed=100);
	virtual ~CEnemy(void);
	//! ������� ���������
	void Draw();
	//! ������� �������
	void Update(float fDeltaTime);
};
