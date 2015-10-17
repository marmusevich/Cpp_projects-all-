#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <cstdio>

#include <SDL.h>
#include <SDL_TTF.h>

#include "cSpriteEngine.h"
#include "cBackGround.h"
#include "cPlayer.h"
#include "cEnemy.h"
#include "cWearon.h"





//расчет FPS
Uint32 ShowFPS_func(Uint32 interval, void *param);// FPS
//просто генерирует событие
Uint32 my_callbackfunc(Uint32 interval, void *param);

SDL_TimerID FPS_timer_id, my_timer_id; //

void TipeText(const char *text,int x, int y, int R, int G, int B); //оберта для печати

bool        ShowFPS,            //показывать FPS
            ShowFPSInWinCap,    //показывать FPS в заголовке окна
            fullscreen,         //полноэкранный режим
            ShowCursor;         //показывать системный курсор
int         width,              //ширина
            height,             //высота
            bpp,                //битрейт
            FPS_caunter,         //счетчик для расчета FPS
            FPS;                //значение FPS
char        *WinCaption,        //Заголовок окна
            *WinIconCaption;    //заголовок иконки
SDL_Surface
            *WinIcon,           //иконка окна
            *Screen;            //экран
TTF_Font *main_font = NULL; // шрифт


int main(int argc, char *argv[])
{
   {//иницилизация
      ShowFPS=true;            //
      ShowFPSInWinCap=true;    //
      fullscreen=false;        //
      ShowCursor=false;         //
      width=800;               //
      height=600;              //
      bpp=32;                  //
      FPS=0;
      FPS_caunter=0;
      WinCaption=new char[20] ;
      strcpy(WinCaption, "My App");
      //    *WinIconCaption;         //
      //    *WinIcon,                //髮 﫭͊      //鮨鬨衶鿠SDL
      if ( SDL_Init( ShowFPS ? SDL_INIT_TIMER|SDL_INIT_VIDEO : SDL_INIT_VIDEO ) < 0 )
      {
        fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
      }
      //
      //atexit(SDL_Quit);
      //
      SDL_WM_SetCaption(WinCaption,WinIconCaption);
      SDL_WM_SetIcon(WinIcon, NULL);
      //
      Screen = SDL_SetVideoMode( width, height, bpp, fullscreen ? SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN : SDL_HWSURFACE|SDL_DOUBLEBUF);
      if ( Screen == NULL )
      {
        fprintf(stderr, "Unable to set %d x %d - %d video: %s\n", width, height, bpp, SDL_GetError());
        exit(1);
      }
      //
      SDL_ShowCursor(ShowCursor);
      // FPS
      if (ShowFPS)
        FPS_timer_id = SDL_AddTimer(1000, ShowFPS_func, NULL);
      //

      my_timer_id = SDL_AddTimer(10, my_callbackfunc, NULL);



      if (TTF_Init() == -1)
      {
        fprintf(stderr, "Unable to initialize SDL_ttf: %s \n", TTF_GetError());
      }
      main_font = TTF_OpenFont("LucidaSansDemiBold.ttf", 16); // 䱳詬 鵲
      if (main_font == NULL)
      {  //  NULL
         fprintf(stderr, "Unable to load font: %s \n", TTF_GetError());
         return false;
      }

   }//иницилизация SDL


   //
   cSpriteRepository *Repository=new cSpriteRepository((char*)"Sprites.info");
   srand((1));
   cSpriteEngine *sEn= new cSpriteEngine(Screen);
   cBackGround *back_ground = new cBackGround(Screen, Repository->Image[0].Anim[0].image);
   //


   cPlayer *player=new cPlayer(Repository, 4);
   player->x = (Screen->w-player->w)/2;
   player->y = (Screen->h-player->h);
   player->z =50;
   player->wearon=new cWearon(Repository, 6);
   sEn->add(player);


   for(int i=0;i<9;i++)
   {
      sEn->add(new cEnemy(Repository, 5),rand() % (800),rand() % (600),rand() % (49));
   }

   cSprite *mouse = new cSprite(Repository, 7);
//   mouse->x = (Screen->w-mouse->w)/2;
//   mouse->y = (Screen->h-mouse->h)/2;
   int x,y;
   Uint8 mause_stay;
   mause_stay=SDL_GetMouseState(&x,&y);
   mouse->x = x;
   mouse->y = y;

   mouse->z =500;
   sEn->add(mouse);


   //главный цикл
   bool done = false;
   bool focus=true;
   while (!done)
   {
      // обработка событий
      SDL_Event event;
      while (SDL_PollEvent(&event))
      {
         switch (event.type)
         {
         case SDL_QUIT: //выход
            done = true;
            break;

         case SDL_USEREVENT: //пользовательское событие


            break;

         case SDL_KEYDOWN: // клавиша ESC
            if (event.key.keysym.sym == SDLK_ESCAPE)
                done = true;
            break;

         case SDL_ACTIVEEVENT: //теряем фокус
            if (!event.active.state&&SDL_APPMOUSEFOCUS)
               focus = (event.active.gain==1);
            break;
         }
      } // обработка событий

      if ( focus) //event.active.gain==1& event.active.state==SDL_APPINPUTFOCUS
      {
             //проверка клавиш
         Uint8* keys;
         keys=SDL_GetKeyState(NULL);
         if(keys[SDLK_LEFT])
         {
           player->dx(-1);
         }
         if(keys[SDLK_RIGHT])
         {
          player->dx(1);
         }
         if(keys[SDLK_UP])
         {
          player->dy(-1);
         }
         if(keys[SDLK_DOWN])
         {
            player->dy(1);
         }
         if(keys[SDLK_SPACE])
         {
            //огонь
            player->fire();
         }

         mause_stay=SDL_GetMouseState(&x,&y);
         mouse->x = x;
         mouse->y = y;

         sEn->process();
      }





      // рисование
      back_ground->draw();
      sEn->draw();

//         char text_tmp[100];
//         sprintf(text_tmp, "gain: %d, INPUT %d ACTIVE %d" ,event.active.gain, event.active.state&SDL_APPINPUTFOCUS, event.active.state&SDL_APPACTIVE);
//         TipeText(text_tmp, 00, 100, 240, 240, 0);

      if (ShowFPSInWinCap) //
      {
         char text_tmp[100];
         sprintf(text_tmp, "FPS: %d, спрайтов : %d" ,FPS, sEn->GetCount());
         TipeText(text_tmp, 0, 0, 240, 240, 0);
      }
      SDL_UpdateRect(Screen, 0, 0, 0, 0);
      SDL_Flip(Screen);
      FPS_caunter++;

   } //главный цикл

   //очистка памяти
   delete back_ground;
   delete player;
   delete sEn;
   delete Repository;

   SDL_RemoveTimer(FPS_timer_id);

   TTF_CloseFont(main_font); //
   TTF_Quit(); //
   SDL_Quit(); //
   return 0;
}


//--------------------------------------------------------------------------
//расчет FPS
Uint32 ShowFPS_func(Uint32 interval, void *param)
{
   FPS=FPS_caunter;
   FPS_caunter=0;
   return interval;
}


void TipeText(const char *text,int x=0, int y=0, int R=0, int G=0, int B=0)
{

   SDL_Surface* textSurface = NULL; //
   SDL_Rect textLocation = { x, y, 0, 0 };//

   int w,h;
   TTF_SizeUTF8(main_font,text,&w,&h);

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

   tmp = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCCOLORKEY, w+10, h+10, 32,rmask, gmask, bmask, amask);
   SDL_FillRect(tmp,NULL,SDL_MapRGBA(tmp->format,31,31,31,180));

   SDL_BlitSurface(tmp, NULL, Screen, &textLocation); //  screen
   textSurface = TTF_RenderUTF8_Solid(main_font, text, { R, G, B });//
   textLocation.x=x+5;
   textLocation.y=y+5;
   SDL_BlitSurface(textSurface, NULL, Screen, &textLocation); //  screen
   SDL_FreeSurface(tmp); //
   SDL_FreeSurface(textSurface); //
}

  Uint32 my_callbackfunc(Uint32 interval, void *param)
  {
         SDL_Event event;
         SDL_UserEvent userevent;
         /* Этот пример callback-функии посылает событие SDL_USEREVENT
            в очередь событий SDL и возвращает то же самое значение интервала,
            через которое функция будет вызвана вновь: */
         userevent.type = SDL_USEREVENT;
         userevent.code = 0;
         userevent.data1 = NULL;
         userevent.data2 = NULL;
         event.type = SDL_USEREVENT;
         event.user = userevent;
         SDL_PushEvent(&event);
         return(interval);
  }
