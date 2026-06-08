/* Noah Spurrier (c)Copyright 1993 by Noah Spurrer
 * Submitted to CMP101 for PROGRAM #5
 */

/* Need this for gcc to compile math.h properly */
#define _POSIX_SOURCE 1
#include <stdio.h>
#include <math.h>
#include "handy.h"
#include "maze.h"

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
    printf ("\n");

    /* There is much to be desired about c++, but I will say one thing;
    the ability to create automatic constructors and destructors is a
    nice feature. It eliminates having to remember to destroy your variables
    when done.
    */
    Destroy_Maze (Final_Maze);

    return 0;
}    
