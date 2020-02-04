// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_keyboard.h>
#include <random>
#include <ctime>
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
const int16_t WIDTH = 1000, HEIGHT = 1000, searchRange = 4;
const uint8_t stayAliveSize = 41;

uint8_t stayAlive[stayAliveSize] = { 41,42,43,44,45,46,47,48,49,50,
                                     51,52,53,54,55,56,57,58,59,60,
                                     61,62,63,64,65,66,67,68,69,70,
                                     71,72,73,74,75,76,77,78,79,80,81 };

uint8_t birth[stayAliveSize] = { 41,42,43,44,45,46,47,48,49,50,
                                     51,52,53,54,55,56,57,58,59,60,
                                     61,62,63,64,65,66,67,68,69,70,
                                     71,72,73,74,75,76,77,78,79,80,81 };

const int FPS = 120;
const int frameDelay = 1000 / FPS;
Uint32 frameStart;
int frameTime;

int yy = 0, xx=0, al = 0;
int ylim = HEIGHT - searchRange-1;      
int xlim = WIDTH - searchRange-1;
bool field[HEIGHT][WIDTH];   // Initialize space for grid
int i, j = 0;
bool NextField[HEIGHT][WIDTH];


/*
    Create window and drawing surface layer
 */
SDL_Surface* imageSurface = NULL;
SDL_Surface* windowSurface = NULL;

/*Function Prototypes*/
void Initial_array();
void Draw_grid(int& x, int& y, SDL_Rect& R);
bool Value_in_array(int val, uint8_t arr[]);

int main(int argc, char *argv[])
{
    //====================InitializationStart==================================//
    

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
        HEIGHT, WIDTH,
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

    SDL_Rect dstrect;
    dstrect.x = 0;
    dstrect.y = 0;
    dstrect.w = 0;
    dstrect.h = 0;
    //====================InitializationEnd==================================//
    /*Initial state seed*/
    
    Initial_array();
    /*
    field[499][499] = true;
    field[500][499] = true;
    field[501][499] = true;
    field[499][500] = true;
    field[500][500] = false;
    field[501][500] = true;
    field[499][501] = true;
    field[500][501] = true;
    field[501][501] = true;
    */
    Draw_grid(dstrect.x, dstrect.y, dstrect);

    
    //==============================GameLoopStart==========================================//
    while (true)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (SDL_QUIT == windowEvent.type)
                break;
        }
        frameStart = SDL_GetTicks();
        

        SDL_FillRect(windowSurface, NULL, 0x000000);
        
        for (i = searchRange; i <= ylim; i++)
        {
            for (j = searchRange; j <= xlim; j++)
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
                    if (Value_in_array(al, stayAlive) && field[i][j] == 1)
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
                    if (Value_in_array(al, stayAlive) && field[i][j] == 1)
                        NextField[i][j] = 1;
                    else if (Value_in_array(al, birth) && field[i][j] == 0)
                        NextField[i][j] = 1;
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
                    if (Value_in_array(al, stayAlive) && field[i][j] == 1)
                        NextField[i][j] = 1;
                    else if (Value_in_array(al, birth) && field[i][j] == 0)
                        NextField[i][j] = 1;
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
                    if (Value_in_array(al, stayAlive) && field[i][j] == 1)
                        NextField[i][j] = 1;
                    else if (Value_in_array(al, birth) && field[i][j] == 0)
                        NextField[i][j] = 1;
                    else
                        NextField[i][j] = 0;
                    //------------------------------//
                    //printf("case4: x: %d , y: %d, Alive Neighbors: %d, Alive in Next Generation: %d\n",j,i,al,NextField[i][j]);
                }
                else if (j > 0 && j < xlim && i > 0 && i < ylim)
                {
                    for (yy = -searchRange; yy <= searchRange; yy++)
                    {
                        for (xx = -searchRange; xx <= searchRange; xx++)
                        {
                            /*if (!(i + yy == i && j + xx == j))
                            {
                            }
                            */
                                if (field[i + yy][j + xx] == 1)
                                    al++;
                            
                        }
                    }
                    //----------------------------------//
                    if (Value_in_array(al, stayAlive) && field[i][j] == 1)
                        NextField[i][j] = 1;
                    else if (Value_in_array(al, birth) && field[i][j] == 0)
                        NextField[i][j] = 1;
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
                    if (Value_in_array(al, stayAlive) && field[i][j] == 1)
                        NextField[i][j] = 1;
                    else if (Value_in_array(al, birth) && field[i][j] == 0)
                        NextField[i][j] = 1;
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
                    if (Value_in_array(al, stayAlive) && field[i][j] == 1)
                        NextField[i][j] = 1;
                    else if (Value_in_array(al, birth) && field[i][j] == 0)
                        NextField[i][j] = 1;
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
                    if (Value_in_array(al, stayAlive) && field[i][j] == 1)
                        NextField[i][j] = 1;
                    else if (Value_in_array(al, birth) && field[i][j] == 0)
                        NextField[i][j] = 1;
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
                    if (Value_in_array(al, stayAlive) && field[i][j] == 1)
                        NextField[i][j] = 1;
                    else if (Value_in_array(al, birth) && field[i][j] == 0)
                        NextField[i][j] = 1;
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
                field[i][j] = NextField[i][j];
            }
        }
        Draw_grid(dstrect.x, dstrect.y, dstrect);
        
        SDL_UpdateWindowSurface(window);  

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
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

void Initial_array()
{
    srand(time(0));
    for (i = 0; i <= HEIGHT - 1; i++)
    {
        
        for (j = 0; j <= WIDTH - 1; j++)
        {
           field[i][j] = !(rand() % 3 && rand() % 4);
        }
    }
}
void Draw_grid(int& x, int& y, SDL_Rect& R)
{
    for (i = 0; i <= HEIGHT - 1; i++)
    {
        for (j = 0; j <= WIDTH - 1; j++)
        {   
            if (field[i][j] > 0)
            {
                x = i;
                y = j;
                SDL_BlitSurface(imageSurface, NULL, windowSurface, &R);
            }

        }
    }
}
bool Value_in_array(int val, uint8_t arr[])
{
    int k;
    
    for (k = 0; k < stayAliveSize; k++)
    {
        if (arr[k] == val)
            return true;
    }
    return false;
}