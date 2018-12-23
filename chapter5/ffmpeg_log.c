#include <stdio.h>
#include <libavutil/log.h>
/*
命令行：clang -g -o ffmpeg_log ffmpeg_log.c -lavutil
*/

int main(int argc, char* argv[])
{
    av_log_set_level(AV_LOG_DEBUG);

    av_log(NULL, AV_LOG_INFO, "Hello World!%s\n","test content");
    return 0;
}
