#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    const int TICKS_PER_SECOND = 25;
    const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;

    int fps=0;
    DWORD pred_game_tick = GetTickCount();
    DWORD qurent_tiks = 0;
    DWORD tiks_for_fps = GetTickCount();

    DWORD a1 = pred_game_tick;

    bool game_is_running = true;
    while( game_is_running ) {
        qurent_tiks = GetTickCount();
        //update_game
        if(qurent_tiks - pred_game_tick  > SKIP_TICKS )
        {
            //update_game();
            cout << "   update! D = " <<(qurent_tiks - pred_game_tick) << endl;
            Sleep(5);
            pred_game_tick = qurent_tiks;
        }


        //Displey game
        {
            cout << "       Displey! DD = " <<(qurent_tiks - pred_game_tick) << endl;
            Sleep(5);
        }
        // FPS
        {
            fps++;
            if(qurent_tiks - tiks_for_fps >1000) //1 sec
            {
                cout << "fps= " <<fps << endl;
                tiks_for_fps = qurent_tiks;
                fps=0;
            }
        }

        //exit
        if(qurent_tiks-a1 >2000) //2 sec
            game_is_running = false;
    }

    return 0;
}
