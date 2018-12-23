#include <stdio.h>

struct st{
    int a;
    int b;
};

int main(int argc, char* argv[])
{
    struct st sst;
    sst.a = 10;
    sst.b = 20;
    printf("struct content is: %d, %d\n", sst.a, sst.b);
    return 0;
}
