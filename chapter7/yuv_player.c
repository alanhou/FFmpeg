#include <stdio.h>
#include <string.h>

#include <SDL.h>

//event message
#define REFRESH_EVENT  (SDL_USEREVENT + 1)
#define QUIT_EVENT  (SDL_USEREVENT + 2)

int thread_exit=0;

int refresh_video_timer(void *udata){

    thread_exit=0;

    while (!thread_exit) {
        SDL_Event event;
        event.type = REFRESH_EVENT;
        SDL_PushEvent(&event);
        SDL_Delay(40);
    }

    thread_exit=0;

    //push quit event
    SDL_Event event;
    event.type = QUIT_EVENT;
    SDL_PushEvent(&event);

    return 0;
}

int main(int argc, char* argv[])
{

    FILE *video_fd = NULL;

    SDL_Event event;
    SDL_Rect rect;

    Uint32 pixformat = 0;

    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;

    SDL_Thread *timer_thread = NULL;

    int w_width = 608, w_height = 368;
    const int video_width = 608, video_height = 368;
    
    Uint8 *video_pos = NULL;
    Uint8 *video_end = NULL;

    unsigned int remain_len = 0;
    size_t video_buff_len = 0;
    size_t blank_space_len = 0;
    Uint8 *video_buf = NULL;

    const char *path = "1.yuv";

    const unsigned int yuv_frame_len = video_width * video_height * 12 / 8;
    unsigned int tmp_yuv_frame_len = yuv_frame_len;

    if (yuv_frame_len & 0xF) {
        tmp_yuv_frame_len = (yuv_frame_len & 0xFFF0) + 0x10;
    }

    //initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO)) {
        fprintf( stderr, "Could not initialize SDL - %s\n", SDL_GetError());
        return -1;
    }

    //creat window from SDL
    win = SDL_CreateWindow("YUV Player",
                           SDL_WINDOWPOS_UNDEFINED,
                           SDL_WINDOWPOS_UNDEFINED,
                           w_width, w_height,
                           SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    if(!win) {
        fprintf(stderr, "Failed to create window, %s\n",SDL_GetError());
        goto __FAIL;
    }

    renderer = SDL_CreateRenderer(win, -1, 0);

    //IYUV: Y + U + V  (3 planes)
    //YV12: Y + V + U  (3 planes)
    pixformat= SDL_PIXELFORMAT_IYUV;

//create texture for render
    texture = SDL_CreateTexture(renderer,
                                pixformat,
                                SDL_TEXTUREACCESS_STREAMING,
                                video_width,
                                video_height);

    //alloc space
    video_buf = (Uint8*)malloc(tmp_yuv_frame_len);
    if(!video_buf){
        fprintf(stderr, "Failed to alloce yuv frame space!\n");
        goto __FAIL;
    }

    //open yuv file
    video_fd = fopen(path, "r");
    if( !video_fd ){
        fprintf(stderr, "Failed to open yuv file\n");
        goto __FAIL;
    }


    if((video_buff_len = fread(video_buf, 1, yuv_frame_len, video_fd)) <= 0){
        fprintf(stderr, "Failed to read data from yuv file!\n");
        goto __FAIL;
    }

    //set video positon
    video_pos = video_buf;
    /*
    video_end = video_buf + video_buff_len;
    blank_space_len = BLOCK_SIZE - video_buff_len;
    */

    timer_thread = SDL_CreateThread(refresh_video_timer,
                                    NULL,
                                    NULL);

 do {

        //Wait
        SDL_WaitEvent(&event);
        if(event.type==REFRESH_EVENT){

            SDL_UpdateTexture( texture, NULL, video_pos, video_width);

            //FIX: If window is resize
            rect.x = 0;
            rect.y = 0;
            rect.w = w_width;
            rect.h = w_height;

            SDL_RenderClear( renderer );
            SDL_RenderCopy( renderer, texture, NULL, &rect);
            SDL_RenderPresent( renderer );

            //read block data
            if((video_buff_len = fread(video_buf, 1, yuv_frame_len, video_fd)) <= 0){
                thread_exit =1;
                continue;
            }
            //memset(video_buf+(video_width*video_height), 0, (video_width*video_height)/2);

        }else if(event.type==SDL_WINDOWEVENT){
            //If Resize
            SDL_GetWindowSize(win, &w_width, &w_height);
        }else if(event.type==SDL_QUIT){
            thread_exit=1;
        }else if(event.type==QUIT_EVENT){
            break;
        }
    }while ( 1 );

__FAIL:

    if(video_buf){
        free(video_buf);
    }

    //close file
    if(video_fd){
        fclose(video_fd);
    }

    SDL_Quit();

    return 0;

}
