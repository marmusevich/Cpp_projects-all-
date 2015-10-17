#include "cExplore.h"


//---------------------------------------------
void cExplore::draw(void)
{
   //Ticks=SDL_GetTicks();
   if(Lastupdate + (Uint32)repository->Image[imageID].pause * AnimSpeed < Ticks)
   {
      frame++;
      Lastupdate = Ticks;
      if(frame > repository->Image[imageID].Numframes -1)
      {
         kiled=true;
         return;
      }

   }
   SDL_Rect dest;
   dest.x = (Sint16)(x+0.5)-w/2;
   dest.y = (Sint16)(y+0.5)-h/2;
   SDL_BlitSurface(repository->Image[imageID].Anim[frame].image, NULL, Screen, &dest);

}
