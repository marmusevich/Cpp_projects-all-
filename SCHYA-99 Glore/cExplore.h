#ifndef CEXPLORE_H
#define CEXPLORE_H

#include "csprite.h"
#include "cSpriteEngine.h"

class cExplore : public cSprite
{
   public:
      cExplore(){};
      virtual ~cExplore(){};
      cExplore(cSpriteRepository *repository_, int imageID_):cSprite(repository_,imageID_)
      {
         type_id=explore;
      }
      virtual void draw(void);     //отрисовка
   protected:
   private:
};

#endif // CEXPLORE_H
