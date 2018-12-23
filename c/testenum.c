#include <stdio.h>

enum e_type{
    red=0,
    green=20,
    blue=30
};

int main(int argc, char *argv[])
{
   enum e_type et;
   et = red;

   printf("the color is %d\n", et);

   et = blue;
   printf("the color is %d\n", et);
    return 0;
}
