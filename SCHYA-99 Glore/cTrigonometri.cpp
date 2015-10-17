// -------------------------------------------------------------
// Title:	Trigonometri library
// Version:	0.01
// Description:	класс для вычесления тригонометрических функций
// File:	Trigonometri.cpp
// License:	GNU Library General Public License 2 (LGPL2)
// Authors:	Мармусевич А.В. myrmik@mail.ru
// -------------------------------------------------------------
#include <iostream>
#include <cmath>
#include "cTrigonometri.h"

using namespace std;

cTrigonometri::cTrigonometri(void)
{
    PI=3.141592653589793238462643383279;
    for(int i=0;i<18;i++)
    {
        data[i].grad = i*5;
        data[i].rad  = Grad2Rad(i*5);
        data[i].sin  = sin(data[i].rad);
        data[i].cos  = cos(data[i].rad);
        data[i].tan  = tan(data[i].rad);
    }
    data[18].grad = 90;
    data[18].rad  = PI/2;
    data[18].sin  = 1;
    data[18].cos  = 0;
    data[18].tan  = 1.04571e+06;

    loaded=1;
}

float cTrigonometri::cos_g(float arg)
{
    float r=0;
    if(loaded==1)
    {
       // если аргумент больше 360 градусов
        if(abs(arg)>360)
        {

        }

        //если аргумент отрицательный
        if(arg<0)
        {
            arg=360-arg;
        }

        //проверяем квадрант и приводим к первому
        if(arg>=0 && arg<=90)
        {
            //arg=arg;
            r=1;
        }
        else if(arg>90 && arg<=180)
            {
                arg=arg-90;//????
                r=1;
            }
            else if(arg>90 && arg<=180)
                {
                    arg=arg-90;//????
                    r=-1;
                }
                else if(arg>90 && arg<=180)
                    {
                        arg=arg-90; //????
                        r=-1;
                    }
        //находим для 1 квадранта
        int i;
        for(i=0;i<18;i++)
        {
           if(data[i].grad<=arg && data[i+1].grad>arg) break;
        }
        return r *( data[i].cos+(data[i+1].cos-data[i].cos)/(data[i+1].grad-data[i].grad)*(arg-data[i].grad));
   }
    else return 0;
}


float cTrigonometri::sin_g(float arg)
{
    float r=0;
    if(loaded==1)
    {
        //если аргумент больше 360 градусов
//        if(abs(arg)>360)
//        {
//
//        }

        //если аргумент отрицательный
        if(arg<0)
        {
            arg=360-arg;
        }

        //проверяем квадрант и приводим к первому
        if(arg>=0 && arg<=90)
        {
            //arg=arg;
            r=1;
        }
        else if(arg>90 && arg<=180)
            {
                arg=arg-90;//????
                r=1;
            }
            else if(arg>90 && arg<=180)
                {
                    arg=arg-90;//????
                    r=-1;
                }
                else if(arg>90 && arg<=180)
                    {
                        arg=arg-90; //????
                        r=-1;
                    }
        //находим для 1 квадранта
        int i;
        for(i=0;i<18;i++)
        {
           if(data[i].grad<=arg && data[i+1].grad>arg) break;
        }
        return r *( data[i].sin+(data[i+1].sin-data[i].sin)/(data[i+1].grad-data[i].grad)*(arg-data[i].grad));
    }
    else return 0;
}

float cTrigonometri::tan_g(float arg)
{
    float r=0;
    if(loaded==1)
    {
        //если аргумент больше 360 градусов
//        if(abs(arg)>360)
//        {
//
//        }

        //если аргумент отрицательный
        if(arg<0)
        {
            arg=360-arg;
        }

        //проверяем квадрант и приводим к первому
        if(arg>=0 && arg<=90)
        {
            //arg=arg;
            r=1;
        }
        else if(arg>90 && arg<=180)
            {
                arg=arg-90;//????
                r=1;
            }
            else if(arg>90 && arg<=180)
                {
                    arg=arg-90;//????
                    r=-1;
                }
                else if(arg>90 && arg<=180)
                    {
                        arg=arg-90; //????
                        r=-1;
                    }
        //находим для 1 квадранта
        int i;
        for(i=0;i<18;i++)
        {
           if(data[i].grad<=arg && data[i+1].grad>arg) break;
        }
        return r *( data[i].tan+(data[i+1].tan-data[i].tan)/(data[i+1].grad-data[i].grad)*(arg-data[i].grad));
    }
    else return 0;
}
