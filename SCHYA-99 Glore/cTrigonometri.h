// -------------------------------------------------------------
// Title:	Trigonometri library
// Version:	0.01
// Description:	����� ��� ���������� ������������������ �������
// File:	Trigonometri.h
// License:	GNU Library General Public License 2 (LGPL2)
// Authors:	���������� �.�. myrmik@mail.ru
// -------------------------------------------------------------

#ifndef TRIGONOMETRI_H_INCLUDED
#define TRIGONOMETRI_H_INCLUDED

class cTrigonometri
{
  private:
    struct
    {
        int   grad;
        float rad;
        float cos;
        float sin;
        float tan;
    } data[19];

    int loaded;

  protected:

  public:

    float PI;

    cTrigonometri(void);



    //������� ��� ��������
    float cos_g(float arg);
    float sin_g(float arg);
    float tan_g(float arg);

    //������� ��� ��������
    float cos_r(float arg) {return cos_g(arg * 180 / 3.141592653589793238462643383279);}
    float sin_r(float arg) {return sin_g(arg * 180 / 3.141592653589793238462643383279);}
    float tan_r(float arg) {return tan_g(arg * 180 / 3.141592653589793238462643383279);}

    //������� �������� � �������
    inline float Rad2Grad(float arg) {return arg * 180 / 3.141592653589793238462643383279;}
    //������� �������� � �������
    inline float Grad2Rad(float arg) {return arg * 3.141592653589793238462643383279 / 180;}

};

    //float cTrigonometri::PI;
    //int cTrigonometri::loaded;
    //cTrigonometri::
#endif // TRIGONOMETRI_H_INCLUDED
