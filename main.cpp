#include <iostream>

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <string>

/*using namespace std;

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

}*/

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

SDL_Texture* LoadImage(std::string file)
{
    SDL_Surface *loadedImage = NULL;
    SDL_Texture *texture = NULL;
    loadedImage = SDL_LoadBMP(file.c_str());
    if (loadedImage != NULL)
    {
        texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
        SDL_FreeSurface(loadedImage);
    }
    else
        std::cout << SDL_GetError() << std::endl;
    return texture;
}
void ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend)
{
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
    SDL_RenderCopy(rend, tex, NULL, &pos);
}
int main(int argc, char** argv)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        std::cout <<SDL_GetError() << std::endl;
        return 1;
    }
    window = SDL_CreateWindow("Lesson 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 2;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 3;
    }

    SDL_Texture *background = NULL, *image = NULL;
    background = LoadImage("background.bmp");
    image = LoadImage("image.bmp");
    if(background == NULL || image == NULL)
        return 4;
    SDL_RenderClear(renderer);

    int bW, bH;
    SDL_QueryTexture(background, NULL, NULL, &bW, &bH);
    ApplySurface(0, 0, background, renderer);
    ApplySurface(bW, 0, background, renderer);
    ApplySurface(0, bH, background, renderer);
    ApplySurface(bW, bH, background, renderer);

    int iW, iH;
    SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
    int x =SCREEN_WIDTH / 2 - iW / 2;
    int y = SCREEN_HEIGHT / 2 -iH /2;
    ApplySurface(x, y, image, renderer);

    SDL_RenderPresent(renderer);
    SDL_Delay(2000);

    SDL_DestroyTexture(background);
    SDL_DestroyTexture(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}











