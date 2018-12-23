#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int *a, *b;
    a = (int*)malloc(sizeof(int));
    b = (int*)malloc(sizeof(int));

    *a = 1;
    *b = 2;
    int c[3] = {0,1,2};

    printf("addr of a:%p, %p, %d\n", &a, a, *a);
    printf("addr of b:%p, %p, %d\n", &b, b, *b);
    printf("addr of c:%p, %p, %d, %d, %d\n", &c, c, c[0], c[1], c[2]);

    return 0;
}
