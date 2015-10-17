#ifndef CTRAEKTORYLIBRARY_H
#define CTRAEKTORYLIBRARY_H

#include "SDL.h"

enum traektory_type
{
   nomuved,
   up2down,
   down2up,
   left2right,
   right2left,
   diogonal_up2down_left,
   diogonal_up2down_right
};

class cTraektoryLibrary
{
   public:
      cTraektoryLibrary();
      virtual ~cTraektoryLibrary();

      void moved(traektory_type type, Uint32 time, float &x, float &y); //
   protected:
   private:
};

#endif // CTRAEKTORYLIBRARY_H
