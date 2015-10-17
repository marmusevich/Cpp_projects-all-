#pragma once
#include "Graphics.h"
#include "LiveObject.h"

class CBullet
{
	int m_iDamage; // ����
	D3DXVECTOR2 m_pos; // ������� �������
	D3DXVECTOR2 m_speed; // ������� ��������

	//! C����� �������
	CSprite m_Sprite;

public:
	CBullet(D3DXVECTOR2 pos=D3DXVECTOR2(0,0),
		D3DXVECTOR2 speed=D3DXVECTOR2(0,0), const std::wstring& strTexFile=L"Data/bullet.dds");
	virtual ~CBullet(void);
	D3DXVECTOR2 Pos() const;
	void Draw() const;
	int Damage() const;
	void Update(float fDeltaTime); // ������ �������
	bool TestCollision(const CLiveObject& obj) const;
};
