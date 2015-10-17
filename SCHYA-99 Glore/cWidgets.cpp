#include "cWidgets.h"

cWidgets::cWidgets()
{
   //ctor
}

cWidgets::~cWidgets()
{
   //dtor
}

bool cWidgets::is_in_rect(int x_, int y_)
{
	if ((x_ < x) || (x_ >= (x + w)) || (y_ < y) || (y_ >= (y + h)))
        return(false);
	return(true);
}
