// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_keyboard.h>
#include <random>
#include <time.h>
#include <stdlib.h>

/*
WIDTH = Window Width
HEIGHT = Window Height
ITERATION LMIT = The number of generations the GOL will simulate
yy = Iterator for neighboring y-coordinates
xx = Iterator for neighboring x-coordinates
al = The number of alive neighbors for a given cell
ylim = Iterator limit for grid y-coordinates
xlim = Iterator limit for grid x-coordinates
i and j = Iterators to hit every point in the grid (for every increase in 'j',
'i' will have increased by WIDTH and reset until 'j' has reached HEIGHT
*/
const int WIDTH = 1000, HEIGHT = 1000, ITERATION_LIMIT = 200;
int yy = 0, xx=0, al = 0;
int ylim = HEIGHT - 1;      
int xlim = WIDTH - 1;       
int field[HEIGHT][WIDTH];   // Initialize space for grid
int i, j = 0;               
int NextField[HEIGHT][WIDTH];
int counter = 0;
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
    //====================InitializationEnd==================================//

    SDL_Rect dstrect;
    dstrect.x = 0;
    dstrect.y = 0;
    dstrect.w = 0;
    dstrect.h = 0;
    srand(time(NULL));
    for (i = 0; i <= HEIGHT - 1; i++)
    {
        for (j = 0; j <= WIDTH - 1; j++)
        {
            field[i][j] = rand() % 3;
        }
    }
    for (i = 0; i <= HEIGHT - 1; i++)
    {
        for (j = 0; j <= WIDTH - 1; j++)
        {
            if (field[i][j] == 1)
            {
                dstrect.x = i;
                dstrect.y = j;
                SDL_BlitSurface(imageSurface, NULL, windowSurface, &dstrect);
            }
        }
    }
    
    //==============================GameLoopStart==========================================//
    while (true)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (SDL_QUIT == windowEvent.type)
                break;
        }

        SDL_FillRect(windowSurface, NULL, 0x000000);
        
        for (i = 0; i <= ylim; i++)
        {
            for (j = 0; j <= xlim; j++)
            {
                al = 0;
                if (j == 0 && i == 0)
                {
                    if (field[i + 1][j] == 1)
                        al++;
                    if (field[i + 1][j + 1] == 1)
                        al++;
                    if (field[i][j + 1] == 1)
                        al++;
                    //----------------------------------//
                    if ((al == 2 || al == 3) && field[i][j] == 1)
                        NextField[i][j] = 1;
                    else if (al == 3 && field[i][j] == 0)
                        NextField[i][j] = 1;
                    else if (al < 1)
                        NextField[i][j] = 0;
                    else
                        NextField[i][j] = 0;
                    //------------------------------//
                      //printf("case1: x: %d , y: %d, Alive Neighbors: %d, Alive in Next Generation: %d\n",j,i,al,NextField[i][j]);
                }
                else if (j > 0 && j < xlim && i == 0)
                {

                    for (yy = 0; yy <= 1; yy++)
                    {
                        for (xx = -1; xx <= 1; xx++)
                        {
                            if (!(i + yy == i && j + xx == j))
                                if (field[i + yy][j + xx] == 1)
                                    al++;
                        }
                    }
                    //----------------------------------//
                    if ((al == 2 || al == 3) && field[i][j] == 1)
                        NextField[i][j] = 1;
                    else if (al == 3 && field[i][j] == 0)
                        NextField[i][j] = 1;
                    else if (al < 1)
                        NextField[i][j] = 0;
                    else
                        NextField[i][j] = 0;
                    //------------------------------//
                    //printf("case2: x: %d , y: %d, Alive Neighbors: %d, Alive in Next Generation: %d\n",j,i,al,NextField[i][j]);
                }
                else if (j >= xlim && i == 0)
                {
                    if (field[i + 1][j] == 1)
                        al++;
                    if (field[i + 1][j - 1] == 1)
                        al++;
                    if (field[i][j - 1] == 1)
                        al++;
                    //----------------------------------//
                    if ((al == 2 || al == 3) && field[i][j] == 1)
                        NextField[i][j] = 1;
                    else if (al == 3 && field[i][j] == 0)
                        NextField[i][j] = 1;
                    else if (al < 1)
                        NextField[i][j] = 0;
                    else
                        NextField[i][j] = 0;
                    //------------------------------//
                    //printf("case3: x: %d , y: %d, Alive Neighbors: %d, Alive in Next Generation: %d\n",j,i,al,NextField[i][j]);
                }
                else if (j == 0 && i > 0 && i < ylim)
                {
                    for (yy = -1; yy <= 1; yy++)
                    {
                        for (xx = 0; xx <= 1; xx++)
                        {
                            if (field[i + yy][j + xx] == 1)
                                al++;
                        }
                    }
                    //----------------------------------//
                    if ((al == 2 || al == 3) && field[i][j] == 1)
                        NextField[i][j] = 1;
                    else if (al == 3 && field[i][j] == 0)
                        NextField[i][j] = 1;
                    else if (al < 1)
                        NextField[i][j] = 0;
                    else
                        NextField[i][j] = 0;
                    //------------------------------//
                    //printf("case4: x: %d , y: %d, Alive Neighbors: %d, Alive in Next Generation: %d\n",j,i,al,NextField[i][j]);
                }
                else if (j > 0 && j < xlim && i > 0 && i < ylim)
                {
                    for (yy = -1; yy <= 1; yy++)
                    {
                        for (xx = -1; xx <= 1; xx++)
                        {
                            if (!(i + yy == i && j + xx == j))
                            {
                                if (field[i + yy][j + xx] == 1)
                                    al++;
                            }
                        }
                    }
                    //----------------------------------//
                    if ((al == 2 || al == 3) && field[i][j] == 1)
                        NextField[i][j] = 1;
                    else if (al == 3 && field[i][j] == 0)
                        NextField[i][j] = 1;
                    else if (al < 1)
                        NextField[i][j] = 0;
                    else
                        NextField[i][j] = 0;
                    //------------------------------//
                    //printf("case5: x: %d , y: %d, Alive Neighbors: %d, Alive in Next Generation: %d\n",j,i,al,NextField[i][j]);
                }
                else if (j >= xlim && i > 0 && i < ylim)
                {
                    for (yy = -1; yy <= 1; yy++)
                    {
                        for (xx = -1; xx <= 0; xx++)
                        {
                            if (field[i + yy][j + xx] == 1)
                                al++;
                        }
                    }
                    //----------------------------------//
                    if ((al == 2 || al == 3) && field[i][j] == 1)
                        NextField[i][j] = 1;
                    else if (al == 3 && field[i][j] == 0)
                        NextField[i][j] = 1;
                    else if (al < 1)
                        NextField[i][j] = 0;
                    else
                        NextField[i][j] = 0;
                    //------------------------------//
                    //printf("case6: x: %d , y: %d, Alive Neighbors: %d, Alive in Next Generation: %d\n",j,i,al,NextField[i][j]);
                }
                else if (j == 0 && i >= ylim)
                {
                    if (field[i - 1][j] == 1)
                        al++;
                    if (field[i - 1][j + 1] == 1)
                        al++;
                    if (field[i][j + 1] == 1)
                        al++;
                    //----------------------------------//
                    if ((al == 2 || al == 3) && field[i][j] == 1)
                        NextField[i][j] = 1;
                    else if (al == 3 && field[i][j] == 0)
                        NextField[i][j] = 1;
                    else if (al < 1)
                        NextField[i][j] = 0;
                    else
                        NextField[i][j] = 0;
                    //------------------------------//
                    //printf("case7: x: %d , y: %d, Alive Neighbors: %d, Alive in Next Generation: %d\n",j,i,al,NextField[i][j]);
                }
                else if (j > 0 && j < xlim && i >= ylim)
                {
                    for (yy = -1; yy <= 0; yy++)
                    {
                        for (xx = -1; xx <= 1; xx++)
                        {
                            if (i + yy != i && j + xx != j)
                                if (field[i + yy][j + xx] == 1)
                                    al++;
                        }
                    }
                    //----------------------------------//
                    if ((al == 2 || al == 3) && field[i][j] == 1)
                        NextField[i][j] = 1;
                    else if (al == 3 && field[i][j] == 0)
                        NextField[i][j] = 1;
                    else if (al < 1)
                        NextField[i][j] = 0;
                    else
                        NextField[i][j] = 0;
                    //------------------------------//
                    //printf("case8: x: %d , y: %d, Alive Neighbors: %d, Alive in Next Generation: %d\n",j,i,al,NextField[i][j]);
                }
                else if (j >= xlim && i >= ylim)
                {
                    if (field[i][j - 1] == 1)
                        al++;
                    if (field[i - 1][j - 1] == 1)
                        al++;
                    if (field[i - 1][j] == 1)
                        al++;
                    //----------------------------------//
                    if ((al == 2 || al == 3) && field[i][j] == 1)
                        NextField[i][j] = 1;
                    else if (al == 3 && field[i][j] == 0)
                        NextField[i][j] = 1;
                    else if (al < 1)
                        NextField[i][j] = 0;
                    else
                        NextField[i][j] = 0;
                    //------------------------------//
                    //printf("case9: x: %d , y: %d, Alive Neighbors: %d, Alive in Next Generation: %d\n",j,i,al,NextField[i][j]);
                }
                else
                {
                    //printf("case?: x: %d , y: %d\n",j,i);
                }
            }
        }

        for (i = 0; i <= HEIGHT - 1; i++)
        {
            for (j = 0; j <= WIDTH - 1; j++)
            {
                if (NextField[i][j] == 1)
                {
                    dstrect.x = i;
                    dstrect.y = j;
                    SDL_BlitSurface(imageSurface, NULL, windowSurface, &dstrect);
                }
            }
        }

        for (i = 0; i <= HEIGHT - 1; i++)
        {
            for (j = 0; j <= WIDTH - 1; j++)
            {
                field[i][j] = NextField[i][j];
            }
        }
        std::cout << "Iteration" << std::endl;
        //SDL_Delay(16);
        //SDL_FillRect(windowSurface, NULL, 0x000000);
        //SDL_BlitSurface(imageSurface, NULL, windowSurface, &dstrect);
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
