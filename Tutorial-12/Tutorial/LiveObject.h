#pragma once
#include <d3dx9.h>

//! ����� ������ �������
class CLiveObject
{
private: // ��������� ������
	int m_iHealth; // ���������� ������
	D3DXVECTOR2 m_vPos; // ������� �� ������
	float m_fRadius; // ������ ��� ������������

protected: // ���������� ������, ������ ������ �����������
	void Move(float dx, float dy); // �������� �� dx, dy
	void Move(const D3DXVECTOR2 delta); // �������� �� delta
	void MoveTo(const D3DXVECTOR2 pos); // ������ ����� �������

public: // ��������� ������ ������
	CLiveObject(D3DXVECTOR2 pos, int iHealth=100);
	virtual ~CLiveObject(void); // ����. ����������
	void SetHealth(int iHealth);
	int Health() const;
	void DoDamage(const int iDamage); // ������� �����������
	bool IsAlive() const; // ��� ��� (������ ������ 0) ?
	D3DXVECTOR2 Pos() const; // ������� �������
	float Radius() const; // ������ �������
	//! ������� ��� �������� ������������ � ������ CLiveObject
	bool TestCollision(const CLiveObject& obj) const;
};
