// -------------------------------------------------------------
// Title:	SpriteEngine library
// Version:	0.01
// Description:	класс спрайтов, сами изображени€ из хранилища
// перед использованием: присвоить *CSprite::Screen - поверхность экрана, и счетчик спрайтов обнулить CSprite::id=0
// Dependences:	SDL library
// File:	CSprite.h
// License:	GNU Library General Public License 2 (LGPL2)
// Authors:	ћармусевич ј.¬. myrmik@mail.ru
// -------------------------------------------------------------

#include <stdio.h>
#include "csprite.h"


//об€вление статических переменных класса
SDL_Surface *cSprite::Screen;
cSpriteEngine *cSprite::SpriteEngine;
Uint32 cSprite::Ticks;
//---------------------------------------------
int cSprite::init(cSpriteRepository *repository_, int imageID_)
{
   repository = repository_;
   imageID = imageID_;
   h=repository->Image[imageID].H;
   w=repository->Image[imageID].W;
   x=y=z=0;
   col_h=h;
   col_w=w;
   animated=repository->Image[imageID].Numframes > 1;
   AnimSpeed=1;
   frame=0;
   kiled=false;
   Lastupdate=0;
   type_id=uncnow;



   return 0; // ошибок нет
}


//---------------------------------------------
//переопредел€ть
void cSprite::process(void)
{

}

//---------------------------------------------
void cSprite::draw(void)
{
    if(animated)
    {
        if(Lastupdate + (Uint32)repository->Image[imageID].pause * AnimSpeed < Ticks)
        {
            frame++;
            if(frame > repository->Image[imageID].Numframes -1)
                frame=0;
            Lastupdate = Ticks;
        }
    }
    SDL_Rect dest;
    dest.x = (Sint16)(x+0.5);
    dest.y = (Sint16)(y+0.5);
    SDL_BlitSurface(repository->Image[imageID].Anim[frame].image, NULL, Screen, &dest);
}


int cSprite::Collide(cSprite *sp)
{
	if(sp->x + sp->col_w < x)	return 0;	//just checking if their
	if(sp->x > x + col_w)	return 0;	//bounding boxes even touch

	if(sp->y + sp->col_h < y)	return 0;
	if(sp->y > y + col_h)	return 0;

	return 1;				//bounding boxes intersect
}
