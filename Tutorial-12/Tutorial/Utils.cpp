#include "stdafx.h"
#include "Utils.h"
#include <fstream>

using namespace std;

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

string GetFileAsString(const string& strFileName)
{
	string content;
	std::ifstream in(strFileName.c_str(), std::ios::binary);
	std::istreambuf_iterator<char> begin(in), end;
	while(begin != end)
		content += *begin++;
	return content;
}