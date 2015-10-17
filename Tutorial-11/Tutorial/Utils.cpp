#include "stdafx.h"
#include "Utils.h"

CPoint::CPoint()
: m_x(0), m_y(0)
{
}

CPoint::CPoint( int x, int y )
: m_x(x), m_y(y)
{
}

CRect::CRect()
{
}

CRect::CRect( CPoint ptmin, CPoint ptmax )
: m_min(ptmin), m_max(ptmax)
{
}