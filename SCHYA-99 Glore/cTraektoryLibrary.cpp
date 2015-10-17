#include "cTraektoryLibrary.h"

cTraektoryLibrary::cTraektoryLibrary()
{
   //ctor
}

cTraektoryLibrary::~cTraektoryLibrary()
{
   //dtor
}


void cTraektoryLibrary::moved(traektory_type type, Uint32 time, float &x, float &y)
{
   switch(type)
   {

      case nomuved:
         return;
         break;
      case up2down:
         break;
      case down2up:
         break;
      case left2right:
         break;
      case right2left:
         break;
      case diogonal_up2down_left:
         break;
      case diogonal_up2down_right:
         break;
   }
}
