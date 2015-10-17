#ifndef CWIDGETS_H
#define CWIDGETS_H


class cWidgets
{
   public:
      cWidgets();
      virtual ~cWidgets();

      bool active;      //активный
      bool deleted;     //удаленый
      bool visible;     //видемый
      bool enabled;     //доступный

      int x;
      int y;
      int h;
      int w;
      int z; //слой

      bool is_in_rect(int x_, int y_);
   protected:
   private:

};

#endif // CWIDGETS_H
