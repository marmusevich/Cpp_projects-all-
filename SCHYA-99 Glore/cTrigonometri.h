// -------------------------------------------------------------
// Title:	Trigonometri library
// Version:	0.01
// Description:	класс для вычесления тригонометрических функций
// File:	Trigonometri.h
// License:	GNU Library General Public License 2 (LGPL2)
// Authors:	Мармусевич А.В. myrmik@mail.ru
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



    //функции для градусов
    float cos_g(float arg);
    float sin_g(float arg);
    float tan_g(float arg);

    //функции для радианов
    float cos_r(float arg) {return cos_g(arg * 180 / 3.141592653589793238462643383279);}
    float sin_r(float arg) {return sin_g(arg * 180 / 3.141592653589793238462643383279);}
    float tan_r(float arg) {return tan_g(arg * 180 / 3.141592653589793238462643383279);}

    //перевод радианов в градусы
    inline float Rad2Grad(float arg) {return arg * 180 / 3.141592653589793238462643383279;}
    //перевод градусов в радианы
    inline float Grad2Rad(float arg) {return arg * 3.141592653589793238462643383279 / 180;}

};

    //float cTrigonometri::PI;
    //int cTrigonometri::loaded;
    //cTrigonometri::
#endif // TRIGONOMETRI_H_INCLUDED
