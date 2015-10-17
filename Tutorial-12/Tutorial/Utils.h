#pragma once
#include <d3d9.h>
#include <string>

struct CPoint
{
	int m_x, m_y;
	CPoint();
	CPoint(int x, int y);
};

struct CRect
{
	CPoint m_min, m_max;
	CRect();
	CRect(CPoint ptmin, CPoint ptMax);
};

std::string GetFileAsString(const std::string& strFileName);