#include <stdio.h>

int main(int argc, char* argv[])
{
   int a =10;
   int b = 20;

   int c = a +b;
   int d = c-b;
   int e = 5%4;

    printf("c=%d, d=%d, e=%d\n",c, d, e);
    if(a>b){
        printf("a>b\n"); 
    }else{
        printf("a<b\n");
    }
    return 0;
}
