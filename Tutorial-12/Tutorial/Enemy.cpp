#include "StdAfx.h"
#include "Enemy.h"

// форвард декларация функции выстрела врага
void FireEnemy(D3DXVECTOR2 pos, D3DXVECTOR2 speed);

CEnemy::CEnemy(const std::wstring& strSpriteFile, int iHealth, float fSpeed)
: CLiveObject(D3DXVECTOR2((rand()%700)-350.0f, -400.0f)/*старт. поз.*/, iHealth/*нач. жизни*/)
, m_Sprite(strSpriteFile/*L"Data/enemy-01.png"*/, 0, 0, 64, 64, 32, 32),
m_fSpeed(fSpeed),
fFireTimeOut(0)
{
}

CEnemy::~CEnemy(void)
{
//	delete m_Sprite;
}

void CEnemy::Draw()
{
	// рисуем спрайт
	D3DXVECTOR2 pos = Pos();
	m_Sprite.Draw(pos);
}

void CEnemy::Update( float fDeltaTime )
{
	Move(0, m_fSpeed*fDeltaTime);
	
	// стрельба
	fFireTimeOut -= fDeltaTime;
	if (fFireTimeOut<0 && (rand()&127)==127)
	{
		FireEnemy(Pos(), D3DXVECTOR2(0, m_fSpeed+100));
		fFireTimeOut = 1.0f; // не сможем стрелять ещё секунду
	}
}
