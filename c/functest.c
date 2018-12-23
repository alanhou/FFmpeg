#include <stdio.h>

int sum(int a, int b)
{
    return(a+b);
}

int sub(int a, int b){
    return (a-b);
}

void printinfo(){
    printf("This is a function test on adding numbers:\n");
}

int main(int argc, char* argv[])
{
    int result;
    int r;
    int(*f)(int, int);
    printinfo();

    f = sum;

    result = f(3,5);
    printf("3+5=%d\n",result);

    f = sub;
    r = f(result,3);
    printf("8-3=%d\n",r);
    return 0;
}

