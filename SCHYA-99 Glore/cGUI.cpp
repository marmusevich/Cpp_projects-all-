#include "cGUI.h"


#include <stdio.h>
#include <new>

using namespace std;

//-------------------------------------------------------------------------------------------
int cGUI::init(SDL_Surface *screen_)
{
    Screen=screen_;
    count=0;
    count_max=10;
    count_rezerv=10;
    try
    {
         WidgetList = new cWidgets*[count_max];
    }
    catch (bad_alloc xa)
    {
        fprintf(stderr, "Error no spice to memory \n\n");
        return -1;
    }


    return 0; // ошибок нет
}

//-----------------------------------------------------------------------------------------------
cGUI::cGUI()
{
   //ctor
}


//----------------------------------------------------------------------------------------------
cGUI::~cGUI()
{
	if ( WidgetList != NULL ) {
		for ( int i=0; i<count; ++i )
		{
			delete WidgetList[i];
		}
		delete [] WidgetList;
	}
}



//-------------------------------------------------------------------------------------
void cGUI::sort_widgets(void)
{
    cWidgets *t;
    int i, j;


    for (i = 1; i < count; i++) {
        t = WidgetList[i];

        /* Сдвигаем элементы вниз, пока */
        /*  не найдем место вставки.    */
        for (j = i-1; j >= 0 && (WidgetList[j]->z > t->z); j--)
            WidgetList[j+1] = WidgetList[j];

        /* вставка */
        WidgetList[j+1] = t;
    }
}
