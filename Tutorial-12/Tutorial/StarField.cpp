#include "StdAfx.h"
#include "StarField.h"

CStarField::CStarField(void)
{
	m_fDT = .0f;
	m_Sprite = new CSprite(L"Data/star.dds");
}

CStarField::~CStarField(void)
{
	delete m_Sprite;
}

void CStarField::Update( float fDeltaTime )
{
	// ������� �����
	// ��� ������ ������ - ��� ������� ��� ��������
	for (size_t i=0; i<vecStars.size(); i++)
	{
		vecStars[i].m_pos.y += vecStars[i].m_size*fDeltaTime*50;
		if (vecStars[i].m_pos.y>300) // ���� ������ ����� �� �����
		{
			// ������� � �� �������
			// ���������� ��������� � ������� �� ����� ����
			vecStars[i] = vecStars[vecStars.size()-1];
			// � ��������� ������ �������
			vecStars.pop_back();
		}
	}
	
	// ���������� ����� �����, ���� ������ ������,
	// ��� 0.1 ���
	m_fDT += fDeltaTime;
	while(m_fDT>.1f)
	{
		vecStars.push_back(Star(D3DXVECTOR2( (rand()%800)-400, -300), (rand()%5)+1));
		m_fDT-=.1f;
	}
}

void CStarField::Draw()
{
	// ������ �� ���� �� �������
	for (size_t i=0; i<vecStars.size(); i++)
	{
		D3DXVECTOR2 pos = vecStars[i].m_pos;
		float size = float(vecStars[i].m_size);
		m_Sprite->Draw(pos, size*.2f);
	}
}

CStarField::Star::Star( D3DXVECTOR2 pos, int size )
: m_pos(pos), m_size(size)
{
}
