#include "cBackGround.h"
//#include "SDL_rotozoom.h"
//------------------------------------------------------------------------------------------------------
cBackGround::cBackGround(SDL_Surface *screen_, SDL_Surface *background_, int x_, int y_, int w_, int h_)
{
    dest.x = x_;
    dest.y = y_;
    Screen=screen_;
    if (!w_||!h_)
    {
        dest.w=Screen->w;
        dest.h=Screen->h;
    }
    else
    {
        dest.w=w_;
        dest.h=h_;
    }
    //background=zoomSurface(background_, (double)(dest.w+1) / (double)background_->w, (double)(dest.h+1) / (double)background_->h, 0);
 background=background_;//, (double)(dest.w+1) / (double)background_->w, (double)(dest.h+1) / (double)background_->h, 0);
}

//------------------------------------------------------------------------------------------------------
//вывод фона
 void cBackGround::draw()
{
   // SDL_BlitSurface(background,  NULL, Screen, &dest);
}


