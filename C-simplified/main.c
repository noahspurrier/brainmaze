/* Noah Spurrier (c)Copyright 1993 by Noah Spurrer
 * Submitted to CMP101 for PROGRAM #5
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
/* Need this for gcc to compile math.h properly */
#define _POSIX_SOURCE 1
#include <stdio.h>
#include <math.h>
/*#include "handy.h"*/
/*#include "maze.h"*/

/*
typedef unsigned int    UINT;
#define randomize() (srand((UINT)time( (time_t *)NULL )))
*/
#define randomize() (srand((unsigned int)time( (time_t *)NULL )))

/* #define BLOCK ((char)0xdb) */
#define BLOCK '#'
#define BLANK ' '

struct MAZE_TAG
{
    char *Uni;
    int Size;
};
typedef struct MAZE_TAG * Maze;

Maze Create_Maze (int size)
{
    Maze m;

    if ((m = (struct MAZE_TAG *) malloc (sizeof (struct MAZE_TAG)) ) == NULL)
    {
        fprintf (stderr, "Can't allocate memory, Maze.\n");
        exit (1);
    }

    if ((m->Uni = (char *) malloc (sizeof (char) * size * size) ) == NULL)
    {
        fprintf (stderr, "Can't allocate memory, Maze->Uni.\n");
        exit (1);
    }

    m->Size = size;

    return m;
}

void Destroy_Maze (Maze m)
{
    free (m->Uni);
    free (m);
}

char Maze_Get (Maze m, int x, int y)
{
    return *(m->Uni + (m->Size * y) + x);
}

void Maze_Put (Maze m, int x, int y, char c)
{
    *(m->Uni + (m->Size * y) + x) = c;
}

int  Maze_Size (Maze m)
{
    return m->Size;
}

void Print_Maze (Maze m)
{
    int x, y, size;
    int value;
    size = Maze_Size (m);
    for (x = 0; x < size; ++x)
    {
        for (y = 0; y < size; ++y)
        {
            value = Maze_Get (m,x,y);
            if (value == BLOCK)
                printf ("%s", "\033[40m#\033[0m");
            else
                printf ("%c", value);
        }
        printf ("\n");
    }
} /* End Print_Maze() */

void Random_Basic_Element (Maze m)
{
    switch (rand()%(6))
    {
        case (0):
            Maze_Put (m, 0,0,BLOCK); Maze_Put (m, 1,0,BLANK); Maze_Put (m, 2,0,BLOCK);
            Maze_Put (m, 0,1,BLOCK); Maze_Put (m, 1,1,BLANK); Maze_Put (m, 2,1,BLOCK);
            Maze_Put (m, 0,2,BLOCK); Maze_Put (m, 1,2,BLOCK); Maze_Put (m, 2,2,BLOCK);
        break;

        case (1):
            Maze_Put (m, 0,0,BLOCK); Maze_Put (m, 1,0,BLOCK); Maze_Put (m, 2,0,BLOCK);
            Maze_Put (m, 0,1,BLOCK); Maze_Put (m, 1,1,BLANK); Maze_Put (m, 2,1,BLANK);
            Maze_Put (m, 0,2,BLOCK); Maze_Put (m, 1,2,BLOCK); Maze_Put (m, 2,2,BLOCK);
        break;

        case (2):
            Maze_Put (m, 0,0,BLOCK); Maze_Put (m, 1,0,BLOCK); Maze_Put (m, 2,0,BLOCK);
            Maze_Put (m, 0,1,BLOCK); Maze_Put (m, 1,1,BLANK); Maze_Put (m, 2,1,BLOCK);
            Maze_Put (m, 0,2,BLOCK); Maze_Put (m, 1,2,BLANK); Maze_Put (m, 2,2,BLOCK);
        break;

        case (3):
            Maze_Put (m, 0,0,BLOCK); Maze_Put (m, 1,0,BLOCK); Maze_Put (m, 2,0,BLOCK);
            Maze_Put (m, 0,1,BLANK); Maze_Put (m, 1,1,BLANK); Maze_Put (m, 2,1,BLOCK);
            Maze_Put (m, 0,2,BLOCK); Maze_Put (m, 1,2,BLOCK); Maze_Put (m, 2,2,BLOCK);
        break;

        case (4):
            Maze_Put (m, 0,0,BLOCK); Maze_Put (m, 1,0,BLOCK); Maze_Put (m, 2,0,BLOCK);
            Maze_Put (m, 0,1,BLANK); Maze_Put (m, 1,1,BLOCK); Maze_Put (m, 2,1,BLANK);
            Maze_Put (m, 0,2,BLOCK); Maze_Put (m, 1,2,BLOCK); Maze_Put (m, 2,2,BLOCK);
        break;

        case (5):
            Maze_Put (m, 0,0,BLOCK); Maze_Put (m, 1,0,BLANK); Maze_Put (m, 2,0,BLOCK);
            Maze_Put (m, 0,1,BLOCK); Maze_Put (m, 1,1,BLOCK); Maze_Put (m, 2,1,BLOCK);
            Maze_Put (m, 0,2,BLOCK); Maze_Put (m, 1,2,BLANK); Maze_Put (m, 2,2,BLOCK);
        break;

        default:
            fprintf (stderr, "Random_Basic_Element given wrong element.\n");
            exit (1);
    }
} /* End Random_Basic_Element */

void Combine_Submazes_Into_Maze (Maze m, Maze mq1, Maze mq2, Maze mq3, Maze mq4)
{
    int sub_size;
    int x, y;

    /* This the implicit size of the mq1, mq2, mq3, mq4 submaze quarters */
    sub_size = Maze_Size(m) / 2;
    /* Error Check */
    if (sub_size != Maze_Size(mq1))
    {
        fprintf (stderr, "Combine_Submazes_Into_Maze found bad maze sizes.\n");
        exit (1);
    }

    /* Copy the Submaze quarter's data */
    for (x = 0; x < sub_size; ++x)
        for (y = 0; y < sub_size; ++y)
        {
            Maze_Put (m, x,            y,            Maze_Get(mq1, x, y));
            Maze_Put (m, x+sub_size+1, y,            Maze_Get(mq2, x, y));
            Maze_Put (m, x,            y+sub_size+1, Maze_Get(mq3, x, y));
            Maze_Put (m, x+sub_size+1, y+sub_size+1, Maze_Get(mq4, x, y));
        }

    /* Fill the strip between the quarters with BLANKs */
    for (x = 0; x < Maze_Size(m); ++x)
    {
        Maze_Put (m, x, sub_size, BLANK);
        Maze_Put (m, sub_size, x, BLANK);
    }

    /* Now connect the quadrants with three connecting blocks
    I don't currently attempt to allow the center of the four quadrants to
    be filled. This would be nicer for completeness in the future, but it's
    a very minor deficancy.
     */

    do
        x = (rand()%(sub_size));
    while (!(Maze_Get(m, x, sub_size-1) == BLOCK && Maze_Get(m, x, sub_size+1) == BLOCK));
    Maze_Put (m, x, sub_size, BLOCK);

    do
        y = (rand()%(sub_size));
    while (!(Maze_Get(m, sub_size-1, y) == BLOCK && Maze_Get(m, sub_size+1, y) == BLOCK));
    Maze_Put (m, sub_size, y, BLOCK);

    if (rand()%(2))
    {
        do
            x = (rand()%(sub_size)) + sub_size + 1;
        while (!(Maze_Get(m, x, sub_size-1) == BLOCK  && Maze_Get(m, x, sub_size+1) == BLOCK));
        Maze_Put (m, x, sub_size, BLOCK);
    }
    else
    {
        do
            y = (rand()%(sub_size)) + sub_size + 1;
        while (!(Maze_Get(m, sub_size-1, y) == BLOCK  && Maze_Get(m, sub_size+1, y) == BLOCK));
        Maze_Put (m, sub_size, y, BLOCK);
    }
}

void Build_Maze (Maze m)
{
    Maze maze_quarter_1, maze_quarter_2, maze_quarter_3, maze_quarter_4;
    int sub_size;

    if (Maze_Size(m) == 3)
        Random_Basic_Element (m);
    else
    {
        sub_size = Maze_Size(m) / 2;  /* Integer divide rounds down. */

        maze_quarter_1 = Create_Maze (sub_size);
        maze_quarter_2 = Create_Maze (sub_size);
        maze_quarter_3 = Create_Maze (sub_size);
        maze_quarter_4 = Create_Maze (sub_size);

        Build_Maze (maze_quarter_1);
        Build_Maze (maze_quarter_2);
        Build_Maze (maze_quarter_3);
        Build_Maze (maze_quarter_4);

        Combine_Submazes_Into_Maze (m, maze_quarter_1, maze_quarter_2, maze_quarter_3, maze_quarter_4);

        Destroy_Maze (maze_quarter_1);
        Destroy_Maze (maze_quarter_2);
        Destroy_Maze (maze_quarter_3);
        Destroy_Maze (maze_quarter_4);
    }
} /* End Build_Maze */



int main (int argc, char *argv[])
{
    Maze Final_Maze;
    long Number_Of_3x3_Elements;
    int Number_Of_Quarterings_To_Do;

    printf ("NOAH SPURRIER for CMP101 PROG #5\n");

    /* Set the number of times the universe is to be quartered
    before you want to reach "the bottom". This will determine
    how much space you will need to store the universe. The number of
    quarter operations directly effects how many 3x3 base elements are
    needed (so the number of quarterings time 9 is the amounts of memory
    needed.
    */
    if (argc > 1)
      Number_Of_Quarterings_To_Do = atoi (argv[1]);
    else
      Number_Of_Quarterings_To_Do = 0;

    /* Six is the max value that seems to work on a 640K DOS machine */
    if (Number_Of_Quarterings_To_Do < 1 || Number_Of_Quarterings_To_Do > 6)
    {
      fprintf (stderr, "Enter an integer argument for the number of recursive\n");
      fprintf (stderr, "fractal layers you wish to descend (1 to 6).\n");
      exit(1);
    }

    /* The number of 3x3 elements corresponds to 4 raised to the power of
    the number of quartering operations to do.
    */
    Number_Of_3x3_Elements = (long) pow ((double)4, (double)Number_Of_Quarterings_To_Do);

    /* Create the Final_Maze storage area. Since the universe (maze) is
    square you only need to tell the dimensions of one side of the universe.
    This would seem the be the square-root of the number of 3x3 basic
    elements, but it isn't this simple, since you also have to allow for the
    fact that each 3x3 basic element wants a single space between it and its
    neighbor therefore the actual formula for finding the size of the side
    of the universe is 2(sqrt(num_3x3))-1. I had the client rather than
    Create_Maze figure this out because this formula is only applicable to
    this particular recursive algorithm and I want to add other algorithm
    options later.
    */
    Final_Maze = Create_Maze (2*(int)sqrt((double)Number_Of_3x3_Elements)-1);

    randomize();

    /* This is the member function of Maze that creates a maze using a
    recursive fractal technique. After this function is called the maze
    is all set to play with. All I do in this demo is print out the maze.
    */
    Build_Maze (Final_Maze);

    printf ("\n");
    Print_Maze (Final_Maze);
/* "\033[40m \033[0m" */
    printf ("\n");

    /* There is much to be desired about c++, but I will say one thing;
    the ability to create automatic constructors and destructors is a
    nice feature. It eliminates having to remember to destroy your variables
    when done.
    */
    Destroy_Maze (Final_Maze);

    return 0;
}
