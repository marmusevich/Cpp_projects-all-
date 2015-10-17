#include "StdAfx.h"
#include "SpriteAnimation.h"

CSpriteAnimation::CSpriteAnimation(void)
{
}

CSpriteAnimation::~CSpriteAnimation(void)
{
}

void CSpriteAnimation::Add( const std::wstring& strTexFileName/*=L""*/, int x/*=0*/, int y/*=0*/, int sx/*=0*/, int sy/*=0*/, int pivotx/*=0*/, int pivoty/*=0*/, float fTimeToShow/*=.1f*/ )
{
	m_vecSprites.push_back(CSprite(strTexFileName, x, y, sx, sy, pivotx, pivoty));
	m_vecTimes.push_back(fTimeToShow);
}

void CSpriteAnimation::Draw(D3DXVECTOR2 pos, float fTime, float fSize)
{
	size_t index = 0; // ищем индекс нужного спрайта
	for (; index<m_vecTimes.size(); index++)
	{
		if (fTime>m_vecTimes[index])
			fTime -= m_vecTimes[index];
		else
			break;
	}
	
	if (index==m_vecTimes.size())
		index = m_vecTimes.size()-1;

	// рисуем спрайт
	m_vecSprites[index].Draw(pos, fSize);
}

float CSpriteAnimation::Length() const
{
	float fTime = 0.0f;
	for (size_t index = 0; index<m_vecTimes.size(); index++)
		fTime += m_vecTimes[index];
	return fTime;
}
