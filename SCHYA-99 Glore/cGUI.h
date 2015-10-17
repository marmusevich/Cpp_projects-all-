#ifndef CGUI_H
#define CGUI_H

#include "SDL.h"


#include "cWidgets.h"

class cGUI
{
   public:
      cGUI();
      cGUI(SDL_Surface *screen_) {init(screen_);}
      virtual ~cGUI();
      int GetCount(void) {return(count);}
   protected:
    int init(SDL_Surface *screen_);
   private:
    SDL_Surface *Screen;     //������ �� �����
    cWidgets **WidgetList;
   int  count,         //����������
        count_max,     //������������ ����������
        count_rezerv;  //���������� ������������� �� ���� ���
   void sort_widgets(void); //����������
};

#endif // CGUI_H
