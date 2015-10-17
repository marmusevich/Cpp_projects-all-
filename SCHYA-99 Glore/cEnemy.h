// -------------------------------------------------------------
// Title:
// Version:	0.01
// Description:
//
// Dependences:	SDL library
// File:	cEnemy.cpp
// License:	GNU Library General Public License 2 (LGPL2)
// Authors:	Мармусевич А.В. myrmik@mail.ru
// -------------------------------------------------------------

#ifndef CENEMY_H
#define CENEMY_H

#include "csprite.h"

class cEnemy : public cSprite
{
    public:
      cEnemy();
      cEnemy(cSpriteRepository *repository_, int imageID_):cSprite(repository_,imageID_)
      {
         type_id=enemy;
         dx = rand() % (5)-3;
         dy = rand() % (5)-3;
      }
      virtual ~cEnemy(){};
      virtual void draw();     //отрисовка
      virtual void process(void);   //внутренние вычесления
    protected:
       //отладка
      int dx,dy;
    private:
};

#endif // CENEMY_H
