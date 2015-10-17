//#include <stdio.h>
//#include <conio.h>
//#include <stdlib.h>
//
//const int size = 20;
//const int fullfill = 100; // in %
//const int wallshort= 50; // in %
//char m[size+1][size+1];
//// Random generator
//int r[2][size/2*size/2];
//int h; // How many number in array;
//
//
//void initrandom ()
//{
//    int j=0;
//    for (int y=2; y<size; y+=2)
//        for (int x=2; x< size; x+=2)
//        {
//            r[0][j] = x;
//            r[1][j] = y;
//            j++;
//        }
//    h=j-1;
//}
//
//int getrandom(int &x, int &y)
//{
//    int i = random (h);
//    x = r[0][i];
//    y = r[1][i];
//    r[0][i] = r[0][h];
//    r[1][i] = r[1][h];
//    return h--;
//}
//
//// View labirint on screen
//void view()
//{
//    for (int y=0; y<=size; y++)
//        for (int x=0; x<=size; x++)
//        {
//            gotoxy (x*2+1,y+1);
//            if (m[y][x]==0) cprintf ("..");
//            if (m[y][x]==1) cprintf ("__");
//        }
//}
//
//int main1(void)
//{
//    printf ("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
//    printf ("Labirint generator");
//    // Clear labirint
//    for (int c = 0; c < size*size; c++) ((char *)m)[c] = 0;
//    // Make border
//    for (int i = 0; i <= size; i++)
//    {
//        m[0][i] = 1;
//        m[size][i] = 1;
//        m[i][0] = 1;
//        m[i][size] = 1;
//    }
//    view ();
//    initrandom();
//    int startx, starty;
//    while (getrandom (startx, starty))
//    {
//        if (m[starty][startx]==1) continue;
//        if (random (100) > fullfill) continue;
//        int sx=0,sy=0;
//        do
//        {
//            sx=random (3)-1;
//            sy=random (3)-1;
//        }
//        while (sx==0 && sy==0 || sx!=0 && sy!=0);   //sx==0 and sy==0
//        while (m[starty][startx]==0)
//        {
//            if (random (100) > wallshort)
//            {
//                m[starty][startx] = 1;
//                break;
//            }
//            m[starty][startx] = 1;
//            startx +=sx;
//            starty+=sy;
//            m[starty][startx] = 1;
//            startx +=sx;
//            starty+=sy;
//        }
//    }
//    view();
//    return 0;
//}
