// -------------------------------------------------------------
// Title:	SpriteEngine library
// Version:	0.01
// Description: спрайтовый движок, ресуем, обсчитываем, храним спрайты
//
// Dependences:	SDL library
// File:	cSpriteEngine.h
// License:	GNU Library General Public License 2 (LGPL2)
// Authors:	ћармусевич ј.¬. myrmik@mail.ru
// -------------------------------------------------------------

#ifndef __CSPRITEENGINE_H__
#define __CSPRITEENGINE_H__
#include "SDL.h"


#include "cSprite.h"

using namespace std;

//class cSprite;

class cSpriteEngine
{
  private:
    SDL_Surface *Screen;     //ссылка на экран
    cSprite **SprateList;
    int  count,         //количество спрайтов
         count_max,     //максимальное количество
         count_rezerv;  //количество резервируемых за один раз
   void sort_sprites(void); //сортировка спрайтов
   int id2index(int id); //индекс прайта по ид

  protected:
    int init(SDL_Surface *screen_);

  public:
    cSpriteEngine() {};
    cSpriteEngine(SDL_Surface *screen_) {init(screen_);}
    ~cSpriteEngine();

    void process(void);
    void draw(void);

    int add(cSprite *cSprite_, int x_=-1, int y_=-1, int z_=-1);
    int add(cSpriteRepository *repository_, int imageID_, int x_=-1, int y_=-1, int z_=-1);
    void kill_index(int index) {SprateList[index]->kill();}
    cSprite *get_index(int index) {return (SprateList[index]);};
    void kill_id(int id) {SprateList[id2index(id)]->kill();}
    cSprite *get_id(int id) {return (SprateList[id2index(id)]);};
    int GetCount(void) {return(count);}
};

#endif //__CSPRITEENGINE_H__
