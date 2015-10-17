
#ifndef _CPLAYER_H_
#define _CPLAYER_H_

#include "csprite.h"
#include "cWearon.h"

class cPlayer : public cSprite
{
    public:

      cPlayer() {}
      cPlayer(cSpriteRepository *repository_, int imageID_):cSprite(repository_,imageID_)
        {type_id=player; vx=0;vy=0;dirX=0;dirY=0;last_fire=0;last_process=0;}
      ~cPlayer(){};
      virtual void draw(void);     //отрисовка
      virtual void process(void);   //внутренние вычесления
      void dx(int dir);
      void dy(int dir);
      void fire(void);

    cWearon *wearon;
    protected:

    private:
      float vx, vy; //скорость по x y соответственно
      int dirX, dirY; //направление движения
      Uint32 last_fire; // последний выстрел
      Uint32 last_process; // последний выстрел

};



#endif // _CPLAYER_H_
