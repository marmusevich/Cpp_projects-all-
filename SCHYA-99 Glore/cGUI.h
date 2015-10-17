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
    SDL_Surface *Screen;     //ссылка на экран
    cWidgets **WidgetList;
   int  count,         //количество
        count_max,     //максимальное количество
        count_rezerv;  //количество резервируемых за один раз
   void sort_widgets(void); //сортировка
};

#endif // CGUI_H
