#include "StdAfx.h"
#include "Bullet.h"

CBullet::CBullet( D3DXVECTOR2 pos, D3DXVECTOR2 speed, const std::wstring& strTexFile)
: m_pos(pos), m_speed(speed), m_iDamage(30),
m_Sprite(strTexFile, 0, 0, 0, 0, 8, 8)
{
}

CBullet::~CBullet(void)
{
}

D3DXVECTOR2 CBullet::Pos() const
{
	return m_pos;
}

void CBullet::Update( float fDeltaTime )
{
	m_pos += m_speed*fDeltaTime;
}

bool CBullet::TestCollision( const CLiveObject& obj ) const
{
	// вектор от одного объекта до другого
	D3DXVECTOR2 dist = obj.Pos() - Pos();

	// если расстояние меньше или равно сумме радиусов
	if (obj.Radius()>=D3DXVec2Length(&dist))
		return true; // столкновение

	return false; // иначе нет
}

int CBullet::Damage() const
{
	return m_iDamage;
}

void CBullet::Draw() const
{
	// рисуем спрайт
	D3DXVECTOR2 pos = Pos();
	m_Sprite.Draw(pos);
}
