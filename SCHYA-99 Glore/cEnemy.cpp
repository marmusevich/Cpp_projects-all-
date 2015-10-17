
#include "cEnemy.h"

//---------------------------------------------
void cEnemy::draw()
{
   cSprite::draw();
}

//---------------------------------------------
void cEnemy::process(void)
{
   x=x+dx;
   y=y+dy;

   //ограничения выхода за экран
   if(x < (0-w) )
   {
      x = 0-w;
      dx = -dx;
   }
   if(x > (Screen->w + w) )
   {
      x = Screen->w+w;
      dx = -dx;
   }
   if(y < (0-h) )
   {
      y = 0-h;
      dy = -dy;
   }
   if(y > (Screen->h+h) ) {
      y = Screen->h+h;
      dy = -dy;
   }
}
