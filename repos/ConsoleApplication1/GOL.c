
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

const ITERATION = 200;
const  x = 40;         // Width of grid
const  y = 20;         // Height of grid

int yy = 0;         // Iterator for neighboring y-coordinates
int xx = 0;         // Iterator for neighboring x-coordinates
int letter_array[2] = { 0,1 }; // 0 for dead, 1 for alive
int al = 0;         // Number of neighboring alive cells

int main(void)
{
    int ylim = y - 1;        // Iterator limit for grid y-coordinates
    int xlim = x - 1;        // Iterator limit for grid x-coordinates
    int field[y][x];         // Initialize space for grid
    int i, j = 0;            // Iterator to hit every point in the grid
    /*
    for(i=0;i<=y-1;i++) // Initialize array to all zeros
    {
      for(j=0;j<=x-1;j++)
      {
        field[i][j] = letter_array[0];
      }
    }
    field[2][1] = letter_array[1];
    field[2][2] = letter_array[1];
    field[2][3] = letter_array[1];
    */

    srand(time(NULL));// Seed for random values
    for (i = 0; i <= y - 1; i++)
    {
        for (j = 0; j <= x - 1; j++)
        {
            field[i][j] = letter_array[rand() % 2];
        }
    }

    for (i = 0; i <= ylim; i++) // print out array
    {
        for (j = 0; j <= xlim; j++)
        {
            printf("%d", field[i][j]);
        }
        printf("\n");
    }

    //Copy Array
    int NextField[y][x];
    int counter = 0;

    while (counter < ITERATION)
    {
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


        for (i = 0; i <= y - 1; i++)
        {
            for (j = 0; j <= x - 1; j++)
            {
                field[i][j] = NextField[i][j];
            }
        }
        system("cls");
        for (i = 0; i <= y - 1; i++)
        {
            for (j = 0; j <= x - 1; j++)
            {
                printf("%d", field[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        sleep(1);

        counter++;
    }

    return 0;
}
