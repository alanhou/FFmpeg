#include <libavformat/avformat.h>

/*
 命令行：clang -g -o ffmpeg_del ffmpeg_file.c `pkg-config --libs libavformat`
*/

int main(int argc, char* agrv[])
{
    int ret;
    char str[] = "./mytestfile.txt";
    ret = avpriv_io_move("111.txt", "222.txt");
    if(ret < 0){
        av_log(NULL, AV_LOG_ERROR, "Failed to rename file.\n");
        return -1;
    }
    av_log(NULL, AV_LOG_INFO, "Successly renamed file.\n");

    // delete url
    ret = avpriv_io_delete(str);

    if(ret < 0){
        av_log(NULL, AV_LOG_ERROR, "Failed to delete file.%s\n", str);
        return -1;
    }
    av_log(NULL, AV_LOG_INFO,"Delete %s successfully.\n",str);
    return 0;
}
