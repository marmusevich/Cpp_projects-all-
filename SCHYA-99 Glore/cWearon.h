#ifndef CWEARON_H
#define CWEARON_H

#include "csprite.h"
#include "cSpriteEngine.h"

class cWearon : public cSprite
{
    public:
      cWearon(){};
      cWearon(cSpriteRepository *repository_, int imageID_):cSprite(repository_,imageID_)
      {type_id=wearon;}
      virtual ~cWearon(){};
      virtual void draw(void);     //отрисовка
      virtual void process(void);  //внутренние вычесления
    protected:
    private:
};

#endif // CWEARON_H
