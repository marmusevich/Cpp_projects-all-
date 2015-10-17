// -------------------------------------------------------------
// Title:	SpriteEngine library
// Version:	0.01
// Description:	����� ��������, ���� ����������� �� ���������
// ����� ��������������: ��������� *CSprite::Screen - ����������� ������, � ������� �������� �������� CSprite::id=0
// Dependences:	SDL library
// File:	CSprite.h
// License:	GNU Library General Public License 2 (LGPL2)
// Authors:	���������� �.�. myrmik@mail.ru
// -------------------------------------------------------------

#ifndef __CSPRITE_H__
#define __CSPRITE_H__

#include "SDL.h"
#include "cSpriteRepository.h"

enum sprite_type
{
   uncnow = 0,
   player = 1,
   wearon = 10,
   explore  = 999,
   enemy  = 1000
};

class cSpriteEngine;

class cSprite
{
  private:

  protected:
    int init(cSpriteRepository *repository_, int imageID_); // ������������ �������,
                                                             //��������� ������ �� ���������
                                                             //� ������ �����������
   Uint32  Lastupdate;           //���� ��������� ��������� ����
   unsigned    imageID,          //������ ����������� � ���������
               frame;            //������� ����
   float       AnimSpeed;        //�������� ��������
   bool        animated,         //���./����. ��������
               kiled;            //"������" ������, - �� �������� ������
                  // ��� ������� ������������
   int       col_h,              //������
             col_w;              //������


   cSpriteRepository *repository;//������ �� ���������

  public:
   cSprite();
   cSprite(cSpriteRepository *repository_, int imageID_) {init(repository_, imageID_);}
   virtual ~cSprite() {};

   virtual void draw(void);                    //���������
   virtual void process(void);                 //���������� ����������

   void kill(void) {kiled=true;}
   bool iskiled(void) {return kiled;}


   int Collide(cSprite *sp); // �������� �� ������������

   int       id;                 //�����������
   sprite_type type_id;          //��� �������
   float     x,                  //����������
             y;                  //����������
   int       z,                  //����, ��� ������ ��� �������
             h,                  //������
             w;                  //������

   static SDL_Surface *Screen;     //������ �� �����
   static cSpriteEngine *SpriteEngine;  //������ �� ������
   static Uint32  Ticks;

};
#endif //__CSPRITE_H__
