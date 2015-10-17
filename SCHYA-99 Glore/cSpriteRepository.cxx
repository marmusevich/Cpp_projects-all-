// -------------------------------------------------------------
// Title:	SpriteEngine library
// Version:	0.01
// Description:	хранилеще анимированых спрайтов.
//		загрузка изображений поддерживаемых SDL_Image
// Dependences:	SDL library
// File:	cSpriteRepository.cxx
// License:	GNU Library General Public License 2 (LGPL2)
// Authors:	Мармусевич А.В. myrmik@mail.ru
// -------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <new>
#include <string>
#include "SDL_image.h"

#include "cSpriteRepository.h"
using namespace std;

//-------------------------------------------------
int cSpriteRepository::init(char* SpriteInfoFile)
{


    char buffer[512];
    char name[255];

    int lNumframes=1, lpause=0, lW=1, lH=1, r=0, g=0, b=0;
    int Nw; //количество кадров по горизонтале
    unsigned count = 0; //счетчик прочитаных спрайтов
    FILE *fp;

    //чтение файла с описанием загружаемого хранилища
    if((fp=fopen(SpriteInfoFile,"r"))==NULL)
    {
        fprintf(stderr, "Error opening sprite info file %s\n\n",SpriteInfoFile);
        return -1;
    }
    //получение из файла количества спрайтов в хранилеще
    fgets(buffer, 512 ,fp);
    sscanf(buffer,"SPRITES: %d",&NumSprites);

    //создание масива под хранилеще
    try
    {
         Image = new COneSprite[NumSprites];
    }
    catch (bad_alloc xa)
    {
        fprintf(stderr, "Error no spice to memory \n\n");
        return -1;
    }
    //последовательное чтение всех строк файла
    while(!feof(fp) && count < NumSprites)
    {
        fgets(buffer, 512, fp);
        //если пустая строка или коментарий то не читаем
        if(buffer[0]!='#' && buffer[0]!='\r' && buffer[0]!='\n' && buffer[0]!='\0' && strlen(buffer)!=0)
        {
            sscanf(buffer, "%s %d %d %d %d %d %d %d", name, &lNumframes, &lpause, &lW, &lH, &r, &g, &b);
            Image[count].Numframes=lNumframes;
            Image[count].pause=lpause;
            Image[count].W=lW;
            Image[count].H=lH;
            //размер масива с кадрами анимации
            try
            {
               Image[count].Anim = new CSpriteFrame[lNumframes];
            }
            catch (bad_alloc xa)
            {
                fprintf(stderr, "Error no spice to memory \n\n");
                return -1;
            }
            //чтение изображения
            SDL_Surface *temp = IMG_Load(name);                                           // из SDL_image.h чтение

            if(!temp)
            {
                fprintf(stderr, "Loading %s failed...\n",name);
                return -1;
            }
            Nw=temp->w / lW;
            //квадрат харектеристик одного кадра
            SDL_Rect srcr;
            srcr.x = 0;
            srcr.y = 0;
            srcr.w = lW;
            srcr.h = lH;
            //создаём временную пустую поверхность
            SDL_Surface *tmp;
            Uint32 rmask, gmask, bmask, amask;
            #if SDL_BYTEORDER == SDL_BIG_ENDIAN
                rmask = 0xff000000;
                gmask = 0x00ff0000;
                bmask = 0x0000ff00;
                amask = 0x000000ff;
            #else
                rmask = 0x000000ff;
                gmask = 0x0000ff00;
                bmask = 0x00ff0000;
                amask = 0xff000000;
            #endif
            tmp = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCCOLORKEY, lW, lH, 32,rmask, gmask, bmask, amask);
            if(tmp == NULL)
            {
                fprintf(stderr, "Create temp RGBSurface failed: %s\n", SDL_GetError());
                return -1;
            }
            //вырезаем кадры
            for(int i=0; i<lNumframes; i++)
            {
                //получить коордионаты текущего кадра
                srcr.x=lW * (i - (i / Nw) * Nw);
                srcr.y=lH * (i / Nw);
                //вырезаем кадр из исходного изображения
                SDL_BlitSurface(temp,&srcr,tmp,NULL);
                //устанавливаем прозрачность
                if(r>=0 && g>=0 && b>=0)
                    SDL_SetColorKey(tmp,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tmp->format,r,g,b));
                //сохраняем конечное изображение
                Image[count].Anim[i].image = SDL_DisplayFormat(tmp);
            }
            SDL_FreeSurface(tmp);
            SDL_FreeSurface(temp);
            printf( "Loaded  sprite '%s' %d x %d frames %d \n",name,lW,lH,lNumframes);
            count++;
        }
    }
    fclose(fp);
    return 0; // ошибок нет
}

cSpriteRepository::~cSpriteRepository()
{
    for(unsigned i=0; i<NumSprites; i++)
        delete [] Image[i].Anim;
    delete [] Image;

}
