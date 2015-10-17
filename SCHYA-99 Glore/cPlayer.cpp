#include "cPlayer.h"
#include "cSpriteEngine.h"

//Начальная скорость по X
#define nach_vel_X 4
//Начальная скорость по Y
#define nach_vel_Y 4
//скорость замедления по X
#define vel_zamed_X 0.1
//скорость замедления по Y
#define vel_zamed_Y 0.1
//время между выстрелами
#define fire_tyme 120
//время реагирования на клавиши
#define process_tyme 80
//---------------------------------------------
void cPlayer::draw(void)
{
    cSprite::draw();
}


//---------------------------------------------
void cPlayer::process(void)
{

   if(vx>0)
   {
      vx= vx-vel_zamed_X; //скорость замедления по X
   }
   else
   {
      vx=0;
      dirX=0;
   }
   x= x+vx*dirX;

   if(vy>0)
   {
      vy= vy-vel_zamed_Y;  //скорость замедления по Y
   }
   else
   {
      vy=0;
      dirY=0;
   }
   y= y+vy*dirY;

   if(x<0) x=0;
   if(x>(Screen->w-w)) x=Screen->w-w;
   if(y<0) y=0;
   if(y>(Screen->h-h)) y=Screen->h-h;
}


//---------------------------------------------
void cPlayer::dx(int dir)
{
    if((Ticks-last_process)> process_tyme)
    {
      vx=nach_vel_X; //Начальная скорость по X
      dirX=dir;
      last_process=Ticks;
    }
}

//---------------------------------------------
void cPlayer::dy(int dir)
{
    if((Ticks-last_process)> process_tyme)
    {
      vy=nach_vel_Y; //Начальная скорость по Y
      dirY=dir;
      last_process=Ticks;
    }
}

//---------------------------------------------
void cPlayer::fire(void)
{
    if((Ticks-last_fire)>fire_tyme)
    {
     SpriteEngine->add(new cWearon(repository, 6), x+w/2-repository->Image[6].W/2, y, 100);
     last_fire=Ticks;
    }
}

