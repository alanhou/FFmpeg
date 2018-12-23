#include <stdio.h>

int main(int argc, char* argv[])
{
    int a=0;
    const int b = 10;

    printf("b=%d\n",b);
    printf("a=%d\n", a);

    a = 10;
    printf("a=%d\n", a);
    return a;
}
