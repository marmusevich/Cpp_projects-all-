
#ifndef _CBACKGROUND_H_INCLUDED_
#define _CBACKGROUND_H_INCLUDED_

#include "SDL.h"



class cBackGround
{
  private:
    SDL_Surface *background,        //����������� ������� ����
                *Screen;            //������ �� �����
    SDL_Rect dest; //�������������  ������

  protected:

  public:
   // cBackGround();
    cBackGround(SDL_Surface *screen_, SDL_Surface *background_, int x_=0, int y_=0, int w_=0, int h_=0);


   // ~cBackGround();
    void draw();//����� ����

    // ������� ������; r, g, b - ���� ���� �� ��������� ������ ����
    void clear(int r=0, int g=0, int b=0) {SDL_FillRect(Screen, &dest, SDL_MapRGB(Screen->format, r, g, b));}
};


#endif // _CBACKGROUND_H_INCLUDED_
