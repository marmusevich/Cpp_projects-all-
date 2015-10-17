#include "cWearon.h"
#include "cExplore.h"



//---------------------------------------------
void cWearon::draw(void)
{
   cSprite::draw();
}

//---------------------------------------------
void cWearon::process(void)
{

   y=y-3;
   if((y < (0-h))||(y > (Screen->h+h)))
   {
      kiled=true;
   }

   for(int i=0;i < SpriteEngine->GetCount();i++)
   {
      cSprite *sp=SpriteEngine->get_index(i);
      if(sp->type_id >= enemy && Collide(sp))
      {
         int x = sp->x + sp->w/2;
         int y = sp->y + sp->h/2;
         sp->kill();
         kiled=true;
         SpriteEngine->add(new cExplore(repository, 1),x,y,999);

      }
   }
}
