#include "StdAfx.h"
#include "LiveObject.h"

CLiveObject::CLiveObject(D3DXVECTOR2 pos, int iHealth)
: m_vPos(pos),
m_iHealth(iHealth),
m_fRadius(28)
{
}

CLiveObject::~CLiveObject(void)
{
}

void CLiveObject::DoDamage( const int iDamage )
{
	m_iHealth -= iDamage; // ��������� �����
}

bool CLiveObject::IsAlive() const
{
	return ( m_iHealth > 0 ); // ������ ������ ����?
}

void CLiveObject::Move( float dx, float dy )
{
	Move(D3DXVECTOR2(dx, dy));
}

void CLiveObject::Move( const D3DXVECTOR2 delta )
{
	m_vPos += delta;
}

void CLiveObject::MoveTo( const D3DXVECTOR2 pos )
{
	m_vPos = pos;
}

D3DXVECTOR2 CLiveObject::Pos() const
{
	return m_vPos;
}

float CLiveObject::Radius() const
{
	return m_fRadius;
}

bool CLiveObject::TestCollision( const CLiveObject& obj ) const
{
	 // ������ �� ������ ������� �� �������
	D3DXVECTOR2 dist = obj.Pos()-Pos();

	// ���� ���������� ������ ��� ����� ����� ��������
	if (obj.Radius()+Radius()>=D3DXVec2Length(&dist))
		return true; // ������������
	
	return false; // ����� ���
}

void CLiveObject::SetHealth( int iHealth )
{
	m_iHealth = iHealth;
}

int CLiveObject::Health() const
{
	return m_iHealth;
}
