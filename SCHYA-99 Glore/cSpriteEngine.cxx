// -------------------------------------------------------------
// Title:	SpriteEngine library
// Version:	0.01
// Description: спрайтовый движок, ресуем, обсчитываем, храним спрайты
//
// Dependences:	SDL library
// File:	cSpriteEngine.cxx
// License:	GNU Library General Public License 2 (LGPL2)
// Authors:	ћармусевич ј.¬. myrmik@mail.ru
// -------------------------------------------------------------

#include <stdio.h>
#include <new>
#include "cSpriteEngine.h"

using namespace std;

//-------------------------------------------------------------------------------------------
int cSpriteEngine::init(SDL_Surface *screen_)
{
    cSprite::Screen=screen_;
    cSprite::SpriteEngine=this;
    Screen=screen_;
    count=0;
    count_max=100;
    count_rezerv=100;
    try
    {
         SprateList = new cSprite*[count_max];
    }
    catch (bad_alloc xa)
    {
        fprintf(stderr, "Error no spice to memory \n\n");
        return -1;
    }


    return 0; // ошибок нет
}

//--------------------------------------------------------------------------------------------
void cSpriteEngine::draw(void)
{
    cSprite::Ticks=SDL_GetTicks();
    int i;
    for(i=0;i < count ; ++i)
        if(!SprateList[i]->iskiled())
        {
            SprateList[i]->draw();
        }
//	SDL_UpdateRect(Screen, 0, 0, 0, 0);
}

//---------------------------------------------------------------------------------------------
void cSpriteEngine::process(void)
{
    int i;
    for(i=0;i < count; i++)
        if(!SprateList[i]->iskiled())
            SprateList[i]->process();
}

//----------------------------------------------------------------------------------------------
cSpriteEngine::~cSpriteEngine()
{
	if ( SprateList != NULL ) {
		for ( int i=0; i<count; ++i )
		{
			delete SprateList[i];
		}
		delete [] SprateList;
	}
}


//-----------------------------------------------------------------------------------------------
int cSpriteEngine::add(cSprite *cSprite_,int x_,int y_,int z_)
{
   int i;

   if(x_!=-1)
    cSprite_->x=x_;
   if(y_!=-1)
    cSprite_->y=y_;
   if(z_!=-1)
    cSprite_->z=z_;
   //найти удаленные  и вставить вместо него
    for(i=0;i < count; ++i)
    {
      if(SprateList[i]->iskiled())
      {
         delete SprateList[i];
         SprateList[i] = cSprite_;
         SprateList[i]->id=i;
         sort_sprites();
         return(i);
      }
    }
   //если удаленных нет тогда добовл€ем в конец
   //добавить в конец

   if ((count+1)>count_max) //если нужно увеличить размер
   {

      cSprite **temp;
      try
      {
         temp=new cSprite*[count];
      }
      catch (bad_alloc xa)
      {
        fprintf(stderr, "Error no spice to memory \n\n");
        return -1;
      }
      for(int i=0;i<count;i++)
      {
         temp[i] = SprateList[i];
      }
      //удал€ем массив ор и создаем заново но на один элемент больше
      delete [] SprateList;
      count_max=count_max+count_rezerv;
      try
      {
         SprateList = new cSprite*[count_max];
      }
      catch (bad_alloc xa)
      {
        fprintf(stderr, "Error no spice to memory \n\n");
        return -1;
      }
      for(int i=0;i<count;i++)
      {
         SprateList[i]=temp[i];
      }
      delete [] temp;
   } //если нужно увеличить размер

   // добавл€ем элемент в конец
   SprateList[count] = cSprite_;
   SprateList[count]->id=count;
   i=count;
   count++;
   sort_sprites();
   return (i);
}

//-------------------------------------------------------------------------------------
int cSpriteEngine::add(cSpriteRepository *repository_, int imageID_,int x_,int y_,int z_)
{
   int id;
   try
   {
      id=add(new cSprite(repository_, imageID_),x_,y_,z_);
   }
   catch (bad_alloc xa)
   {
      fprintf(stderr, "Error no spice to memory \n\n");
      return -1;
   }
   return( id );
}



//-------------------------------------------------------------------------------------
void cSpriteEngine::sort_sprites(void)
{
    cSprite *t;
    int i, j;


    for (i = 1; i < count; i++) {
        t = SprateList[i];

        /* —двигаем элементы вниз, пока */
        /*  не найдем место вставки.    */
        for (j = i-1; j >= 0 && (SprateList[j]->z > t->z); j--)
            SprateList[j+1] = SprateList[j];

        /* вставка */
        SprateList[j+1] = t;
    }
}

//-------------------------------------------------------------------------------------
int cSpriteEngine::id2index(int id)
{
   for ( int i = 0; i <= count; i++)
   {
      if(SprateList[i]->id==id)
         return i;
   }
   return -1; //ненашли
}

