#ifndef CWIDGETS_H
#define CWIDGETS_H


class cWidgets
{
   public:
      cWidgets();
      virtual ~cWidgets();

      bool active;      //��������
      bool deleted;     //��������
      bool visible;     //�������
      bool enabled;     //���������

      int x;
      int y;
      int h;
      int w;
      int z; //����

      bool is_in_rect(int x_, int y_);
   protected:
   private:

};

#endif // CWIDGETS_H
