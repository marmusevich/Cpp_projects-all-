// -------------------------------------------------------------
// Title:	SpriteEngine library
// Version:	0.01
// Description:	хранилеще анимированых спрайтов.
//		загрузка изображений поддерживаемых SDL_Image
// Dependences:	SDL library
// File:	cSpriteRepository.h
// License:	GNU Library General Public License 2 (LGPL2)
// Authors:	Мармусевич А.В. myrmik@mail.ru
// -------------------------------------------------------------

#ifndef __CSPRITEREPOSITORY_H__
#define __CSPRITEREPOSITORY_H__

#include "SDL.h"
#include <SDL_Image.h>

typedef struct
{
  SDL_Surface *image;
} CSpriteFrame;

typedef struct  //структура для хранения одного спрайта
{
  CSpriteFrame *Anim;   //масив с кадрами
  unsigned
        Numframes,      //количество кадров
        W,              //ширина
        H,              //высота
        pause;          //пауза анимации
  //заголовок, имя  и т.д.
} COneSprite;

class cSpriteRepository //клас хранилеще спрайтов
{
  public:
    cSpriteRepository();
    cSpriteRepository(char *SpriteInfoFile_) {init(SpriteInfoFile_);} //конструктор
    ~cSpriteRepository(); //диструктор
   // SDL_Surface get_sprite(int index);
    //SDL_Surface get_sprite(string name);
 // protected:

    int init(char *SpriteInfoFile);

    unsigned NumSprites;     //количество спрайтов на хранении
    COneSprite *Image;  //масив спрайтов на хранении
};

#endif //__CSPRITEREPOSITORY_H__
