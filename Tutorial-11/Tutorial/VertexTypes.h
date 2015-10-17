#pragma once
#include <d3dx9.h>

struct VertPosDiffuse 
{
	D3DXVECTOR3 m_pos;
	D3DCOLOR m_color;
	VertPosDiffuse(D3DXVECTOR3 pos, D3DCOLOR color)
		: m_pos(pos), m_color(color)
	{}
};

struct VertPosTc 
{
	D3DXVECTOR3 m_pos;
	D3DXVECTOR2 m_tc;
	VertPosTc() {}
	VertPosTc(D3DXVECTOR3 pos, D3DXVECTOR2 tc)
		: m_pos(pos), m_tc(tc)
	{}
};
