#include <stdio.h>

int main(int argc, char* argv[])
{
    FILE* file;
    char buf[1024] = {0,};

    file = fopen("1.txt", "a+");

    fwrite("hello, world!", 1, 13, file);
    rewind(file);
    fread(buf,1,26,file);

    fclose(file);

    printf("buf:%s\n",buf);
    return 0;
}
