#include <iostream>

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

using namespace std;

int main(int argc, char*args[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        cout<<"SDL_Init_Eror: " << SDL_GetError() <<endl;
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480,SDL_WINDOW_SHOWN);
    if (win == NULL)
    {
        cout<<"SDL_CreateWindow Eror: "<< SDL_GetError() <<endl;
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL)
    {
        cout<<"SDL_CreateRendere Error :"<< SDL_GetError() <<endl;
        return 1;
    }

    SDL_Surface *bmp = SDL_LoadBMP("hello.bmp");
    if (bmp == NULL){
        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if (tex == NULL){
	std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
	return 1;
    }

    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, tex, NULL, NULL);
    SDL_RenderPresent(ren);

    SDL_Delay(20000);
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

}
