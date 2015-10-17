
#ifndef _CBACKGROUND_H_INCLUDED_
#define _CBACKGROUND_H_INCLUDED_

#include "SDL.h"



class cBackGround
{
  private:
    SDL_Surface *background,        //поверхность заднего фона
                *Screen;            //ссылка на экран
    SDL_Rect dest; //прямоугольник  вывода

  protected:

  public:
   // cBackGround();
    cBackGround(SDL_Surface *screen_, SDL_Surface *background_, int x_=0, int y_=0, int w_=0, int h_=0);


   // ~cBackGround();
    void draw();//вывод фона

    // очистка экрана; r, g, b - цвет фона по умалчанию черный цвет
    void clear(int r=0, int g=0, int b=0) {SDL_FillRect(Screen, &dest, SDL_MapRGB(Screen->format, r, g, b));}
};


#endif // _CBACKGROUND_H_INCLUDED_
