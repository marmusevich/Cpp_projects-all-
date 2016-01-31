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
