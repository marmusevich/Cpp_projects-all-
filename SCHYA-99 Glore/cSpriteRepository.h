// -------------------------------------------------------------
// Title:	SpriteEngine library
// Version:	0.01
// Description:	��������� ������������ ��������.
//		�������� ����������� �������������� SDL_Image
// Dependences:	SDL library
// File:	cSpriteRepository.h
// License:	GNU Library General Public License 2 (LGPL2)
// Authors:	���������� �.�. myrmik@mail.ru
// -------------------------------------------------------------

#ifndef __CSPRITEREPOSITORY_H__
#define __CSPRITEREPOSITORY_H__

#include "SDL.h"
#include <SDL_Image.h>

typedef struct
{
  SDL_Surface *image;
} CSpriteFrame;

typedef struct  //��������� ��� �������� ������ �������
{
  CSpriteFrame *Anim;   //����� � �������
  unsigned
        Numframes,      //���������� ������
        W,              //������
        H,              //������
        pause;          //����� ��������
  //���������, ���  � �.�.
} COneSprite;

class cSpriteRepository //���� ��������� ��������
{
  public:
    cSpriteRepository();
    cSpriteRepository(char *SpriteInfoFile_) {init(SpriteInfoFile_);} //�����������
    ~cSpriteRepository(); //����������
   // SDL_Surface get_sprite(int index);
    //SDL_Surface get_sprite(string name);
 // protected:

    int init(char *SpriteInfoFile);

    unsigned NumSprites;     //���������� �������� �� ��������
    COneSprite *Image;  //����� �������� �� ��������
};

#endif //__CSPRITEREPOSITORY_H__
