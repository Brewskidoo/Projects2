// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_keyboard.h>
#include <random>

/*
WIDTH = Window Width
HEIGHT = Window Height
ITERATION LMIT = The number of generations the GOL will simulate
yy = Iterator for neighboring y-coordinates
xx = Iterator for neighboring x-coordinates
al = The number of alive neighbors for a given cell
*/
const int WIDTH = 500, HEIGHT = 500, ITERATION_LIMIT = 200;
int yy = 0, xx=0, al = 0;

int main(int argc, char *argv[])
{
    //====================InitializationStart==================================//
    /*
    Create window and drawing surface layer
    */
    SDL_Surface *imageSurface = NULL;
    SDL_Surface *windowSurface = NULL;

    /*
    Initialize all subsystems for use in the program
    */
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL could not initialize! SDL Error:" << SDL_GetError() << std::endl;
    }
    
    SDL_Window* window = SDL_CreateWindow("GOL",
                                            SDL_WINDOWPOS_UNDEFINED,
                                            SDL_WINDOWPOS_UNDEFINED,
                                            WIDTH, HEIGHT,
                                            SDL_WINDOW_ALLOW_HIGHDPI);
    windowSurface = SDL_GetWindowSurface(window);
    //====================InitializationEnd==================================//
    

    if (NULL == window)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cout << "Failed to initialize SDL_image for PNG files: " << IMG_GetError() << std::endl;
    }
    
    SDL_Event windowEvent;

    imageSurface = IMG_Load("GreenSquare.png");
    if (NULL == imageSurface)
    {
        std::cout << "SDL Could not load image! SDL Error: " << SDL_GetError() << std::endl;
    }

    SDL_Rect dstrect;
    dstrect.x = 0;
    dstrect.y = 0;
    dstrect.w = 0;
    dstrect.h = 0;
    bool goingRight = true;
    int speed = 3;
    int offset = 0;
    //==============================GameLoopStart==========================================//
    while (true)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (SDL_QUIT == windowEvent.type)
                break;
        }
    
       
        SDL_FillRect(windowSurface, NULL, 0x000000);
        SDL_BlitSurface(imageSurface, NULL, windowSurface, &dstrect);
        SDL_UpdateWindowSurface(window);  
    }
    //==============================GameLoopEnd==========================================//
    SDL_FreeSurface(imageSurface);
    SDL_FreeSurface(windowSurface);
    imageSurface = NULL;
    windowSurface = NULL;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
