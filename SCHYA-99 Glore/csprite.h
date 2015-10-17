// -------------------------------------------------------------
// Title:	SpriteEngine library
// Version:	0.01
// Description:	класс спрайтов, сами изображения из хранилища
// перед использованием: присвоить *CSprite::Screen - поверхность экрана, и счетчик спрайтов обнулить CSprite::id=0
// Dependences:	SDL library
// File:	CSprite.h
// License:	GNU Library General Public License 2 (LGPL2)
// Authors:	Мармусевич А.В. myrmik@mail.ru
// -------------------------------------------------------------

#ifndef __CSPRITE_H__
#define __CSPRITE_H__

#include "SDL.h"
#include "cSpriteRepository.h"

enum sprite_type
{
   uncnow = 0,
   player = 1,
   wearon = 10,
   explore  = 999,
   enemy  = 1000
};

class cSpriteEngine;

class cSprite
{
  private:

  protected:
    int init(cSpriteRepository *repository_, int imageID_); // иницилизация спрайта,
                                                             //передаётся ссылка на хранилище
                                                             //и индекс изображения
   Uint32  Lastupdate;           //кога выводился последний кадр
   unsigned    imageID,          //индекс изображения в хранилище
               frame;            //текущий кадр
   float       AnimSpeed;        //скорость анимации
   bool        animated,         //вкл./выкл. анимацию
               kiled;            //"убитый" спрайт, - не активный спрайт
                  // для расчета столкновений
   int       col_h,              //высота
             col_w;              //ширина


   cSpriteRepository *repository;//ссылка на хранилище

  public:
   cSprite();
   cSprite(cSpriteRepository *repository_, int imageID_) {init(repository_, imageID_);}
   virtual ~cSprite() {};

   virtual void draw(void);                    //отрисовка
   virtual void process(void);                 //внутренние вычесления

   void kill(void) {kiled=true;}
   bool iskiled(void) {return kiled;}


   int Collide(cSprite *sp); // проверка на столкновение

   int       id;                 //индификатор
   sprite_type type_id;          //тип спрайта
   float     x,                  //координата
             y;                  //координата
   int       z,                  //слой, или высота над экраном
             h,                  //высота
             w;                  //ширина

   static SDL_Surface *Screen;     //ссылка на экран
   static cSpriteEngine *SpriteEngine;  //ссылка на движок
   static Uint32  Ticks;

};
#endif //__CSPRITE_H__
