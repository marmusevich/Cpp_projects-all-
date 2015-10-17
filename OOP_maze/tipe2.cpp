//#include <stdio.h>
//#include <stdlib.h>
//#include <malloc.h>
//#include <conio.h>
//
//#include <windows.h>
//#include <time.h>
//#define cls() (printf("\n\n\n\n\n"))
//HANDLE hdl = 0;
//
//#define makeeven(_num)(_num & 0xFE)
//#define myrand(_num)(_num?rand()%_num:0)
//#define myevenrand(_num)(myrand(_num)& 0xFE) //obtain even number in the given range by clearing first bit
//#define evenmax(_num)(_num & 0xFE)
//#define evenaverage(_num)((evenmax(_num)/2)& 0xFE)
//#define myoddrand(_num)(myrand(_num)| 0x01)
//#define randomize()(srand( (unsigned)time( NULL ) ))
//
//void display(int size,int w);                   //displays labirinth
//void createborder(int size,int w,int h);        //creates lab border
//void createdoors(int size, int width);
//void cleanup(void);
//int getrandom(int width,int height,int *x);
//int getdirection(int width);
//int evenbetween(int n1, int n2);
//int oddbetween(int n1, int n2);
//
//int *a;                                         //pointer to pseudo 2 dimentional array holding labirinth
//int cycle;
//
//int main(int argc, char *argv[])
//{
//    int *p,size,length,h,w;
//
//    h = makeeven(40);
//    w = makeeven(50);
//
//    length = 55; // 1 - 100
//
//    length = length == 0?70:length;
//    ++h;
//    ++w;
//    size = h * w;
//
//    /* allocate our array to hold lab. data*/
//    a = (int *)calloc(size, sizeof(int));
//
//    if(a != NULL)
//        printf("\n\t%d bytes of memory allocated\n",size * sizeof(int));
//    else
//    {
//        printf("Memory allocation failed\n");
//        free(a);
//        return 1;
//    }
//
//    printf("\n\tprinting labyrinth, dimentions %d x %d...\n\n\t",w-1,h-1);
//
////собственно построение
//
//    createborder(size,w,h);
//    createdoors(size,w);
//
//    /*set random seed*/
//    randomize();
//
//    int x = 0,z = 0;
//    cycle+= size + size/2;
//    while(getrandom(w,h,&x) > 0)
//    {
//
//        if(a[x] == 1) continue;
//        z = getdirection(w);
//        //printf("%5d",x);
//
//        /*here we're building the walls, creating derived points*/
//        do
//        {
//            if(a[x] == 0) a[x] = 1;
//            x += z;
//            if(myrand(100) > length) break;
//        }
//        while(a[x] == 0 );
//    }
//
//    display(size,w);
//    cleanup();
//
//    return 0;
//}
//
//void createborder(int size,int w,int h)
//{
//    int *p = a;
//    for(p; p - a < size; p++)
//    {
//        if((p - a) < w ||          /* defines first row*/
//                (p - a)%w == 0 ||          /* defines left side*/
//                (p - a)%w == w - 1 ||      /* defines right side*/
//                (p - a) > w * (h - 1))     /*   defines bottom*/
//            *p = 1;
//    }
//}
//
//void createdoors(int size, int width)
//{
//    int t;
//    do
//    {
//        t = oddbetween(0,width);
//    }
//    while(t == 0 || t == width);
//    a[t] = 0x2F;
//    do
//    {
//        t = oddbetween(size - width, size);
//    }
//    while(t == size || a[t] == 0);
//    a[t] = 0x2F;
//}
//
//void display(int size,int w)
//{
//    int *p = a,row = 0;
//    char ch = 32;
////    printf("\n\n\t%05d",0x0);
//    printf("\n\n");
//    for(p; p - a < size; p++)
//    {
//        if((p - a) > 0 && (p - a)%w == 0)      //print another row
//        {
//            printf("\n");
////            if((p - a)%2 == 0) printf("\n\t%05d",row);
////            else printf("\n\t%5c",32);
//        }
//        //printf( " %c",(char)*p);
//        ch = *p == 1? 'O' : 32;
//        printf ("%c",ch);
//        row++;
//    }
//    printf("\n");
//}
//
///*this function defines in which direction we need to move while building the wall*/
//inline int getdirection(int width)
//{
//    int z = myrand(4);
//    return (z == 0?-1: z == 1?1: z == 2? width: -width);
//}
//
//inline int oddbetween(int n1, int n2)
//{
//    int t;
//    return (t = myoddrand(n2)) > n1?t:oddbetween(n1,n2);
//}
//
//inline int evenbetween(int n1, int n2)
//{
//    int t;
//    return (t = myevenrand(n2)) > n1?t:evenbetween(n1,n2);
//}
//
//int getrandom(int width,int height,int *x)
//{
//    int row,col;
//    row = evenbetween(0,height);
//    col = evenbetween(0,width);
//    *x = width * row + col;
//    /* here we prevent generation of number that would produce odd column value*/
//    if((*x%width)%2 != 0)
//    {
//        //printf("\n\tratio = %2d",(*x%width)%2); //getch();
//        getrandom(width,height,x);
//    }
////  printf("\n\trow - %3d , col - %3d x = %3d width = %3d cycle = %4d", row,col,*x,width,cycle);
//    return cycle--;
//}
//
//
//
//void cleanup(void)
//{
//
//    free(a);
//}
//
