#include <iostream>
#include <stdio.h>
#include <string>
#include <SDL.h>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *argv[])
{
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize. SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    else
    {
        window = SDL_CreateWindow( "ayy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL)
        {
            printf("Window could not be created. SDL_Error: %s\n", SDL_GetError());
            return 1;
        }
        else
        {
            screenSurface = SDL_GetWindowSurface(window);
            SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (ren == NULL)
            {
                SDL_DestroyWindow(window);
                printf("SDL_CreateRenderer Error: %s\n",SDL_GetError());
                SDL_Quit();
                return 1;
            }
            SDL_Surface *bmp = SDL_LoadBMP((string(SDL_GetBasePath()) + string("\\about5.bmp")).c_str());
            if (bmp == NULL)
            {
                SDL_DestroyRenderer(ren);
                SDL_DestroyWindow(window);
                printf("SDL_LoadBMP Error: %s\n",SDL_GetError());
                SDL_Quit();
                return 1;
            }
            SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
            if (tex == NULL)
            {
                SDL_DestroyRenderer(ren);
                SDL_DestroyWindow(window);
                printf("SDL_CreateTextureFromSurface Error: %s\n",SDL_GetError());
                SDL_Quit();
                return 1;
            }
            SDL_FreeSurface(bmp);
            for (int i = 0; i < 3; ++i)
            {
                //First clear the renderer
                SDL_RenderClear(ren);
                //Draw the texture
                SDL_RenderCopy(ren, tex, NULL, NULL);
                //Update the screen
                SDL_RenderPresent(ren);
                //Take a quick break after all that hard work
                SDL_Delay(1000);
            }
        }
    }

    SDL_DestroyWindow( window );
    SDL_Quit();

    return 0;
}
