#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

int main()
{
    int i;
    i = 0;
    do
    {
        --i;
        printf("%d\n", i);
        i++;
    }
    while(i >= 0);

    return 0;
}

/*
#include <stdio.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 20

enum {N=1,E=4,S=2,W=8};
int DX[9];
int DY[9];
int OPPOSITE[9];

int carve_passage_from(int cx, int cy, int *grid[]);
int shuffle_array(int *array, int size);

int main(int argc, char *argv[], char **envp)
{
    int x, y;
    OPPOSITE[N] = S;
    OPPOSITE[E] = W;
    OPPOSITE[S] = N;
    OPPOSITE[W] = E;

    DX[N] = 0;
    DX[E] = 1;
    DX[S] = 0;
    DX[W] = -1;

    DY[N] = -1;
    DY[E] = 0;
    DY[S] = 1;
    DY[W] = 0;
    int grid[WIDTH][HEIGHT];
    //** Seed the random generator
    srand((unsigned int)time((time_t *)NULL));

    memset(&grid[0], 0, sizeof(grid));

    carve_passage(0, 0, grid);

    printf("Display the grid\n");
    //** Display the grid
    printf(" ");
    for(x = 0; x < (WIDTH * 2); x++)
    {
        printf("_");
    }
    printf("\n");

    for(y = 0; y < HEIGHT; y++)
    {
        printf("|");
        for(x = 0; x < WIDTH; x++)
        {
            printf( ((grid[x][y] & S) !=  0)?" ":"_");
            if((grid[x][y] & E) != 0)
            {
                printf((( (grid[x][y] | grid[x + 1][y]) & S) != 0) ?" ":"_");
            }
            else
            {
                printf("|");
            }
        }
        printf("\n");
    }
}

int shuffle_array(int *array, int size)
{
    int i;

    for( i=0; i<(size - 1); i++)
    {
        int r = i + (rand() % (size - i));
        int temp = array[i];
        array[i] = array[r];
        array[r] = temp;
    }
}

int carve_passage(int cx, int cy, int *grid[WIDTH][HEIGHT])
{

    int dx, dy, nx, ny;
    int directions[4] = {N, E, S, W};

    //shuffle the direction array
    shuffle_array(directions, 4);

    int i;
    for(i = 0; i < 4; i++)
    {
        printf("Direction: %d\n", directions[i]);
    }
    //iterates through the direction then test if the cell in that direction is valid and
    //within the bounds of the maze
    for(i = 0; i < 4; i++)
    {
        dx = DX[directions[i]];
        dy = DY[directions[i]];
        printf("Check direction=x:y - %d=%d:%d\n", directions[i], dx, dy);
        // check if the cell is valid
        nx = cx + dx;
        ny = cy + dy;
        // check if we are on valid grid
        if ( ((nx < WIDTH) & (nx >= 0)) & ((ny < HEIGHT) & (ny >= 0)) )
        {
            //check if grid is not visited
            if (grid[nx][ny] == 0)
            {
                printf("Valid cell x:y %d:%d\n", nx, ny);
                grid[cx][cy] = (int)((int)grid[cx][cy] | (int)directions[i]);
                grid[nx][ny] = (int)((int)grid[nx][ny] | (int)OPPOSITE[directions[i]]);
                carve_passage(nx, ny, grid);
            }
        }

    }
}
*/
